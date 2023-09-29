#include "pmRect.h"

void pmRect::setup() {

}

void pmRect::beforeRender() {

}

void pmRect::update() {

}

void pmRect::draw() {
  float w = ofGetWidth();
  float h = ofGetHeight();

  ofNoFill();
  ofSetColor(ofColor::fromHsb(80, 160, 160));
  ofSetLineWidth(4);

  ofDrawRectangle(0.2 * w, 0.2 * h, 0.6 * w, 0.6 * h);
  ofFill();
}

void pmRect::receiveOscMessage(ofxOscMessage m) {

}

