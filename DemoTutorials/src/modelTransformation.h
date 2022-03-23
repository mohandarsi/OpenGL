#pragma once

#include"demoBase.h"

class ModelTransformation : public DemoBase
{
public:
    ModelTransformation();
    void init() override;
    void draw() override;
    void onKeyPressed(const int& key, const int& scancode, const int& action, const int& mods) override;
    void onViewportSizeChanged(const int& width, const int& height) override;

private:
   glm::vec2 m_viewportSize;
   bool m_startRotation = false;
   bool m_clone = false;
};