//
//  FLVDownloader.h
//  flv_player
//
//  Created by Greg Slomin on 5/28/16.
//  Copyright © 2016 Greg Slomin. All rights reserved.
//
#import <Foundation/Foundation.h>

typedef enum {
	CLOSED, // Initial state
	WAIT_FOR_HEADER, // Waiting for FLV header
	READING, // Reading frame data
	CANCELLING, // Cancelling stream reader
	READ_FINISHED // Finished reading
} ReaderState;

@protocol FLVDownloaderDelegate <NSObject>
-(void)headerReceived:(NSData*)header withStartTime:(NSDate*)date;
-(void)tagReceived:(NSData*)tag atOffset:(NSUInteger)fileOffset;
-(void)connectionClosedWithError:(NSError*)error;
@end

@interface FLVDownloader : NSObject<NSStreamDelegate, NSURLConnectionDelegate>
@property (nonatomic, retain) id<FLVDownloaderDelegate> delegate;
@property (nonatomic, retain) NSURLConnection *connection;
@property (nonatomic, retain) NSDate *startTime;
@property (nonatomic, assign) ReaderState readerState;
-(id)initWithURL:(NSURL*)url;
-(void)openStream;
-(void)closeStream;
@end
