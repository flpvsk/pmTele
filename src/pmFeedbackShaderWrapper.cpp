#include "pmFeedbackShaderWrapper.h"

pmFeedbackShaderWrapper::pmFeedbackShaderWrapper(unique_ptr<pmView> v): view{std::move(v)} {}

void pmFeedbackShaderWrapper::beforeRender() {
  this->view->beforeRender();
}


void pmFeedbackShaderWrapper::setup() {
  float w = ofGetWidth();
  float h = ofGetHeight();

  feedbackShader.load(
    "shadersGL2/generic.vert",
    "shadersGL2/feedback.frag"
  );

  framebuffer0.allocate(w, h);
  framebuffer1.allocate(w, h);
  framebuffer2.allocate(w, h);

  framebuffer0.begin();
  ofClear(0, 0, 0, 0);
  framebuffer0.end();

  framebuffer1.begin();
  ofClear(0, 0, 0, 0);
  framebuffer1.end();

  framebuffer2.begin();
  ofClear(0, 0, 0, 0);
  framebuffer2.end();

  view->setup();
};

void pmFeedbackShaderWrapper::update() {
  view->update();
};

void pmFeedbackShaderWrapper::draw() {
  float w = ofGetWidth();
  float h = ofGetHeight();

  framebuffer0.begin();
    feedbackShader.begin();
      framebuffer1.draw(0, 0);

      feedbackShader.setUniformTexture(
        "tex1", framebuffer2.getTexture(), 1
      );

      feedbackShader.setUniform2f(
        "u_resolution", w, h
      );

      feedbackShader.setUniform1f(
        "u_time", ofGetElapsedTimef()
      );
    feedbackShader.end();
  framebuffer0.end();

  framebuffer0.draw(0, 0);

  framebuffer1.begin();
    ofClear(0, 0, 0, 0);
    framebuffer0.draw(0,0);
  framebuffer1.end();

  framebuffer2.begin();
    ofClear(0, 0, 0, 0);
    this->view->draw();
  framebuffer2.end();
};

void pmFeedbackShaderWrapper::receiveOscMessage(ofxOscMessage m) {
  view->receiveOscMessage(m);
};
