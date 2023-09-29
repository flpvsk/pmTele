#pragma once

#include <algorithm>
#include "ofMain.h"
#include "pmView.h"

class pmFadingLines: public pmView {
  private:
    deque<ofPoint> points;
    int maxPoints;
    ofColor bgColor;
    ofColor fgColor;
    ofVec2f spread;
    float speed;

  public:
    void setup() override;
    void update() override;
    void beforeRender() override;
    void draw() override;
    void receiveOscMessage(ofxOscMessage m) override;
};
