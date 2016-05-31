//
//  ViewController.h
//  PayDemo
//
//  Created by SongChunMin on 15/8/12.
//  Copyright (c) 2015年 SongChunMin. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <PassKit/PassKit.h>

@interface ViewController : UIViewController
<PKPaymentAuthorizationViewControllerDelegate>

- (IBAction)checkOut:(id)sender;

@end

