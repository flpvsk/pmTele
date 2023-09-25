#pragma once

#include "ofMain.h"
#include "pmView.h"

class pmLogoFeedback: public pmView {
  public:
    void setup() override;
    void update() override;
    void draw() override;
    void receiveOscMessage(ofxOscMessage m) override;
};
