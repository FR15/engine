// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

import 'package:test/bootstrap/browser.dart';
import 'package:test/test.dart';
import 'package:ui/src/engine.dart';
import 'package:ui/ui.dart' as ui;

import '../common/matchers.dart';
import 'common.dart';

void main() {
  internalBootstrapBrowserTest(() => testMain);
}

void testMain() {
  group('CanvasKit', () {
    setUpCanvasKitTest();

    late LayerScene scene;

    setUp(() {
      // Create a scene to use in tests.
      final CkPicture picture =
          paintPicture(const ui.Rect.fromLTRB(0, 0, 60, 60), (CkCanvas canvas) {
        canvas.drawRect(const ui.Rect.fromLTRB(0, 0, 60, 60),
            CkPaint()..style = ui.PaintingStyle.fill);
      });
      final LayerSceneBuilder sb = LayerSceneBuilder();
      sb.addPicture(ui.Offset.zero, picture);
      scene = sb.build();
    });

    test('can render into arbitrary views', () async {
      CanvasKitRenderer.instance.renderScene(scene, implicitView);

      final EngineFlutterView anotherView = EngineFlutterView(
          EnginePlatformDispatcher.instance, createDomElement('another-view'));
      EnginePlatformDispatcher.instance.viewManager.registerView(anotherView);

      CanvasKitRenderer.instance.renderScene(scene, anotherView);
    });

    test('will error if trying to render into an unregistered view', () async {
      final EngineFlutterView unregisteredView = EngineFlutterView(
          EnginePlatformDispatcher.instance,
          createDomElement('unregistered-view'));
      expect(
        () => CanvasKitRenderer.instance.renderScene(scene, unregisteredView),
        throwsAssertionError,
      );
    });

    test('will dispose the Rasterizer for a disposed view', () async {
      final EngineFlutterView view = EngineFlutterView(
          EnginePlatformDispatcher.instance, createDomElement('multi-view'));
      EnginePlatformDispatcher.instance.viewManager.registerView(view);
      expect(
        CanvasKitRenderer.instance.debugGetRasterizerForView(view),
        isNotNull,
      );

      EnginePlatformDispatcher.instance.viewManager
          .disposeAndUnregisterView(view.viewId);
      expect(
        CanvasKitRenderer.instance.debugGetRasterizerForView(view),
        isNull,
      );
    });
  });
}
