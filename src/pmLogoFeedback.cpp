#include "pmLogoFeedback.h"

ofRectangle getBitmapStringBoundingBox(string text) {
  vector<string> lines = ofSplitString(text, "\n");
  int maxLineLength = 0;
  for(int i = 0; i < (int)lines.size(); i++) {
    // tabs are not rendered
    const string & line(lines[i]);
    int currentLineLength = 0;
    for(int j = 0; j < (int)line.size(); j++) {
      if (line[j] == '\t') {
        currentLineLength += 8 - (currentLineLength % 8);
      } else {
        currentLineLength++;
      }
    }
    maxLineLength = MAX(maxLineLength, currentLineLength);
  }

  int fontSize = 8;
  float leading = 1.7;
  int height = lines.size() * fontSize * leading - 1;
  int width = maxLineLength * fontSize;

  return ofRectangle(0,0,width, height);
}


void pmLogoFeedback::setup() {
  bgColor = ofColor::fromHsb(0, 0, 20);
  fgColor = ofColor::fromHsb(0, 0, 255);
  scale = 1;

  ofLoadImage(logo, "img/perry-color-small.png");
  logo.setTextureWrap(GL_REPEAT, GL_REPEAT);

  traceShapeShader.load(
    "shadersGL2/generic.vert",
    "shadersGL2/traceShape.frag"
  );

  mesh = ofMesh::plane(ofGetWidth(), ofGetHeight());

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
}

void pmLogoFeedback::beforeRender() {
  fgColor = ofColor::fromHsb(
    ofRandom(0, 360),
    ofRandom(100, 255),
    ofRandom(100, 255)
  );
  scale = ofRandom(0.001, 1);
}

void pmLogoFeedback::update() {

}

void pmLogoFeedback::draw() {
  float width = ofGetWidth();
  float height = ofGetHeight();
  ofPoint center = ofPoint(width, height) * 0.5;

  ofPushMatrix();
  ofTranslate(center);

  traceShapeShader.begin();

  traceShapeShader.setUniformTexture("u_tex0", logo, 0);
  traceShapeShader.setUniform2f(
    "u_tex0Resolution",
    logo.getWidth(),
    logo.getHeight()
  );

  traceShapeShader.setUniform2f("u_resolution", ofVec2f(
    width,
    height
  ));

  traceShapeShader.setUniform2f("u_offset", offset);
  traceShapeShader.setUniform1f("u_scale", scale);

  traceShapeShader.setUniform3f(
    "u_color",
    fgColor.r / 255.,
    fgColor.g / 255.,
    fgColor.b / 255.
  );

  // ofScale(width * 0.5, height * 0.5, 1);
  mesh.draw();

  traceShapeShader.end();
  ofPopMatrix();
}

void pmLogoFeedback::receiveOscMessage(ofxOscMessage m) {
  if (m.getAddress() == "/color/fg/hsb") {
    fgColor = ofColor::fromHsb(
      255 * m.getArgAsFloat(0),
      255 * m.getArgAsFloat(1),
      255 * m.getArgAsFloat(2)
    ).clamp();
  }

  if (m.getAddress() == "/logoFeedback/scale") {
    scale = ofClamp(m.getArgAsFloat(0), 0, 1);
  }

  if (m.getAddress() == "/logoFeedback/offset") {
    offset = ofVec2f(
      ofClamp(m.getArgAsFloat(0), 0, 1),
      ofClamp(m.getArgAsFloat(0), 0, 1)
    );
  }
}
