// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SHELL_PLATFORM_IOS_FRAMEWORK_SOURCE_SEMANTICS_OBJECT_TEST_MOCKS_H_
#define SHELL_PLATFORM_IOS_FRAMEWORK_SOURCE_SEMANTICS_OBJECT_TEST_MOCKS_H_

#import "flutter/shell/platform/darwin/ios/framework/Source/SemanticsObject.h"

const CGRect kScreenSize = CGRectMake(0, 0, 600, 800);

namespace flutter {
namespace testing {

class SemanticsActionObservation {
 public:
  SemanticsActionObservation(int32_t observed_id, SemanticsAction observed_action)
      : id(observed_id), action(observed_action) {}

  int32_t id;
  SemanticsAction action;
};

class MockAccessibilityBridge : public AccessibilityBridgeIos {
 public:
  MockAccessibilityBridge() : observations({}) {
    view_ = [[UIView alloc] initWithFrame:kScreenSize];
    window_ = [[UIWindow alloc] initWithFrame:kScreenSize];
    [window_ addSubview:view_];
  }
  bool isVoiceOverRunning() const override { return isVoiceOverRunningValue; }
  UIView* view() const override { return view_; }
  UIView<UITextInput>* textInputView() override { return nil; }
  void DispatchSemanticsAction(int32_t id, SemanticsAction action) override {
    SemanticsActionObservation observation(id, action);
    observations.push_back(observation);
  }
  void DispatchSemanticsAction(int32_t id,
                               SemanticsAction action,
                               fml::MallocMapping args) override {
    SemanticsActionObservation observation(id, action);
    observations.push_back(observation);
  }
  void AccessibilityObjectDidBecomeFocused(int32_t id) override {}
  void AccessibilityObjectDidLoseFocus(int32_t id) override {}
  std::shared_ptr<FlutterPlatformViewsController> GetPlatformViewsController() const override {
    return nil;
  }
  std::vector<SemanticsActionObservation> observations;
  bool isVoiceOverRunningValue;

 private:
  UIView* view_;
  UIWindow* window_;
};

class MockAccessibilityBridgeNoWindow : public AccessibilityBridgeIos {
 public:
  MockAccessibilityBridgeNoWindow() : observations({}) {
    view_ = [[UIView alloc] initWithFrame:kScreenSize];
  }
  bool isVoiceOverRunning() const override { return isVoiceOverRunningValue; }
  UIView* view() const override { return view_; }
  UIView<UITextInput>* textInputView() override { return nil; }
  void DispatchSemanticsAction(int32_t id, SemanticsAction action) override {
    SemanticsActionObservation observation(id, action);
    observations.push_back(observation);
  }
  void DispatchSemanticsAction(int32_t id,
                               SemanticsAction action,
                               fml::MallocMapping args) override {
    SemanticsActionObservation observation(id, action);
    observations.push_back(observation);
  }
  void AccessibilityObjectDidBecomeFocused(int32_t id) override {}
  void AccessibilityObjectDidLoseFocus(int32_t id) override {}
  std::shared_ptr<FlutterPlatformViewsController> GetPlatformViewsController() const override {
    return nil;
  }
  std::vector<SemanticsActionObservation> observations;
  bool isVoiceOverRunningValue;

 private:
  UIView* view_;
};
}  // namespace testing
}  // namespace flutter

@interface SemanticsObject (Tests)
- (BOOL)accessibilityScrollToVisible;
- (BOOL)accessibilityScrollToVisibleWithChild:(id)child;
- (id)_accessibilityHitTest:(CGPoint)point withEvent:(UIEvent*)event;
@end

#endif  // SHELL_PLATFORM_IOS_FRAMEWORK_SOURCE_SEMANTICS_OBJECT_TEST_MOCKS_H_
