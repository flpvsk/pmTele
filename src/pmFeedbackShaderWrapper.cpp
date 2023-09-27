#include "pmFeedbackShaderWrapper.h"

pmFeedbackShaderWrapper::pmFeedbackShaderWrapper(unique_ptr<pmView> v): view{std::move(v)} {}

void pmFeedbackShaderWrapper::setup() {
  bgColor = ofColor::fromHsb(0, 0, 20);

  feedbackShader.load(
    "shadersGL2/generic.vert",
    "shadersGL2/feedback.frag"
  );

  ofDisableArbTex();
  framebuffer0.allocate(ofGetWidth(), ofGetHeight());
  framebuffer1.allocate(ofGetWidth(), ofGetHeight());
  framebuffer2.allocate(ofGetWidth(), ofGetHeight());

  framebuffer0.begin();
  ofClear(bgColor.r, bgColor.g, bgColor.b, 255);
  framebuffer0.end();

  framebuffer1.begin();
  ofClear(bgColor.r, bgColor.g, bgColor.b, 255);
  framebuffer1.end();

  framebuffer2.begin();
  ofClear(bgColor.r, bgColor.g, bgColor.b, 255);
  framebuffer2.end();

  mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
  mesh.addVertex(ofPoint(-1.,-1));
  mesh.addTexCoord(ofVec2f(0.,1.));
  mesh.addColor(ofFloatColor(1.));
  mesh.addVertex(ofPoint(-1.,1));
  mesh.addTexCoord(ofVec2f(0.,0.));
  mesh.addColor(ofFloatColor(1.));
  mesh.addVertex(ofPoint(1.,1));
  mesh.addTexCoord(ofVec2f(1.,0.));
  mesh.addColor(ofFloatColor(1.));
  mesh.addVertex(ofPoint(1.,-1));
  mesh.addTexCoord(ofVec2f(1.,1.));
  mesh.addColor(ofFloatColor(1.));

  view->setup();
};

void pmFeedbackShaderWrapper::update() {
  view->update();
};

void pmFeedbackShaderWrapper::draw() {
  float w = ofGetWidth();
  float h = ofGetHeight();

  framebuffer1.begin();
  this->view->draw();
  framebuffer1.end();

  framebuffer0.begin();
  ofPoint center = ofPoint(w, h) * 0.5;

  ofPushMatrix();
  ofTranslate(center);

  feedbackShader.begin();

  auto fbTex = framebuffer2.getTexture();
  fbTex.setTextureWrap(GL_REPEAT, GL_REPEAT);

  feedbackShader.setUniformTexture(
    "u_tex0", fbTex, 0
  );
  feedbackShader.setUniform2f(
    "u_tex0Resolution", w, h
  );

  feedbackShader.setUniformTexture(
    "u_tex1",
    framebuffer1.getTexture(),
    0
  );
  feedbackShader.setUniform2f(
    "u_tex1Resolution", w, h
  );

  feedbackShader.setUniform2f(
    "u_resolution", w, h
  );

  ofVec2f uDisplace = ofVec2f(
    ofGetElapsedTimef() / 2,
    0
  );

  feedbackShader.setUniform2f(
    "u_displace",
    uDisplace
  );

  feedbackShader.setUniform1f(
    "u_time", ofGetElapsedTimef()
  );

  ofScale(w * 0.5, h * 0.5, 1);
  mesh.draw();
  feedbackShader.end();
  ofPopMatrix();
  framebuffer0.end();

  framebuffer0.draw(0,0);

  framebuffer2.begin();
  framebuffer0.draw(0,0);
  framebuffer2.end();
};

void pmFeedbackShaderWrapper::receiveOscMessage(ofxOscMessage m) {
  view->receiveOscMessage(m);

  if (m.getAddress() == "/color/bg/hsb") {
    bgColor = ofColor::fromHsb(
      255 * m.getArgAsFloat(0),
      255 * m.getArgAsFloat(1),
      255 * m.getArgAsFloat(2)
    ).clamp();
  }
};
