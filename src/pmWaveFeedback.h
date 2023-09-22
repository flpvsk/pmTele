#pragma once

#include "ofMain.h"

class pmWaveFeedback: public ofBaseApp {

	public:
		void setup();
		void update();
		void draw();

    ofShader shader_Feedback;
    ofFbo framebuffer0;
    ofFbo framebuffer1;
};
