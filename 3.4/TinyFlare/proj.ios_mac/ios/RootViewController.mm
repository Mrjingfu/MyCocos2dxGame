/****************************************************************************
 Copyright (c) 2013      cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#import "RootViewController.h"
#import "cocos2d.h"
#import "platform/ios/CCEAGLView-ios.h"

@implementation RootViewController

/*
 // The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if ((self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])) {
        // Custom initialization
    }
    return self;
}
*/

/*
// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
}
*/

/*
// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
}

*/
// Override to allow orientations other than the default portrait orientation.
// This method is deprecated on ios6
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return UIInterfaceOrientationIsLandscape( interfaceOrientation );
}

// For ios6, use supportedInterfaceOrientations & shouldAutorotate instead
- (NSUInteger) supportedInterfaceOrientations{
#ifdef __IPHONE_6_0
    return UIInterfaceOrientationMaskAllButUpsideDown;
#endif
}

- (BOOL) shouldAutorotate {
    return YES;
}

- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation {
    [super didRotateFromInterfaceOrientation:fromInterfaceOrientation];

    auto glview = cocos2d::Director::getInstance()->getOpenGLView();

    if (glview)
    {
        CCEAGLView *eaglview = (CCEAGLView*) glview->getEAGLView();

        if (eaglview)
        {
            CGSize s = CGSizeMake([eaglview getWidth], [eaglview getHeight]);
            cocos2d::Application::getInstance()->applicationScreenSizeChanged((int) s.width, (int) s.height);
        }
    }
}

//fix not hide status on ios7
- (BOOL)prefersStatusBarHidden
{
    return YES;
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];

    // Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


- (void)dealloc {
    [super dealloc];
}

- (void) showRateAppViewCH {
    NSString *plistPath = [[NSBundle mainBundle] pathForResource:@"chinese" ofType:@"plist"];
    NSMutableDictionary *data = [[NSMutableDictionary alloc] initWithContentsOfFile:plistPath];
    NSString* rateTitle = [data objectForKey:@"RATE_TITLE"];
    NSString* rateMessage = [data objectForKey:@"RATE_MESSAGE"];
    NSString* rateNow = [data objectForKey:@"RATE_NOW"];
    NSString* rateNever = [data objectForKey:@"RATE_NEVER"];
    NSString* rateLater = [data objectForKey:@"RATE_LATER"];
    [RateThisAppDialog threeButtonLayoutWithTitle:rateTitle
                                          message:rateMessage
                                rateNowButtonText:rateNow
                              rateLaterButtonText:rateLater
                              rateNeverButtonText:rateNever];
}
- (void) showRateAppViewEN {
    NSString *plistPath = [[NSBundle mainBundle] pathForResource:@"english" ofType:@"plist"];
    NSMutableDictionary *data = [[NSMutableDictionary alloc] initWithContentsOfFile:plistPath];
    NSString* rateTitle = [data objectForKey:@"RATE_TITLE"];
    NSString* rateMessage = [data objectForKey:@"RATE_MESSAGE"];
    NSString* rateNow = [data objectForKey:@"RATE_NOW"];
    NSString* rateNever = [data objectForKey:@"RATE_NEVER"];
    NSString* rateLater = [data objectForKey:@"RATE_LATER"];
    [RateThisAppDialog threeButtonLayoutWithTitle:rateTitle
                                          message:rateMessage
                                rateNowButtonText:rateNow
                              rateLaterButtonText:rateLater
                              rateNeverButtonText:rateNever];
}
- (void)initAdmob {
    
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        
        CGPoint origin = CGPointMake(0,self.view.frame.size.height - kGADAdSizeBanner.size.height);
        // NOTE:
        // Add your publisher ID here and fill in the GADAdSize constant for the ad
        // you would like to request.
        admobBannerView = [[GADBannerView alloc] initWithAdSize:kGADAdSizeBanner origin:origin];
    } else {
        CGPoint origin = CGPointMake(0,self.view.frame.size.height - kGADAdSizeFullBanner.size.height);
        // NOTE:
        // Add your publisher ID here and fill in the GADAdSize constant for the ad
        // you would like to request.
        admobBannerView = [[GADBannerView alloc] initWithAdSize:kGADAdSizeFullBanner origin:origin];
    }
    if(admobBannerView != nil)
    {
        admobBannerView.adUnitID = @"ca-app-pub-3628527903442392/3305707866";
        [admobBannerView setRootViewController:self];
        admobBannerView.hidden = YES;
        [self.view addSubview:admobBannerView];
    }
    [self requestAndLoadInterstitialAds];
}
- (GADRequest *)createRequest {
    GADRequest *request = [GADRequest request];
    // Requests test ads on devices you specify. Your test device ID is printed to the console when
    // an ad request is made.
    request.testDevices = [NSArray arrayWithObjects:
                           @"63c2655bf2b6d8b7776d3e37639a6a0add8ea741",
                           nil];
    return request;
}
- (void) showAdsView {
    if(admobBannerView != nil)
    {
        admobBannerView.delegate = self;
        [admobBannerView loadRequest:[self createRequest]];
    }
}
- (void) hideAdsView {
    if(admobBannerView != nil)
    {
        admobBannerView.delegate = nil;
        admobBannerView.hidden = YES;
    }
}
- (void) requestAndLoadInterstitialAds {
    admobInterstitial = [[GADInterstitial alloc] initWithAdUnitID:@"ca-app-pub-3628527903442392/4782441069"];
    if(admobInterstitial != nil)
    {
        admobInterstitial.delegate = self;
        [admobInterstitial loadRequest:[self createRequest]];
    }
}
- (void) playInterstitialAds {
    if(admobInterstitial != nil)
    {
        if (admobInterstitial.isReady)
            [admobInterstitial presentFromRootViewController:self];
        else
            NSLog(@"The interstitial didn't finish loading or failed to load");
    }
}

- (void) showIndicatorView {
     activityIndicator = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhiteLarge];
    activityIndicator.center = self.view.center;
    [self.view addSubview:activityIndicator];
    [self.view bringSubviewToFront:activityIndicator];
    self.view.window.userInteractionEnabled = NO;
    [activityIndicator startAnimating];
}
- (void) hideIndicatorView {
    if(activityIndicator != nil)
    {
        [activityIndicator stopAnimating];
        [activityIndicator removeFromSuperview];
        self.view.window.userInteractionEnabled = YES;
    }
}

#pragma mark GADBannerViewDelegate impl

- (void)adViewDidReceiveAd:(GADBannerView *)adView {
    NSLog(@"Received ad");
    admobBannerView.hidden = NO;
    [admobBannerView.superview bringSubviewToFront:admobBannerView];
}

- (void)adView:(GADBannerView *)view
didFailToReceiveAdWithError:(GADRequestError *)error {
    NSLog(@"Failed to receive ad with error: %@", [error localizedFailureReason]);
}
#pragma mark GADInterstitialDelegate implementation
- (void)interstitialDidReceiveAd:(GADInterstitial *)ad
{
     NSLog(@"Received interstitial ad");
}

- (void)interstitial:(GADInterstitial *)interstitial
didFailToReceiveAdWithError:(GADRequestError *)error {
    NSLog(@"interstitialDidFailToReceiveAdWithError: %@", [error localizedDescription]);
    [self requestAndLoadInterstitialAds];
}

- (void)interstitialDidDismissScreen:(GADInterstitial *)interstitial {
    NSLog(@"interstitialDidDismissScreen");
    [self requestAndLoadInterstitialAds];
}
@end
