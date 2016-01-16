//
//  NCSGameCenter.m
//  MazeJump
//
//  Created by wang haibo on 15/8/17.
//
//

#import "NCSGameCenter.h"
#import "AppController.h"
@implementation NCSGameCenter
@synthesize gameCenterAvailable;

//静态初始化 对外接口
static NCSGameCenter *sharedHelper = nil;
+ (NCSGameCenter *) sharedGameCenter {
    if (!sharedHelper) {
        sharedHelper = [[NCSGameCenter alloc] init];
    }
    return sharedHelper;
}

//用于验证
- (BOOL)isGameCenterAvailable {
    // check for presence of GKLocalPlayer API
    Class gcClass = (NSClassFromString(@"GKLocalPlayer"));
    
    // check if the device is running iOS 4.1 or later
    NSString *reqSysVer =@"4.1";
    NSString *currSysVer = [[UIDevice currentDevice] systemVersion];
    BOOL osVersionSupported = ([currSysVer compare:reqSysVer
                                           options:NSNumericSearch] != NSOrderedAscending);
    
    return (gcClass && osVersionSupported);
}

- (id)init {
    if ((self = [super init])) {
        gameCenterAvailable = [self isGameCenterAvailable];
        if (gameCenterAvailable) {
            [self registerForAuthenticationNotification];
        }
    }
    return self;
}

//后台回调登陆验证
- (void)authenticationChanged {
    
    if ([GKLocalPlayer localPlayer].isAuthenticated &&!userAuthenticated) {
        NSLog(@"Authentication changed: player authenticated.");
        userAuthenticated = TRUE;
    } else if (![GKLocalPlayer localPlayer].isAuthenticated && userAuthenticated) {
        NSLog(@"Authentication changed: player not authenticated");
        userAuthenticated = FALSE;
    }
}

- (void)authenticateLocalUser {
    
    if (!gameCenterAvailable) return;
    GKLocalPlayer* localPlayer = [GKLocalPlayer localPlayer];
    if (localPlayer.authenticated == NO) {
        if ([[GKLocalPlayer class] instancesRespondToSelector:@selector(setAuthenticateHandler:)]) {
            [localPlayer setAuthenticateHandler:^(UIViewController *viewController,NSError *error) {
                if (viewController != nil)
                {
                    AppController* delegate = (AppController*) [UIApplication sharedApplication].delegate;
                    
                    [delegate.viewController presentViewController : viewController animated : YES completion : nil];
                }
                else if (localPlayer.isAuthenticated)
                {
                    //认证完毕后从gamecenter中获取成就状态，以备后面上传成就时查询
                    [self loadAchievement];
                    //上传缓存积分
                    [self reportCachedScores];
                }
                else
                {
                    if(error != nil)
                        NSLog(@"error: %@", error.localizedDescription);
                    else
                        NSLog(@"error: your game is running on does not support Game Center!");
                }
            }];
        }
        else // alternative for iOS < 6
        {
            [[GKLocalPlayer localPlayer] setAuthenticateHandler:^(UIViewController *viewController,NSError *error) {
                if (error == nil)
                {
                    //认证完毕后从gamecenter中获取成就状态，以备后面上传成就时查询
                    [self loadAchievement];
                    //上传缓存积分
                    [self reportCachedScores];
                }
                else
                    NSLog(@"error: %@", error.localizedDescription);
            }];

        }
    } else {
        NSLog(@"Already authenticated!");
        //认证完毕后从gamecenter中获取成就状态，以备后面上传成就时查询
        [self loadAchievement];
        //上传缓存积分
        [self reportCachedScores];
    }
}

- (void) registerForAuthenticationNotification
{
    NSNotificationCenter *nc = [NSNotificationCenter defaultCenter];
    [nc addObserver:self
           selector:@selector(authenticationChanged)
               name:GKPlayerAuthenticationDidChangeNotificationName
             object:nil];
}

//显示排行榜
- (void) showLeaderboard
{
    if (!gameCenterAvailable) return;
    
    GKLeaderboardViewController *leaderboardController = [[GKLeaderboardViewController alloc] init];
    if (leaderboardController != nil) {
        leaderboardController.leaderboardDelegate = self;
        
        AppController* delegate = (AppController*) [UIApplication sharedApplication].delegate;
        
        [delegate.viewController presentViewController : leaderboardController animated : YES completion : nil];
    }
    
    [self reportCachedScores];
}

