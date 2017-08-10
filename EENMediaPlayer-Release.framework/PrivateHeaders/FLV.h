//
//  FLV.h
//  flv_player
//
//  Created by Greg Slomin on 5/29/16.
//  Copyright © 2016 Greg Slomin. All rights reserved.
//

#ifndef FLV_h
#define FLV_h
#import <AVFoundation/AVFoundation.h>

//#define _DEBUG

uint32_t CFSwapInt24BigToHost(uint32_t val);

extern NSString * const naluTypesStrings[];

extern  const double aacFreqTable[];

extern  const double flvFreqTable[];

extern NSString* const AACObjectTypes [];

extern NSString * const AACFrequencyConfigTypes[];

extern NSString *AACChannelConfigTypes[];

union FLVHeader {
	char buffer[0xD];
	struct {
		char magic[3];
		uint8_t version;
		uint8_t video  : 1;
		uint8_t dummy2 : 1;
		uint8_t audio  : 1;
		uint8_t dummy1 : 5;
		uint32_t dataOffset;
		uint32_t alwaysZero;
	} flv;
};

union base_tag{
	char buffer[11];
	struct{
		uint8_t type : 8;
		uint32_t datasize : 24;
		uint32_t timestamp : 24;
		uint8_t timestamphi : 8;
		uint32_t streamid : 24;
		void* tagData;
	} tag_data;
};

struct audio_tag_data {
	uint8_t channels : 1;
	uint8_t bits : 1;
	uint8_t sr : 2;
	uint8_t fmt : 4;
	uint8_t *buffer;
};

struct aac_audio_data {
	Byte type;
	Byte* data;
};

struct audio_specific_config {
	
	Byte type : 5;
	Byte freqIdx : 4;
	Byte channelConfig : 4;
	
	
};

struct video_tag_data {
	uint8_t codecid : 4;
	uint8_t frmtype : 4;
	uint8_t pkttype : 8;
	uint32_t compositionTime : 24;
	void *buffer;
}  __attribute__ ((__packed__));

struct PSBlock {
	int length;
	uint8_t *data;
} ;

struct avcc_header {
	uint8_t configVersion : 8;
	uint8_t AVCProfileIndication : 8;
	uint8_t profile_compatibility : 8;
	uint8_t AVCLevelIndication : 8;
	uint8_t RLELength : 2;
	uint8_t reserved : 6;
	uint8_t numSPS : 5;
	uint8_t reserved2 : 3;
	struct PSBlock spsBlock;
	uint8_t numPPS : 8;
	struct PSBlock ppsBlock;
};

struct NALU {
	uint32_t size;
	uint8_t* data;
};

#define PRINTERROR(LABEL)   printf("%s err %4.4s %ld\n", LABEL, (char *)&err, (long)err)
#define kNumAQBufs 1024          // number of audio queue buffers we allocate

// (kAQBufSize / 8000) = time until playback starts (1s)
// (kAQBufSize / 8000) * kNumAQBufs = total potential buffered playback time (192s)
#define kAQBufSize 1 * 1024       // number of bytes in each audio queue buffer
#define kAQMaxPacketDescs 1024       // number of packet descriptions in our array

struct AudioQueueData
{
	bool audioQueueStarted;
	AudioQueueRef audioQueue;                               // the audio queue
	AudioQueueBufferRef audioQueueBuffer[kNumAQBufs];       // audio queue buffers
	AudioQueueTimelineRef timeline;
	AudioStreamPacketDescription packetDescs[kAQMaxPacketDescs];    // packet descriptions for enqueuing audio
	AudioStreamBasicDescription asbd;
	unsigned int fillBufferIndex;   // the index of the audioQueueBuffer that is being filled
	size_t bytesFilled;             // how many bytes have been filled
	size_t packetsFilled;           // how many packets have been filled
 
	bool inuse[kNumAQBufs];         // flags to indicate that a buffer is still in use
	bool started;                   // flag to indicate that the queue has been started
	bool failed;                    // flag to indicate an error occurred
	
	int numPrimedFrames;
	
	void* videoLayer;
	void* viewController;
 
	pthread_mutex_t mutex;          // a mutex to protect the inuse flags
	pthread_cond_t cond;            // a condition varable for handling the inuse flags
	pthread_cond_t done;            // a condition varable for handling the inuse flags
	bool configured;
};
#endif /* FLV_h */
