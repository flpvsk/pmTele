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

    float scale;
    ofVec2f offset;

  public:
    void setup() override;
    void update() override;
    void beforeRender() override;
    void draw() override;
    void receiveOscMessage(ofxOscMessage m) override;
};
