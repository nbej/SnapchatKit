//
//  SKIPCRequest.h
//
//  Created by Tanner on 1/17/17.
//  Copyright © 2017 Tanner Bennett. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SKIPCResponse.h"


#pragma mark Request methods
typedef NS_ENUM(NSUInteger, SCAPIRequestMethod) {
    SCAPIRequestMethodGET,
    SCAPIRequestMethodPOST,
    SCAPIRequestMethodDELETE,
    SCAPIRequestMethodPUT
};

extern NSString * SKStringFromMethod(SCAPIRequestMethod method);

#pragma mark Internal keys
extern NSString * const kQueryName;
extern NSString * const kQueryKey;
extern NSString * const kResponseKey;
extern NSString * const kURLRequestKey;
extern NSString * const kRegisterForDelegation;
extern NSString * const kSnapchatBundleID;


#pragma mark - SKIPCRequest
@interface SKIPCRequest : NSObject<NSCopying, NSCoding>

#pragma mark Querying IPC availability
+ (BOOL)testIPC;
+ (void)testIPC:(void(^)(BOOL success))callback;

#pragma mark Initialization
/// needsAuth == YES
+ (instancetype)authForEndpoint:(NSString *)endpoint params:(NSDictionary *)params method:(SCAPIRequestMethod)method;
/// needsAuth == NO, method == SCAPIRequestMethodPOST
+ (instancetype)endpoint:(NSString *)endpoint params:(NSDictionary *)params;

#pragma mark Sending requests
- (void)sendAsync:(void(^)(SKIPCResponse *response))callback;
- (SKIPCResponse *)sendSync;

#pragma mark Automatic properties
/// Comes from SKClient.sharedClient.username
@property (nonatomic, copy) NSString           *username;
@property (nonatomic, copy) NSString           *timestamp;

#pragma mark Manual properties
@property (nonatomic, copy) NSString           *fullURL;
@property (nonatomic, copy) NSString           *endpoint;
@property (nonatomic, copy) NSDictionary       *params;
@property (nonatomic, copy) NSDictionary       *additionalHeaders;
@property (nonatomic      ) SCAPIRequestMethod method;
@property (nonatomic      ) BOOL               needsAuth;
@property (nonatomic      ) BOOL               multipart;

/// Return info even if username / app version doesn't match
@property (nonatomic) BOOL force;

@end
