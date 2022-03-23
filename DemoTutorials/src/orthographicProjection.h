#pragma once

#include"demoBase.h"

class OrthographicProjection : public DemoBase
{
public:
    OrthographicProjection();
    void init() override;
    void draw() override;
    void onKeyPressed(const int& key, const int& scancode, const int& action, const int& mods) override;
    void onViewportSizeChanged(const int& width, const int& height) override;

private:
   glm::vec2 m_viewportSize;
   glm::mat4 m_mvp; 
};