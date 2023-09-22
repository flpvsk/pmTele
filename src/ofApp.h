#pragma once

#include <memory>
#include "ofMain.h"
#include "pmLogoFeedback.h"
#include "pmWaveFeedback.h"

class ofApp : public ofBaseApp{
  private:
    int currentApp;
    std::array<unique_ptr<ofBaseApp>, 2> apps = {
      std::unique_ptr<ofBaseApp>(new pmLogoFeedback()),
      std::unique_ptr<ofBaseApp>(new pmWaveFeedback()),
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
