#include "pmWaveFeedback.h"

float sx=4.95;
float dc=1;
float fv=1;

//--------------------------------------------------------------
void pmWaveFeedback::setup() {
  waveFeedbackShader.load("shadersGL2/waveFeedback");
  framebuffer0.allocate(ofGetWidth(), ofGetHeight());
  framebuffer1.allocate(ofGetWidth(), ofGetHeight());

  framebuffer0.begin();
  ofClear(0, 0, 0, 255);
  framebuffer0.end();

  framebuffer1.begin();
  ofClear(0, 0, 0, 255);
  framebuffer1.end();
}

//--------------------------------------------------------------
void pmWaveFeedback::update() {

}

//--------------------------------------------------------------
void pmWaveFeedback::draw() {
  ofSetColor(
    ofColor::fromHsb(0, 0, 255)
  );

  framebuffer0.begin();
  waveFeedbackShader.begin();

  framebuffer1.draw(0,0);

  sx = 3.9 + 1 * sin(sin(ofGetElapsedTimef()/9));
  waveFeedbackShader.setUniform1f("mixxx",sx);

  ofVec2f feedback_Displace;
  dc = 0.5 + 0.5 * sin(ofGetElapsedTimef()/8);
  fv = 0.0;
  feedback_Displace.set(dc, fv);
  waveFeedbackShader.setUniform2f(
    "feedback_Displace",
    feedback_Displace
  );

  waveFeedbackShader.end();

  float r = 2;
  ofSetColor(
    ofColor::fromHsb(
      0, 0, 245 + 10 * sin(ofGetElapsedTimef()/8), 255)
  );
  ofDrawCircle(
    ofGetWidth() - r,
    r + (ofGetHeight() - 20) * (
      sin(sx * sin(ofGetElapsedTimef()/2)) * 0.5 + 0.5
    ),
    0,
    r
  );


  framebuffer0.end();

  framebuffer0.draw(0,0);

  framebuffer1.begin();
  framebuffer0.draw(0,0);
  framebuffer1.end();

  ofDrawBitmapString((
    " sx = "+ofToString(floor(sx * 100) / 100) +
    ", dc = "+ofToString(floor(dc * 100) / 100) +
    ", fv = "+ofToString(floor(fv * 100) / 100)
  ), 10, ofGetHeight() - 5);
}


void pmWaveFeedback::receiveOscMessage(ofxOscMessage m) {

}
