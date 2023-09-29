#pragma once

#include <memory>
#include "ofMain.h"
#include "pmView.h"

class pmFeedbackShaderWrapper: public pmView {
  private:
    ofShader feedbackShader;
    ofFbo framebuffer0;
    ofFbo framebuffer1;
    ofFbo framebuffer2;

    unique_ptr<pmView> view;
    ofVboMesh mesh;

    ofColor bgColor;

    ofTexture img;

  public:
    pmFeedbackShaderWrapper(unique_ptr<pmView>);
    void setup() override;
    void update() override;
    void draw() override;
    void receiveOscMessage(ofxOscMessage m) override;
};
