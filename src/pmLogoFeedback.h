#pragma once

#include "ofMain.h"
#include "pmView.h"

class pmLogoFeedback: public pmView {
  private:
    ofTexture logo;
    ofColor bgColor;
    ofColor fgColor;
    ofShader traceShapeShader;
    ofVboMesh mesh;

  public:
    void setup() override;
    void update() override;
    void draw() override;
    void receiveOscMessage(ofxOscMessage m) override;
};
