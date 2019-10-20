#pragma once

enum Type {
	Float = 1, Float2 = 2, Float3 = 3, Float4 = 4
};

class Mesh {

private:

	unsigned int vao, vbo, ibo, count;
	unsigned int nextAttrib = 0;

public:

//	explicit Mesh (float vertices[], unsigned verticesCount, int indices[],
//	               unsigned int indicesCount, const std::initializer_list<Type>& types)
//			: vao(0), vbo(0), ibo(0), count(indicesCount) {
	explicit Mesh (std::vector<float> vertices, std::vector<int> indices,
	               const std::initializer_list<Type>& types)
			: vao(0), vbo(0), ibo(0), count(indices.size()) {
		glGenVertexArrays(1, &vao);
		createVBO(&vertices[0], vertices.size(), types);
		createIBO(&indices[0], indices.size());
	}

	void draw () {
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}

	~Mesh () {
		// Destroying IBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &ibo);
		// Destroying VAO and its Attributes
		while (nextAttrib > 0)
			glDisableVertexAttribArray(--nextAttrib);
		glBindVertexArray(0);
		glDeleteVertexArrays(1, &vao);
		// Destroying VBOs
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &vbo);
	}

private:

	void createVBO (float vertices[], unsigned int verticesCount,
	                const std::initializer_list<Type>& types) {
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, verticesCount * 4, vertices, GL_STATIC_DRAW);
		glBindVertexArray(vao);

		int stride = 0;
		for (Type type : types)
			stride += type;
		stride *= 4;

		int offset = 0;
		for (Type type : types) {
			glVertexAttribPointer(nextAttrib, type, GL_FLOAT, false, stride,
			                      (void*) (offset * sizeof(float)));
			glEnableVertexAttribArray(nextAttrib++);
			offset += type;
		}
	}

	void createIBO (int indices[], unsigned int indicesCount) {
		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount * 4, indices, GL_STATIC_DRAW);
	}

};