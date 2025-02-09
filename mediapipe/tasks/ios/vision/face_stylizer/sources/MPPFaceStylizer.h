// Copyright 2023 The MediaPipe Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#import <Foundation/Foundation.h>

#import "mediapipe/tasks/ios/vision/core/sources/MPPImage.h"
#import "mediapipe/tasks/ios/vision/face_stylizer/sources/MPPFaceStylizerOptions.h"
#import "mediapipe/tasks/ios/vision/face_stylizer/sources/MPPFaceStylizerResult.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * Class that performs face stylization on images.
 */
NS_SWIFT_NAME(FaceStylizer)
@interface MPPFaceStylizer : NSObject

/**
 * Creates a new instance of `FaceStylizer` from an absolute path to a model bundle stored locally
 * on the device and the default `FaceStylizer`.
 *
 * @param modelPath An absolute path to a TensorFlow Lite model file stored locally on the device.
 *
 * @return A new instance of `FaceStylizer` with the given model path. `nil` if there is an error in
 * initializing the face stylizer.
 */
- (nullable instancetype)initWithModelPath:(NSString *)modelPath error:(NSError **)error;

/**
 * Creates a new instance of `FaceStylizer` from the given `FaceStylizerOptions`.
 *
 * @param options The options of type `FaceStylizerOptions` to use for configuring the
 * `FaceStylizer`.
 *
 * @return A new instance of `FaceStylizer` with the given options. `nil` if there is an error in
 * initializing the face stylizer.
 */
- (nullable instancetype)initWithOptions:(MPPFaceStylizerOptions *)options
                                   error:(NSError **)error NS_DESIGNATED_INITIALIZER;

/**
 * Performs face stylization on the provided `MPImage` and returns a `MPPFaceStylizerResult`
 * containing a copy of the stylized image. This method should not be used in high-throughput
 * applications since the returned image is copied. Rotation will be applied according to the
 * `orientation` property of the provided `MPImage`.
 *
 * This method supports RGBA images. If your `MPPImage` has a source type of `.pixelBuffer` or
 * `.sampleBuffer`, the underlying pixel buffer must have one of the following pixel format types:
 * 1. kCVPixelFormatType_32BGRA
 * 2. kCVPixelFormatType_32RGBA
 *
 * If your `MPImage` has a source type of `.image` ensure that the color space is RGB with an
 * Alpha channel.
 *
 * @param image The `MPImage` on which face stylization is to be performed.
 *
 * @return A `FaceStylizerResult` that contains the stylized image of the most visible face. The
 * returned image is copied. The stylized output image size is the same as the model output
 * size. The `stylizedImage` of the `FaceStylizerResult` is `nil` if there is no face detected in
 * the imput image. `FaceStylizerResult` is `nil` if there is an error in initializing the face
 * stylizer.
 */
- (nullable MPPFaceStylizerResult *)stylizeImage:(MPPImage *)image
                                           error:(NSError **)error NS_SWIFT_NAME(stylize(image:));

/**
 * Performs face stylization on the provided `MPImage` using the whole image as region of interest
 * and provides zero-copied results via the given completion handler block. The lifetime of the
 * stylized image is only guaranteed for the duration of the block. The method returns synchronously
 * once the completion handler returns.
 *
 * Rotation will be applied according to the `orientation` property of the provided `MPImage`.
 *
 * This method supports RGBA images. If your `MPImage` has a source type of `.pixelBuffer` or
 * `.sampleBuffer`, the underlying pixel buffer must have one of the following pixel format types:
 * 1. kCVPixelFormatType_32BGRA
 * 2. kCVPixelFormatType_32RGBA
 *
 * If your `MPImage` has a source type of `.image` ensure that the color space is RGB with an Alpha
 * channel.
 *
 * @param image The `MPImage` on which face stylization is to be performed.
 * @param completionHandler A block to be invoked with the results of performing face stylization on
 * the imput image. The block takes two arguments, the optional `FaceStylizerResult` that contains
 * the zero-copied stylized image if face stylization was successful and an optional error populated
 * upon failure. The lifetime of the stylized image is only guaranteed for the duration of the
 * block.
 */
- (void)stylizeImage:(MPPImage *)image
    withCompletionHandler:(void (^)(MPPFaceStylizerResult *_Nullable result,
                                    NSError *_Nullable error))completionHandler
    NS_SWIFT_NAME(stylize(image:completion:));

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
