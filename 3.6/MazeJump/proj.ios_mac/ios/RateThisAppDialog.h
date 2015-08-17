//
//  RateThisAppDialog.h
//  RateThisApp
//
//  Created by Michael Dawson on 29/07/11.
//  Copyright 2011 Nippysaurus. All rights reserved.
//

#import <Foundation/Foundation.h>

// this is the link to your app in itunes
// Please use the "iTunes Link Maker" to create this url:
// http://itunes.apple.com/linkmaker/
// you do not need to put "itms://" at the front or anything like that.
#define APP_STORE_LINK @"itms://itunes.apple.com/us/app/rainbows-end/id1031110631?l=zh&ls=1&mt=8"

// this is how many times your app can launch before showing this dialog
// ie. setting this to 2 will cause the dialog to appear on the second time the app is launched
#define PROMPT_AFTER_X_LAUNCHES 10

@interface RateThisAppDialog : NSObject {
    
    @public
    
    void (^_rateNowDefault)(void);
    void (^_rateLaterDefault)(void);
    void (^_rateNeverDefault)(void);
    BOOL (^_shouldShowDialogDefault)(void);
    
    void (^alertViewIndexOne)(void);
    void (^alertViewIndexTwo)(void);
    void (^alertViewIndexThree)(void);
}

+ (void)threeButtonLayoutWithTitle:(NSString*)title
                           message:(NSString*)message
                rateNeverButtonText:(NSString*)rateNeverButtonText
                rateLaterButtonText:(NSString*)rateLaterButtonText
                rateNowButtonText:(NSString*)rateNowButtonText;

+ (void)twoButtonLayoutWithTitle:(NSString*)title
                         message:(NSString*)message
               rateNowButtonText:(NSString*)rateNowButtonText
             rateNeverButtonText:(NSString*)rateNeverButtonText;

@end