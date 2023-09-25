#pragma once

#include "ofMain.h"
#include "pmView.h"

class pmWaveFeedback: public pmView {
  private:
    ofShader waveFeedbackShader;
    ofFbo framebuffer0;
    ofFbo framebuffer1;

	public:
		void setup() override;
		void update() override;
		void draw() override;
    void receiveOscMessage(ofxOscMessage m) override;
};
