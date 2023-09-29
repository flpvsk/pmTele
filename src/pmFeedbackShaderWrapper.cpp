#include "pmFeedbackShaderWrapper.h"

pmFeedbackShaderWrapper::pmFeedbackShaderWrapper(unique_ptr<pmView> v): view{std::move(v)} {}

void pmFeedbackShaderWrapper::beforeRender() {
  this->view->beforeRender();
}


void pmFeedbackShaderWrapper::setup() {
  bgColor = ofColor::fromHsb(0, 0, 20);
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
  ofClear(0, 0, 0, 255);
  framebuffer0.end();

  framebuffer1.begin();
  ofClear(0, 0, 0, 255);
  framebuffer1.end();

  framebuffer2.begin();
  ofClear(0, 0, 0, 255);
  framebuffer2.end();

  // mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);

  // mesh.addVertex(ofPoint(-1.,-1));
  // mesh.addTexCoord(ofVec2f(0.,1.));
  // mesh.addColor(ofFloatColor(1.));

  // mesh.addVertex(ofPoint(-1.,1));
  // mesh.addTexCoord(ofVec2f(0.,0.));
  // mesh.addColor(ofFloatColor(1.));

  // mesh.addVertex(ofPoint(1.,1));
  // mesh.addTexCoord(ofVec2f(1.,0.));
  // mesh.addColor(ofFloatColor(1.));

  // mesh.addVertex(ofPoint(1.,-1));
  // mesh.addTexCoord(ofVec2f(1.,1.));
  // mesh.addColor(ofFloatColor(1.));

  mesh = ofMesh::plane(w, h);
  view->setup();
};

void pmFeedbackShaderWrapper::update() {
  view->update();
};

void pmFeedbackShaderWrapper::draw() {
  float w = ofGetWidth();
  float h = ofGetHeight();

  framebuffer0.begin();
  ofPoint center = ofPoint(w, h) * 0.5;

  // ofPushMatrix();
  // ofTranslate(center);

  feedbackShader.begin();

  // auto fbTex = framebuffer2.getTexture();
  // fbTex.setTextureWrap(GL_REPEAT, GL_REPEAT);
  framebuffer2.draw(0, 0);

  // auto& tex = framebuffer2.getTexture();
  // feedbackShader.setUniformTexture(
  //   "u_tex0", tex, 0
  // );
  // feedbackShader.setUniform2f(
  //   "u_tex0Resolution", w, h
  // );

  // auto& tex1 = framebuffer1.getTexture();
  // feedbackShader.setUniformTexture(
  //   "u_tex1", tex1, 1
  // );
  // feedbackShader.setUniform2f(
  //   "u_tex1Resolution", w, h
  // );

  feedbackShader.setUniform2f(
    "u_resolution", w, h
  );

  ofVec2f uDisplace = ofVec2f(
    ofGetElapsedTimef() / 2,
    ofGetElapsedTimef() / 4
  );

  feedbackShader.setUniform2f(
    "u_displace",
    uDisplace
  );

  feedbackShader.setUniform1f(
    "u_time", ofGetElapsedTimef()
  );

  // ofScale(w * 0.5, h * 0.5, 1);
  // mesh.draw();
  feedbackShader.end();

  // ofPushMatrix();
  // ofTranslate(0, h);
  // ofScale(1, -1, 1);
  this->view->draw();
  // ofPopMatrix();
  // ofDrawRectangle(0.4 * w, 0.4 * h, 0.2 * w, 0.2 * h);

  // ofPopMatrix();
  framebuffer0.end();

  framebuffer0.draw(0, 0);

  framebuffer2.begin();
  ofClear(0, 0, 0, 0);
  // ofPushMatrix();
  // ofTranslate(center);
  // ofRotateZRad(ofGetElapsedTimef() / 4);
  framebuffer0.draw(0,0);
  // ofPopMatrix();
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
