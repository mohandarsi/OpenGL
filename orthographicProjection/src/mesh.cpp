#include "mesh.h"

// Creates an empty mesh object
Mesh::Mesh()
{
    constexpr GLsizei noOfVertexArray = 1;
	glGenVertexArrays(noOfVertexArray, &m_vao);
    
    constexpr GLsizei noOfVertexBuffers = 1;
	glGenBuffers(noOfVertexBuffers, &m_vboVerts);

	// Configure shader attributes
	glBindVertexArray(m_vao); // Bind vao

	// Vertices
	glBindBuffer(GL_ARRAY_BUFFER, m_vboVerts); // Bind vbo
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); // Configure vertex attribute
	glEnableVertexAttribArray(0); // Enable vertex attribute 0 to be used by vertex shader

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind vbo
	glBindVertexArray(0); // Unbind vao
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vboVerts);
}

void Mesh::SetVertices(const std::vector<glm::vec3>& verts)
{
	this->m_vertices = verts;

	glBindBuffer(GL_ARRAY_BUFFER, m_vboVerts); // Bind vbo
	glBufferData(GL_ARRAY_BUFFER, this->m_vertices.size() * sizeof(glm::vec3), &this->m_vertices[0], GL_STATIC_DRAW); // Set the vertices that vbo should use
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind vbo
}

void Mesh::Draw()
{
	glBindVertexArray(m_vao); // Bind vao so it can be drawn
	glDrawArrays(drawMode, 0, m_vertices.size()); // Draw using vertices
	glBindVertexArray(0); // Unbind vao after it has finished drawing
}