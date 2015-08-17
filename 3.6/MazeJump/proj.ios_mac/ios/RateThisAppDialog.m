//
//  RateThisAppDialog.m
//  RateThisApp
//
//  Created by Michael Dawson on 29/07/11.
//  Copyright 2011 Nippysaurus. All rights reserved.
//

#import "RateThisAppDialog.h"

@implementation RateThisAppDialog

#pragma mark - Memory Management

- (id)init
{
    self = [super init];
    if (self)
    {
        // rate now default
        
        self->_rateNowDefault = ^{
            NSLog(@"RateThisAppDialog :: rate now");
            
            NSURL *url = [NSURL URLWithString:APP_STORE_LINK];
            
            BOOL launchSuccess = [[UIApplication sharedApplication] openURL:url];
            
            if(launchSuccess == NO)
            {
                NSLog(@"RateThisAppDialog :: Failed to open URL (this is normal in the iOS Simulator ...)");
            }
            
            [[NSUserDefaults standardUserDefaults] setBool:YES forKey:@"app_rating_disabled"];
            [[NSUserDefaults standardUserDefaults] synchronize];
        };
        
        // rate later default
        
        self->_rateLaterDefault = ^{
            NSLog(@"RateThisAppDialog :: rate later");
            
            // set back to zero
            [[NSUserDefaults standardUserDefaults] setInteger:0 forKey:@"number_of_times_launched"];
            [[NSUserDefaults standardUserDefaults] synchronize];
        };
        
        // rate never default
        
        self->_rateNeverDefault = ^{
            NSLog(@"RateThisAppDialog :: rate never");
            
            [[NSUserDefaults standardUserDefaults] setBool:YES forKey:@"app_rating_disabled"];
            [[NSUserDefaults standardUserDefaults] synchronize];
        };
        
        // should show dialog default
        
        self->_shouldShowDialogDefault = ^{
            BOOL appRatingDisabled = [[NSUserDefaults standardUserDefaults] boolForKey:@"app_rating_disabled"];
            
            if (appRatingDisabled == YES)
            {
                NSLog(@"RateThisAppDialog :: app_rating_disabled = YES");
                return NO;
            }
            
            // if this user default has not been set then it will be zero
            NSInteger numberOfTimesLaunched = [[NSUserDefaults standardUserDefaults] integerForKey:@"number_of_times_launched"] + 1;
            
            NSLog(@"RateThisAppDialog :: number of times launched = %ld / %d", (long)numberOfTimesLaunched, PROMPT_AFTER_X_LAUNCHES);
            
            BOOL result = numberOfTimesLaunched >= PROMPT_AFTER_X_LAUNCHES;
            
            NSLog(@"RateThisAppDialog :: should show dialog = %@", (result == YES ? @"YES" : @"NO"));
            
            // disable now so that if the user closes the app without making a selection, they will not
            // be prompted again immediately after opening it again. they will not be prompted ever again
            // but this might be better than trying to pedict what they might be thinking. after all this
            // if just a friendly reminder convenience thing, not a bridge that the user must be forced
            // to cross before continuing to use the app.
            //if (result == YES)
            //    [[NSUserDefaults standardUserDefaults] setBool:YES forKey:@"app_rating_disabled"];
            
            // update the launch tally
            [[NSUserDefaults standardUserDefaults] setInteger:numberOfTimesLaunched forKey:@"number_of_times_launched"];
            [[NSUserDefaults standardUserDefaults] synchronize];
            
            return result;
        };
    }
    
    return self;
}

#pragma mark - UIAlertViewDelegate

- (void)alertView:(UIAlertView*)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex
{
    NSLog(@"RateThisAppDialog :: clicked button index %ld", (long)buttonIndex);
    
    if (buttonIndex == 0)
    {
        self->alertViewIndexOne();
    }
    if (buttonIndex == 1)
    {
        self->alertViewIndexTwo();
    }
    if (buttonIndex == 2)
    {
        self->alertViewIndexThree();
    }
    
    // i dont think its good practise for an object to release itself, but
    // this needs to be done in this situation, until i can figure out a
    // better way to structure this whole solution.
    [self release];
}

#pragma mark - Access Methods

+ (void)threeButtonLayoutWithTitle:(NSString*)title
                           message:(NSString*)message
                    rateNeverButtonText:(NSString*)rateNeverButtonText
                    rateLaterButtonText:(NSString*)rateLaterButtonText
                    rateNowButtonText:(NSString*)rateNowButtonText

{
    NSLog(@"RateThisAppDialog :: threeButtonLayoutWithTitle:%@ message:%@ rateNeverButtonText:%@ rateLaterButtonText:%@ rateNowButtonText:%@", title, message, rateNeverButtonText, rateLaterButtonText, rateNowButtonText);
    
    RateThisAppDialog *rateThisAppDialog = [[RateThisAppDialog alloc] init];
    
    // configure action handlers
    rateThisAppDialog->alertViewIndexOne = rateThisAppDialog->_rateNowDefault;
    rateThisAppDialog->alertViewIndexTwo = rateThisAppDialog->_rateNeverDefault;
    rateThisAppDialog->alertViewIndexThree = rateThisAppDialog->_rateLaterDefault;
    
    if (rateThisAppDialog->_shouldShowDialogDefault() == YES)
    {
        NSLog(@"RateThisAppDialog :: showing alert view");
        
        UIAlertView *alert = [[UIAlertView alloc]
                              initWithTitle: title
                              message: message
                              delegate: rateThisAppDialog
                              cancelButtonTitle:rateNowButtonText
                              otherButtonTitles:rateNeverButtonText, rateLaterButtonText, nil];
    
        NSLog(@"RateThisAppDialog :: releasing alert view");
        
        [alert show];
        [alert release];
    }

    // instead i will release this object when the "alertView:clickedButtonAtIndex:" delegate function is called. i think
    // that means if the user closes the app while the alert view is showing this object will be leaked, but i dont have
    // a better solution right now.
    // [rateThisAppDialog autorelease];
}

+ (void)twoButtonLayoutWithTitle:(NSString*)title
                         message:(NSString*)message
                   rateNowButtonText:(NSString*)rateNowButtonText
                   rateNeverButtonText:(NSString*)rateNeverButtonText
{
    NSLog(@"RateThisAppDialog :: threeButtonLayoutWithTitle:%@ message:%@ rateNowButtonText:%@ rateNeverButtonText:%@", title, message, rateNowButtonText, rateNeverButtonText);
    
    RateThisAppDialog *rateThisAppDialog = [[RateThisAppDialog alloc] init];

    // configure action handlers
    rateThisAppDialog->alertViewIndexOne = rateThisAppDialog->_rateNowDefault;
    rateThisAppDialog->alertViewIndexThree = rateThisAppDialog->_rateNeverDefault;
    
    if (rateThisAppDialog->_shouldShowDialogDefault() == YES)
    {
        NSLog(@"RateThisAppDialog :: showing alert view");
        
        UIAlertView *alert = [[UIAlertView alloc]
                              initWithTitle: title
                              message: message
                              delegate: rateThisAppDialog
                              cancelButtonTitle:rateNeverButtonText
                              otherButtonTitles:rateNowButtonText, nil];
        
        NSLog(@"RateThisAppDialog :: releasing alert view");
        
        [alert show];
        [alert release];
    }

    // instead i will release this object when the "alertView:clickedButtonAtIndex:" delegate function is called. i think
    // that means if the user closes the app while the alert view is showing this object will be leaked, but i dont have
    // a better solution right now.
    // [rateThisAppDialog autorelease];
}

@end