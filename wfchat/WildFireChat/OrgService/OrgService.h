//
//  AppService.h
//  WildFireChat
//
//  Created by Heavyrain Lee on 2019/10/22.
//  Copyright © 2019 WildFireChat. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WFChatUIKit/WFChatUIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface OrgService : NSObject <WFCUOrgServiceProvider>
+ (OrgService *)sharedOrgService;
- (void)login:(void(^)(void))successBlock error:(void(^)(int errCode))errorBlock;

- (NSData *)getAppServiceCookies;
- (NSString *)getAppServiceAuthToken;

//清除应用服务认证cookies和认证token
- (void)clearAppServiceAuthInfos;
@end

NS_ASSUME_NONNULL_END
