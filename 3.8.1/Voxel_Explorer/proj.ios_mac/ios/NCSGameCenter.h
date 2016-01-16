//
//  NCSGameCenter.h
//  MazeJump
//
//  Created by wang haibo on 15/8/17.
//
//
#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <GameKit/GameKit.h>
@interface NCSGameCenter : NSObject <GKLeaderboardViewControllerDelegate, GKAchievementViewControllerDelegate, GKMatchmakerViewControllerDelegate, GKMatchDelegate> {
    BOOL gameCenterAvailable;
    BOOL userAuthenticated;
}

@property (assign, readonly) BOOL gameCenterAvailable;

//本地成就字典，用来保存已经下载下来的成就，以避免重复从gamecenter获取成就状态
@property (nonatomic, retain) NSMutableDictionary* achievementDictionary;

+ (NCSGameCenter *)sharedGameCenter;
- (void) authenticateLocalUser;
- (void) registerForAuthenticationNotification;

- (void) showLeaderboard;

//上传分数到Gamecenter
- (void) reportScore:(NSString*)rand_id score:(NSNumber *)score;
//上传失败需要存储之后再上传
- (void) storeScoreForLater:(NSData *)scoreData;
//重新提交分数
- (void) reportCachedScores;
//从gamecenter下载前X个分数
- (void) retrieveTopXScores:(NSString*)rand_id number:(int)number;

- (void) showAchievementboard;
- (void) loadAchievement;
- (void) clearAchievements;
- (void) reportAchievement:(NSString*)id percent:(float)percent;
- (GKAchievement*) getAchievementForID:(NSString*)id;

#pragma mark GKLeaderboardViewControllerDelegate
- (void) leaderboardViewControllerDidFinish:(GKLeaderboardViewController *)viewController;
#pragma mark GKAchievementViewControllerDelegate
- (void) achievementViewControllerDidFinish:(GKAchievementViewController *)achievementController;
#pragma mark GKMatchmakerViewControllerDelegate
- (void)matchmakerViewControllerWasCancelled:(GKMatchmakerViewController *)viewController;
#pragma mark GKMatchDelegate
- (void)matchmakerViewController:(GKMatchmakerViewController *)viewController didFailWithError:(NSError *)error;
@end
