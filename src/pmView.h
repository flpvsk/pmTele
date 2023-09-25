#pragma once
#include "ofxOsc.h"

class pmView {
  public:
    virtual ~pmView() {}
    virtual void setup() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void receiveOscMessage(ofxOscMessage m) = 0;
};
