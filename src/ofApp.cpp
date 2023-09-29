#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
  ofLog() << "listening for osc messages on port " << OSC_PORT;
  receiver.setup(OSC_PORT);

  ofSetVerticalSync(true);
  ofSetFrameRate(60);
  ofDisableAntiAliasing();
  ofDisableSmoothing();
  ofDisableArbTex();
  ofEnableAlphaBlending();

  bgColor = ofColor::fromHsb(0, 0, 20);
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

  auto seconds = ofGetElapsedTimeMillis() / 1000;
  currentApp = fmod(floor(seconds / 4), apps.size());
  auto &&app = apps[currentApp];
  app->update();
}

//--------------------------------------------------------------
void ofApp::draw() {
  ofBackground(bgColor);
  auto &&app = apps[currentApp];
  app->draw();
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
