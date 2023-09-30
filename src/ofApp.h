#pragma once

#include <memory>
#include "ofMain.h"
#include "pmView.h"
#include "pmLogoFeedback.h"
#include "pmWaveFeedback.h"
#include "pmFadingLines.h"
#include "pmFeedbackShaderWrapper.h"
#include "pmRect.h"

#include "ofxOsc.h"

// listening port
#define OSC_PORT 8000

class ofApp : public ofBaseApp{
  private:
    ofColor bgColor;

    ofShader transitionShader;
    ofFbo framebuffer0;
    ofFbo framebuffer1;

    ofxOscReceiver receiver;
    int viewDurationSec{8};
    float transitionDurationSec{4};
    float transitionPosition;

    int currentApp;
    std::array<unique_ptr<pmView>, 4> apps = {
      unique_ptr<pmLogoFeedback>(new pmLogoFeedback()),
      unique_ptr<pmFeedbackShaderWrapper>(new pmFeedbackShaderWrapper(
        unique_ptr<pmLogoFeedback>(new pmLogoFeedback())
      )),
      unique_ptr<pmFeedbackShaderWrapper>(new pmFeedbackShaderWrapper(
        unique_ptr<pmFadingLines>(new pmFadingLines())
      )),
      unique_ptr<pmFadingLines>(new pmFadingLines()),
    };

  public:
    void setup() override;
    void update() override;
    void draw() override;
    void exit() override;

    void keyPressed(int key) override;
    void keyReleased(int key) override;
    void mouseMoved(int x, int y ) override;
    void mouseDragged(int x, int y, int button) override;
    void mousePressed(int x, int y, int button) override;
    void mouseReleased(int x, int y, int button) override;
    void mouseScrolled(int x, int y, float scrollX, float scrollY) override;
    void mouseEntered(int x, int y) override;
    void mouseExited(int x, int y) override;
    void windowResized(int w, int h) override;
    void dragEvent(ofDragInfo dragInfo) override;
    void gotMessage(ofMessage msg) override;

};
