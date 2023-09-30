#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
  ofLog() << "listening for osc messages on port " << OSC_PORT;
  receiver.setup(OSC_PORT);

  ofSetVerticalSync(true);
  ofSetFrameRate(12);
  ofDisableAntiAliasing();
  ofDisableSmoothing();
  ofDisableArbTex();
  ofEnableAlphaBlending();

  bgColor = ofColor::fromHsb(0, 0, 20);

  float w = ofGetWidth();
  float h = ofGetHeight();

  transitionShader.load(
    "shadersGL2/generic.vert",
    "shadersGL2/transition.frag"
  );

  framebuffer0.allocate(w, h);
  framebuffer1.allocate(w, h);

  framebuffer0.begin();
  ofClear(0, 0, 0, 0);
  framebuffer0.end();

  framebuffer1.begin();
  ofClear(0, 0, 0, 0);
  framebuffer1.end();

  for (auto &&app: apps) {
    app->setup();
  }
}

//--------------------------------------------------------------
void ofApp::update() {
  while (receiver.hasWaitingMessages()) {
    ofxOscMessage m;
    receiver.getNextMessage(m);

    if (m.getAddress() == "/color/bg/hsb") {
      bgColor = ofColor::fromHsb(
        255 * m.getArgAsFloat(0),
        255 * m.getArgAsFloat(1),
        255 * m.getArgAsFloat(2)
      ).clamp();
    }

    for (auto &&app: apps) {
      app->receiveOscMessage(m);
    }
  }

  float seconds = static_cast<float>(ofGetElapsedTimeMillis()) / 1000;
  int prevFrameApp = currentApp;
  long appNum = floor(seconds / viewDurationSec);
  currentApp = fmod(appNum, apps.size());
  auto &&app = apps[currentApp];

  transitionPosition = (
    fmin(
      transitionDurationSec,
      (seconds - appNum * viewDurationSec)
    ) / transitionDurationSec
  );

  if (prevFrameApp != currentApp) {
    // app->beforeRender();
  }

  int prevApp = currentApp - 1;
  if (prevApp < 0) prevApp = apps.size() - 1;

  apps[prevApp]->update();
  app->update();
}

//--------------------------------------------------------------
void ofApp::draw() {
  ofBackground(bgColor);
  int prevApp = currentApp - 1;
  if (prevApp < 0) prevApp = apps.size() - 1;

  framebuffer0.begin();
    ofClear(0, 0, 0, 0);
    if ((currentApp % 2) == 0) {
      apps[prevApp]->draw();
    } else {
      apps[currentApp]->draw();
    }
  framebuffer0.end();

  framebuffer1.begin();
    ofClear(0, 0, 0, 0);
    if ((currentApp % 2) == 0) {
      apps[currentApp]->draw();
    } else {
      apps[prevApp]->draw();
    }
  framebuffer1.end();

  transitionShader.begin();
    framebuffer0.draw(0, 0);

    transitionShader.setUniform1i(
      "u_flip", (currentApp % 2)
    );

    transitionShader.setUniformTexture(
      "tex1", framebuffer1.getTexture(), 1
    );

    transitionShader.setUniform2f(
      "u_resolution", ofGetWidth(), ofGetHeight()
    );

    transitionShader.setUniform1f(
      "u_transition", transitionPosition
    );
  transitionShader.end();

  ofDrawBitmapString(
    ofToString(floor(transitionPosition * 100) / 100),
    10,
    ofGetHeight() - 20
  );
}

//--------------------------------------------------------------
void ofApp::exit() {

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
