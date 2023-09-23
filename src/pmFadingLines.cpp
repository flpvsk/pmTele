#include "pmFadingLines.h"


void pmFadingLines::setup() {
  maxPoints = 400;
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
    ofSetColor(ofColor::fromHsb(0, 0, 255));
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
