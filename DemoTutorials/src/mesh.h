#pragma once

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

class Mesh
{
public:
	GLenum drawMode = GL_TRIANGLES;
	Mesh();
	~Mesh();
	void SetVertices(const std::vector<glm::vec3>& verts);
	void SetColors(const std::vector<glm::vec4>& colors);
	void SetColor(const glm::vec4& color);
	void Draw();

private:
	std::vector<glm::vec3> m_vertices;
    std::vector<glm::vec4> m_colors;
	GLuint m_vao, m_vboVerts,m_vboColors;
};