//
//  SampleBufferView.h
//  flv_player
//
//  Created by Greg Slomin on 5/29/16.
//  Copyright © 2016 Greg Slomin. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface SampleBufferView : UIView
@property (nonatomic, weak) CALayer *videoSublayer;
-(id)initWithFrame:(CGRect)frame andSublayer:(CALayer*)videoSubLayer;
@end
