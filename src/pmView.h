#pragma once

class pmView {
  public:
    virtual ~pmView() {}
    virtual void setup() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
};
