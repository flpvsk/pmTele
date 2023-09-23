#pragma once

#include "ofMain.h"
#include "pmView.h"

class pmFadingLines: public pmView {
  private:
    deque<ofPoint> points;
    int maxPoints;

  public:
    void setup() override;
    void update() override;
    void draw() override;
};
