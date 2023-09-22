#include "pmLogoFeedback.h"

void pmLogoFeedback::setup() {

}

void pmLogoFeedback::update() {

}

void pmLogoFeedback::draw() {
  // ofClear(
  //   ofColor::fromHsb(0, 0, 20)
  // );

  // ofBackground(
    // ofColor::fromHsb(0, 0, 20)
  // );

  ofSetColor(
    ofColor::fromHsb(0, 0, 120)
  );

  ofDrawBitmapString(
    "hello",
    ofGetWidth() / 2,
    ofGetHeight() / 2
  );
}