//上传分数到排行榜
- (void) reportScore:(NSString*)rand_id score:(NSNumber *)score
{
    GKScore *scoreReporter = [[[GKScore alloc] initWithCategory:rand_id] autorelease];
    if (strcmp([score objCType], @encode(float)) == 0)
        scoreReporter.value = [score floatValue];
    else if (strcmp([score objCType], @encode(double)) == 0)
        scoreReporter.value = [score doubleValue];
    else if (strcmp([score objCType], @encode(int)) == 0)
        scoreReporter.value = [score intValue];
    else
        scoreReporter.value = [score longLongValue];
    
    [scoreReporter reportScoreWithCompletionHandler:^(NSError *error) {
        if (error != nil)
        {
            NSLog(@"上传分数出错.");
            NSData *saveSocreData = [NSKeyedArchiver archivedDataWithRootObject:scoreReporter];
            //未能提交得分，需要保存下来后继续提交
            [self storeScoreForLater:saveSocreData];
        }
        else
        {
            NSLog(@"上传分数成功");
        }
    }];
}
//上传失败需要存储之后再上传
- (void)storeScoreForLater:(NSData *)scoreData{
    NSMutableArray *savedScoresArray = [[NSMutableArray alloc] initWithArray:[[NSUserDefaults standardUserDefaults] objectForKey:@"savedScores"]];
    
    [savedScoresArray addObject:scoreData];
    [[NSUserDefaults standardUserDefaults] setObject:savedScoresArray forKey:@"savedScores"];
}
//重新提交分数
- (void)reportCachedScores{
    NSMutableArray *savedScoreArray = [[NSMutableArray alloc] initWithArray:[[NSUserDefaults standardUserDefaults] objectForKey:@"savedScores"]];
    
    [[NSUserDefaults standardUserDefaults] removeObjectForKey:@"savedScores"];
    
    for(NSData *scoreData in savedScoreArray){
        GKScore *scoreReporter = [NSKeyedUnarchiver unarchiveObjectWithData:scoreData];
        
        [scoreReporter reportScoreWithCompletionHandler:^(NSError *error) {
            if(error != nil){
                NSData *saveSocreData = [NSKeyedArchiver archivedDataWithRootObject:scoreReporter];
                //未能提交得分，需要保存下来后继续提交
                [self storeScoreForLater:saveSocreData];
            }else{
                NSLog(@"提交成功");
            }
        }];
    }
}
//下载分数
- (void) retrieveTopXScores:(NSString*)rand_id number:(int)number
{
    GKLeaderboard *leaderboardRequest = [[GKLeaderboard alloc] init];
    if (leaderboardRequest != nil)
    {
        leaderboardRequest.playerScope = GKLeaderboardPlayerScopeGlobal;
        leaderboardRequest.timeScope = GKLeaderboardTimeScopeAllTime;
        leaderboardRequest.range = NSMakeRange(1,number);
        leaderboardRequest.category = rand_id;
        [leaderboardRequest loadScoresWithCompletionHandler: ^(NSArray *scores, NSError *error) {
            if (error != nil){
                // handle the error.
                NSLog(@"下载失败");
            }
            if (scores != nil){
                // process the score information.
                NSLog(@"下载成功....");
                //NSArray *tempScore = [NSArray arrayWithArray:leaderboardRequest.scores];
                //for (GKScore *obj in tempScore) {
                //    NSLog(@"    playerID            : %@",obj.playerID);
                //    NSLog(@"    category            : %@",obj.category);
                //    NSLog(@"    date                : %@",obj.date);
                //    NSLog(@"    formattedValue    : %@",obj.formattedValue);
                //    NSLog(@"    value                : %d",obj.value);
                //    NSLog(@"    rank                : %d",obj.rank);
                //    NSLog(@"**************************************");
                //}
            }
        }];
    }
}

//汇报成就
//通过ID汇报成就
- (void) reportAchievement:(NSString*)id percent:(float)percent
{
    if ( !gameCenterAvailable ) {
        NSLog(@"ERROR: GameCenter is not available currently");
        return;
    }
    
    GKAchievement* achievement = [[[GKAchievement alloc] initWithIdentifier:id] autorelease];
    if ( achievement != nil )
    {
        achievement.percentComplete = percent;
        achievement.showsCompletionBanner = YES;
        [achievement reportAchievementWithCompletionHandler:^(NSError* error){
            if ( error != nil)
            {
                NSLog(@"上传成就错误，错误提示为\n%@", error);
            }
            else
            {
                NSLog(@"上传成就成功 percent = %f \n", percent);
                [self displayAchievement:achievement];
            }
        }];
    }
}

