#include "pmFadingLines.h"


void pmFadingLines::setup() {
  maxPoints = 100;
  bgColor = ofColor::fromHsb(0, 0, 20);
  fgColor = ofColor::fromHsb(0, 0, 255);
  spread = ofVec2f(0.01, 0.02);
  speed = 0.1;
};

void pmFadingLines::update() {
  int frameDiv = static_cast<int>(1 / speed);
  if (ofGetFrameNum() % (frameDiv) != 0) {
    return;
  }

  float w = ofGetWidth();
  float h = ofGetHeight();
  auto bounds = ofRectangle(
      0.1 * w,
      0.1 * h,
      0.8 * w,
      0.8 * h
  );
  ofVec2f spreadAbs = ofVec2f(
    spread.x * ofGetWidth(),
    spread.y * ofGetHeight()
  );

  ofPoint pt = ofPoint(ofRandom(0, 1), ofRandom(0, 1));
  ofPoint prevPointAbs;

  if (points.empty()) {
    prevPointAbs = ofPoint(
      ofRandom(0, 1) * bounds.getWidth(),
      ofRandom(0, 1) * bounds.getHeight()
    );
    points.push_back(prevPointAbs);
  }

  if (pt.x < 1e-10 && pt.y < 1e-10) return;

  if (!points.empty()) {
    prevPointAbs = points.back();
  }

  auto pointBounds = ofRectangle(
    fmax(bounds.getLeft(), prevPointAbs.x - 0.5 * spreadAbs.x),
    fmax(bounds.getTop(), prevPointAbs.y - 0.5 * spreadAbs.y),
    fmin(bounds.getRight() - prevPointAbs.x, spreadAbs.x),
    fmin(bounds.getBottom() - prevPointAbs.y, spreadAbs.y)
  );

  auto pointAbs = ofPoint(
    ofLerp(pointBounds.getLeft(), pointBounds.getRight(), pt.x),
    ofLerp(pointBounds.getBottom(), pointBounds.getTop(), pt.y)
  );

  while (points.size() >= maxPoints) {
    points.pop_front();
  }

  points.push_back(pointAbs);
};

void pmFadingLines::draw() {
  // ofBackground(bgColor);
  ofPoint prevPointAbs;

  bool hasFirstPoint = false;
  for (auto pointAbs : points) {
    if (!hasFirstPoint) {
      hasFirstPoint = true;
      prevPointAbs = pointAbs;
      continue;
    }

    ofSetColor(fgColor);
    ofSetLineWidth(1.5);

    ofDrawLine(prevPointAbs, pointAbs);

    prevPointAbs = pointAbs;
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

  if (m.getAddress() == "/fadingLines/spread") {
    spread = ofVec2f(
      ofClamp(m.getArgAsFloat(0), 0, 1),
      ofClamp(m.getArgAsFloat(1), 0, 1)
    );
  }

  if (m.getAddress() == "/fadingLines/speed") {
    speed = ofClamp(m.getArgAsFloat(0), 0, 1);
  }
}
