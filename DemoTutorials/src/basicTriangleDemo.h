#pragma once

#include"demoBase.h"

class BasicTriangle : public DemoBase
{
public:
    BasicTriangle();
    void init() override;
    void draw() override;
    std::string getInstructions() const override;

private:

};