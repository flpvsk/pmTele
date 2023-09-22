#include "pmWaveFeedback.h"

float sx=4.95;
float dc=1;
float fv=1;

//--------------------------------------------------------------
void pmWaveFeedback::setup() {
  shader_Feedback.load("shadersGL2/shader_feedback");
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
  shader_Feedback.begin();

  framebuffer1.draw(0,0);

  sx = 2.5 + 1 * sin(sin(ofGetElapsedTimef()/9));
  shader_Feedback.setUniform1f("mixxx",sx);

  ofVec2f feedback_Displace;
  dc = 0.5 + 0.5 * sin(ofGetElapsedTimef()/8);
  fv = 0.5 * sin(ofGetElapsedTimef()/20);
  feedback_Displace.set(dc, fv);
  shader_Feedback.setUniform2f("feedback_Displace",feedback_Displace);

  shader_Feedback.end();

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
}
