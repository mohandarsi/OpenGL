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
	void SetVertices(std::vector<glm::vec3>& verts);
	void Draw();

private:
	std::vector<glm::vec3> m_vertices;
	GLuint m_vao, m_vboVerts;
};