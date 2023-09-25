#include "pmFadingLines.h"


void pmFadingLines::setup() {
  maxPoints = 400;
  bgColor = ofColor::fromHsb(0, 0, 20);
  fgColor = ofColor::fromHsb(0, 0, 255);
};

void pmFadingLines::update() {
  if (ofGetFrameNum() % 10 != 0) {
    return;
  }

  ofPoint pt = ofPoint(ofRandom(0, 1), ofRandom(0, 1));

  if (
    !points.empty() &&
    points.back().x == pt.x &&
    points.back().y == pt.y
  ) {
    return;
  }

  while (points.size() >= maxPoints) {
    points.pop_front();
  }

  points.push_back(pt);
};

void pmFadingLines::draw() {
  ofBackground(bgColor);
  ofPoint prevPoint;
  bool hasFirstPoint = false;
  auto bounds = ofRectangle(
      0,
      0,
      ofGetWidth(),
      ofGetHeight()
  );

  for (auto point : points) {
    if (!hasFirstPoint) {
      prevPoint = point;
      hasFirstPoint = true;
      continue;
    }
    ofSetColor(fgColor);
    ofSetLineWidth(1.5);

    ofDrawLine(
      ofPoint(
        ofLerp(bounds.getLeft(), bounds.getRight(), prevPoint.x),
        ofLerp(bounds.getBottom(), bounds.getTop(), prevPoint.y)
      ),
      ofPoint(
        ofLerp(bounds.getLeft(), bounds.getRight(), point.x),
        ofLerp(bounds.getBottom(), bounds.getTop(), point.y)
      )
    );

    prevPoint = point;
  }
};

void pmFadingLines::receiveOscMessage(ofxOscMessage m) {
  if (m.getAddress() == "/color/bg/hsb") {
    bgColor = ofColor::fromHsb(
      255 * m.getArgAsFloat(0),
      255 * m.getArgAsFloat(1),
      255 * m.getArgAsFloat(2)
    );
  }

  if (m.getAddress() == "/color/fg/hsb") {
    fgColor = ofColor::fromHsb(
      255 * m.getArgAsFloat(0),
      255 * m.getArgAsFloat(1),
      255 * m.getArgAsFloat(2)
    );
  }
}
