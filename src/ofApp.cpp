#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
  ofSetVerticalSync(true);
  ofSetFrameRate(24);
  ofDisableAntiAliasing();
  ofDisableSmoothing();
  ofEnableAlphaBlending();

  ofBackground(0);

  for (auto &&app: apps) {
    app->setup();
  }
}

//--------------------------------------------------------------
void ofApp::update() {
  auto seconds = ofGetElapsedTimeMillis() / 1000;
  currentApp = fmod(floor(seconds / 4), apps.size());
  auto &&app = apps[currentApp];
  app->update();
}

//--------------------------------------------------------------
void ofApp::draw() {
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
