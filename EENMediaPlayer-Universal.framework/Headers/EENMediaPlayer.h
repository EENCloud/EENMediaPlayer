//
//  EENMediaPlayer.h
//  testvideo
//
//  Created by Greg Slomin on 5/19/16.
//  Copyright © 2016 Greg Slomin. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "FLVDownloader.h"


@protocol EENMediaPlayerDelegate <NSObject>
-(void)requestStarted;
-(void)headerReceived:(NSData*)header withStartTime:(NSDate*)date;
-(void)connectionClosedWithError:(NSError*)error;
-(void)playbackDidStart;
-(void)donePressed;
-(void)bufferingStarted;
@end

@interface EENMediaPlayer : UIView<FLVDownloaderDelegate, UIScrollViewDelegate>;
@property (nonatomic, retain) NSDate *startDate;
@property (nonatomic, retain, readonly) NSString *startTime;
@property (nonatomic, retain, readonly) NSString *endTime;
@property (nonatomic, retain) NSMutableArray *audioFrames;
@property (weak, nonatomic) IBOutlet UIButton *playButton;
@property (weak, nonatomic) IBOutlet UIView *controlBar;
@property (weak, nonatomic) IBOutlet UILabel *playedTime;
@property (nonatomic, assign) double duration;
@property (weak, nonatomic) IBOutlet UIBarButtonItem *playBarButton;
@property (weak, nonatomic) IBOutlet UIBarButtonItem *doneBarButton;
@property (nonatomic, retain) id<EENMediaPlayerDelegate> delegate;
-(void)startStream:(NSString*)esn baseURL:(NSString*)baseURL withTitle:(NSString*)title startTime:(NSString*)startTime endTime:(NSString*)endTime dateFormat:(NSString*)dateFormat andTimezone:(NSTimeZone*)timeZone;
-(void)enableControlBar:(BOOL)enable;
-(void)destroy;

@end

