#include "mesh.h"

// Creates an empty mesh object
Mesh::Mesh()
{
    constexpr GLsizei noOfVertexArray = 1;
	glGenVertexArrays(noOfVertexArray, &m_vao);
    
    constexpr GLsizei noOfVertexBuffers = 1;
	glGenBuffers(noOfVertexBuffers, &m_vboVerts);

	glGenBuffers(noOfVertexBuffers, &m_vboColors);

	// Configure shader attributes
	glBindVertexArray(m_vao); // Bind vao

	// Vertices
	glBindBuffer(GL_ARRAY_BUFFER, m_vboVerts); // Bind vbo
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); // Configure vertex attribute
	glEnableVertexAttribArray(0); // Enable vertex attribute 0 to be used by vertex shader

	//Color
	glBindBuffer(GL_ARRAY_BUFFER, m_vboColors); // Bind vbo
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0); 
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind vbo
	glBindBuffer(GL_ARRAY_BUFFER, 1); // Unbind vbo
	glBindVertexArray(0); // Unbind vao
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vboVerts);
	glDeleteBuffers(1, &m_vboColors);
}

void Mesh::SetVertices(const std::vector<glm::vec3>& verts)
{
	this->m_vertices = verts;

	glBindBuffer(GL_ARRAY_BUFFER, m_vboVerts); // Bind vbo
	glBufferData(GL_ARRAY_BUFFER, this->m_vertices.size() * sizeof(glm::vec3), &this->m_vertices[0], GL_STATIC_DRAW); // Set the vertices that vbo should use
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind vbo
}

void Mesh::SetColors(const std::vector<glm::vec4>& colors)
{
	   // If the color array does not have the same size as
    // the vertices array
    if (m_vertices.size() != m_colors.size()) {
        // Create the color array with the same size
        m_colors = std::vector<glm::vec4>(m_vertices.size());
    }

    for (size_t v=0; v<m_colors.size(); v++) {
        m_colors[v] = colors[v];
    }

	glBindBuffer(GL_ARRAY_BUFFER, m_vboColors); // Bind vbo
	glBufferData(GL_ARRAY_BUFFER, m_colors.size() * sizeof(glm::vec4), &this->m_colors[0], GL_STREAM_DRAW ); // Set the vertices that vbo should use
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind vbo
}

void Mesh::SetColor(const glm::vec4& color)
{
	   // If the color array does not have the same size as
    // the vertices array
    if (m_vertices.size() != m_colors.size()) {
        // Create the color array with the same size
        m_colors = std::vector<glm::vec4>(m_vertices.size(),color);
    }
	else{
		for (size_t v=0; v<m_colors.size(); v++) {
			m_colors[v] = color;
		}
	}

	
	glBindBuffer(GL_ARRAY_BUFFER, m_vboColors); // Bind vbo
	glBufferData(GL_ARRAY_BUFFER, m_colors.size() * sizeof(glm::vec4), &this->m_colors[0], GL_STREAM_DRAW ); // Set the vertices that vbo should use
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind vbo

}

void Mesh::Draw()
{
	glBindVertexArray(m_vao); // Bind vao so it can be drawn
	glDrawArrays(drawMode, 0, m_vertices.size()); // Draw using vertices
	glBindVertexArray(0); // Unbind vao after it has finished drawing
}