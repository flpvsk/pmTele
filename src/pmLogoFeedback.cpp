#include "pmLogoFeedback.h"

ofRectangle getBitmapStringBoundingBox(string text) {
  vector<string> lines = ofSplitString(text, "\n");
  int maxLineLength = 0;
  for(int i = 0; i < (int)lines.size(); i++) {
    // tabs are not rendered
    const string & line(lines[i]);
    int currentLineLength = 0;
    for(int j = 0; j < (int)line.size(); j++) {
      if (line[j] == '\t') {
        currentLineLength += 8 - (currentLineLength % 8);
      } else {
        currentLineLength++;
      }
    }
    maxLineLength = MAX(maxLineLength, currentLineLength);
  }

  int fontSize = 8;
  float leading = 1.7;
  int height = lines.size() * fontSize * leading - 1;
  int width = maxLineLength * fontSize;

  return ofRectangle(0,0,width, height);
}


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

  auto t = "hello hi hello";
  auto textBounds = getBitmapStringBoundingBox(t);

  ofDrawBitmapString(
    t,
    (ofGetWidth() - textBounds.getWidth()) / 2,
    (ofGetHeight() - textBounds.getHeight()) / 2
  );
}

void pmLogoFeedback::receiveOscMessage(ofxOscMessage m) {

}
