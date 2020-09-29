#include "Renderers.h"

Shader Renderer::getShader() {
	return this->shader;
}

ObjectRenderer::ObjectRenderer(Shader& shader) {
	this->shader = shader;
	float vertices[] = {
		 //position           //normals          //texture
		 0.5f,  0.0f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
		 0.5f,  0.0f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
		-0.5f,  0.0f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
		-0.5f,  0.0f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f 
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);
	glBindVertexArray(this->VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

ObjectRenderer::~ObjectRenderer() {
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteVertexArrays(1, &this->VBO);
	glDeleteVertexArrays(1, &this->EBO);
}


void ObjectRenderer::drawObject(Texture texture, Texture spec, glm::vec3 position, glm::vec3 size, glm::vec3 rotate, glm::vec3 color) {
	this->shader.use();
	//glUseProgram(this->shader.getID());
	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, position);

	model = glm::rotate(model, glm::radians(rotate.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotate.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotate.z), glm::vec3(0.0f, 0.0f, 1.0f));

	model = glm::scale(model, size);
	this->shader.setMat4("model", model);

	glActiveTexture(GL_TEXTURE0);
	texture.bind();
	glActiveTexture(GL_TEXTURE1);
	spec.bind();

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE1);
//	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, 0);
}


WaterRenderer::WaterRenderer(Shader& shader) {
	this->shader = shader;
	float vertices[] = {
		 //position         
		 1.0f,  1.0f,  1.0f, 1.0f, 1.0f,
		 1.0f,  -1.0f,  1.0f, 1.0f, 0.0f,
		-1.0f,  -1.0f,  1.0f, 0.0f, 0.0f,
		-1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	//generate buffers
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);


	//confgure geomerty
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)3);

	//unbind buffers
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

WaterRenderer::~WaterRenderer() {
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteVertexArrays(1, &this->VBO);
	glDeleteVertexArrays(1, &this->EBO);
}


void WaterRenderer::drawWater(glm::vec3 position, glm::vec3 size, glm::vec3 color) {
	this->shader.use();
	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, position);
	model = glm::scale(model, size);
	//this->shader.setMat4("model", model);
	
	//this->shader.setVec3("color", color);
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->textureColorbuffer);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

ModelRenderer::ModelRenderer(Shader& shader) {
	this->shader = shader;

}

void ModelRenderer::render(Model* m, glm::vec3 position, glm::vec3 size, glm::vec3 rotate) {
	this->shader.use();
	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, position);

	model = glm::rotate(model, glm::radians(rotate.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotate.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotate.z), glm::vec3(0.0f, 0.0f, 1.0f));

	model = glm::scale(model, size);
	this->shader.setMat4("model", model);
	m->render(this->shader);

}
