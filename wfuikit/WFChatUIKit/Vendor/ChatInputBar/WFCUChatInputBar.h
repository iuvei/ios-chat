//
//  ChatInputBar.h
//  WFChat UIKit
//
//  Created by WF Chat on 2017/10/28.
//  Copyright © 2017年 WildFireChat. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>
#import <WFChatClient/WFCChatClient.h>

#define CHAT_INPUT_BAR_HEIGHT 48
#define TYPING_INTERVAL 10

@interface WFCUMetionInfo : NSObject
- (instancetype)initWithType:(int)type target:(NSString *)target range:(NSRange)range;
@property (nonatomic, assign)NSRange range;
//提醒类型，1，提醒部分对象（mentinedTarget）。2，提醒全部。其他不提醒
@property (nonatomic, assign)int mentionType;
@property (nonatomic, strong)NSString *target;
@end

//@interface TextInfo : NSObject
//@property (nonatomic, strong)NSString *text;
//@property (nonatomic, strong)NSMutableArray<MetionInfo *> *mentionInfos;
//@end

@protocol WFCUChatInputBarDelegate <NSObject>
@optional
- (void)didTouchSend:(NSString *)stringContent withMentionInfos:(NSMutableArray<WFCUMetionInfo *> *)mentionInfos withQuoteInfo:(WFCCQuoteInfo *)quoteInfo;

- (void)recordDidBegin;
- (void)recordDidCancel;
- (void)recordDidEnd:(NSString *)dataUri duration:(long)duration error:(NSError *)error;
- (void)imageDidCapture:(UIImage *)image fullImage:(BOOL)fullImage;
- (void)videoDidCapture:(NSString *) videoPath thumbnail:(UIImage *)image duration:(long)duration;
- (void)sightDidFinishRecord:(NSString*)url thumbnail:(UIImage*)image duration:(NSUInteger)duration;
- (void)locationDidSelect:(CLLocationCoordinate2D)location locationName:(NSString *)locationName mapScreenShot:(UIImage *)mapScreenShot;
- (void)imageDataDidSelect:(NSArray<UIImage *> *)selectedImages isFullImage:(BOOL)fullImage;
- (void)didTapChannelMenu:(WFCCChannelMenu *)channelMenu;
- (void)didSelectFiles:(NSArray *)files;
#if WFCU_SUPPORT_VOIP
- (void)didTouchVideoBtn:(BOOL)isAudioOnly;
#endif
- (void)didSelectSticker:(NSString *)stickerPath;
- (void)willChangeFrame:(CGRect)newFrame withDuration:(CGFloat)duration keyboardShowing:(BOOL)keyboardShowing;

- (UINavigationController *)requireNavi;

- (void)onTyping:(WFCCTypingType)type;
- (void)needSaveDraft;
@optional
- (void)gifDidCapture:(NSData *)gifData;
@end

typedef NS_ENUM(NSInteger, ChatInputBarStatus) {
    ChatInputBarDefaultStatus = 0,
    ChatInputBarKeyboardStatus,
    ChatInputBarPluginStatus,
    ChatInputBarEmojiStatus,
    ChatInputBarRecordStatus,
    ChatInputBarPublicStatus,
    ChatInputBarMuteStatus,
#ifdef WFC_PTT
    ChatInputBarPttStatus
#endif
};

@class WFCCConversation;

@interface WFCUChatInputBar : UIView
- (instancetype)initWithSuperView:(UIView *)parentView conversation:(WFCCConversation *)conversation delegate:(id<WFCUChatInputBarDelegate>)delegate;
@property(nonatomic, assign)ChatInputBarStatus inputBarStatus;
- (void)resetInputBarStatue;
@property(nonatomic, strong)NSString *draft;

- (BOOL)appendMention:(NSString *)userId name:(NSString *)userName;
- (BOOL)appendQuote:(WFCCMessage *)message;
- (void)paste:(id)sender;
- (void)willAppear;
- (void)appendText:(NSString *)text;
- (NSString *)getDraftText:(NSString *)draft;
- (void)resetTyping;
@end