//显示成就
- (void) showAchievementboard
{
    if (!gameCenterAvailable) return;
    
    GKAchievementViewController *achievementController = [[GKAchievementViewController alloc] init];
    if (achievementController != nil) {
        achievementController.achievementDelegate = self;
        
        AppController* delegate = (AppController*) [UIApplication sharedApplication].delegate;
        
        [delegate.viewController presentViewController : achievementController animated : YES completion : nil];
    }
    
}

//打印某个成就
- (void) displayAchievement:(GKAchievement*)achievement
{
    if ( achievement == nil) return;
    
    NSLog(@"completed:%d", achievement.completed);
    NSLog(@"lastReportDate:%@", achievement.lastReportedDate);
    NSLog(@"percentComplete:%f", achievement.percentComplete);
    NSLog(@"identifier:%@", achievement.identifier);
}

//加载所有成就。经测试，只能获取到已经上传过的成就状态。
- (void) loadAchievement
{
    if ( self.achievementDictionary == nil )
    {
        self.achievementDictionary = [[NSMutableDictionary alloc] init];
    }
    [GKAchievement loadAchievementsWithCompletionHandler:^(NSArray* achievements, NSError* error){
        if ( error == nil && achievements != nil )
        {
            NSArray* tempArray = [NSArray arrayWithArray:achievements];
            for(GKAchievement* tempAchievement in tempArray)
            {
                [self.achievementDictionary setObject:tempAchievement
                                               forKey:tempAchievement.identifier];
                [self displayAchievement:tempAchievement];
            }
        }
    }];
    
}

//通过成就id生成成就。首先从本地成就字典查询，查询不到则生成一个。
- (GKAchievement*) getAchievementForID: (NSString*) id
{
    if ( self.achievementDictionary == nil )
    {
        self.achievementDictionary = [[NSMutableDictionary alloc] init];
    }
    GKAchievement *achievement = [self.achievementDictionary objectForKey:id];
    if (achievement == nil)
    {
        achievement = [[[GKAchievement alloc] initWithIdentifier:id] autorelease];
        [self.achievementDictionary setObject:achievement
                                       forKey:achievement.identifier];
    }
    [self displayAchievement:achievement];
    return [[achievement retain] autorelease];
}

//初始化所有成就状态。经测试，这段代码暂时无效。
- (void) clearAchievements
{
    NSEnumerator* enumerator = [self.achievementDictionary objectEnumerator];
    for(NSObject* obj in enumerator)
    {
        [self unlockAchievement:(GKAchievement*)obj percent:0.0];
    }
}
//关闭排行榜回调
#pragma mark GKLeaderboardViewControllerDelegate
- (void)leaderboardViewControllerDidFinish:(GKLeaderboardViewController *)viewController{
    AppController* delegate = (AppController*) [UIApplication sharedApplication].delegate;

    [delegate.viewController dismissViewControllerAnimated:YES completion : nil];
}

//关闭成就回调
#pragma mark GKAchievementViewControllerDelegate
- (void)achievementViewControllerDidFinish:(GKAchievementViewController *)viewController{
    AppController* delegate = (AppController*) [UIApplication sharedApplication].delegate;
    
    [delegate.viewController dismissViewControllerAnimated:YES completion : nil];
}

#pragma mark GKMatchmakerViewControllerDelegate
- (void)matchmakerViewControllerWasCancelled:(GKMatchmakerViewController *)viewController{
    
    AppController* delegate = (AppController*) [UIApplication sharedApplication].delegate;

    [delegate.viewController dismissViewControllerAnimated:YES completion : nil];
}
#pragma mark GKMatchDelegate
- (void)matchmakerViewController:(GKMatchmakerViewController *)viewController didFailWithError:(NSError *)error{
    
    AppController* delegate = (AppController*) [UIApplication sharedApplication].delegate;
    
    [delegate.viewController dismissViewControllerAnimated:YES completion : nil];
}
@end
