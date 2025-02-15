// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef FLUTTER_IMPELLER_PLAYGROUND_PLAYGROUND_IMPL_H_
#define FLUTTER_IMPELLER_PLAYGROUND_PLAYGROUND_IMPL_H_

#include <memory>

#include "flutter/fml/macros.h"
#include "impeller/playground/playground.h"
#include "impeller/playground/switches.h"
#include "impeller/renderer/context.h"
#include "impeller/renderer/surface.h"

namespace impeller {

class PlaygroundImpl {
 public:
  static std::unique_ptr<PlaygroundImpl> Create(PlaygroundBackend backend,
                                                PlaygroundSwitches switches);

  virtual ~PlaygroundImpl();

  using WindowHandle = void*;

  virtual WindowHandle GetWindowHandle() const = 0;

  virtual std::shared_ptr<Context> GetContext() const = 0;

  virtual std::unique_ptr<Surface> AcquireSurfaceFrame(
      std::shared_ptr<Context> context) = 0;

  Vector2 GetContentScale() const;

 protected:
  const PlaygroundSwitches switches_;

  explicit PlaygroundImpl(PlaygroundSwitches switches);

 private:
  PlaygroundImpl(const PlaygroundImpl&) = delete;

  PlaygroundImpl& operator=(const PlaygroundImpl&) = delete;
};

}  // namespace impeller

#endif  // FLUTTER_IMPELLER_PLAYGROUND_PLAYGROUND_IMPL_H_
