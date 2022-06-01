#pragma once

#include"demoBase.h"

class OrthographicProjectionNDC : public DemoBase
{
public:
    OrthographicProjectionNDC();
    void init() override;
    void draw() override;
    std::string getInstructions() const override;
    void onKeyPressed(const int& key, const int& scancode, const int& action, const int& mods) override;

private:
   glm::mat4 m_mvp; 
};