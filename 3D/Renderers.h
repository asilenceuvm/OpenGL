#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Texture.h"
#include "Model.h"

class Renderer {
public:
    Shader getShader();
protected:
    GLuint VAO, VBO, EBO;
    Shader shader;
};

class ObjectRenderer : public Renderer {
public:
    ObjectRenderer(Shader& shader);
    ~ObjectRenderer();

    void drawObject(Texture texture, 
        Texture spec, 
        glm::vec3 position, 
        glm::vec3 size = glm::vec3(10, 10, 10), 
        glm::vec3 rotate = glm::vec3(0.0f, 0.0f, 0.0f), 
        glm::vec3 color = glm::vec3(1.0f));
};


class WaterRenderer : public Renderer {
public:
    WaterRenderer(Shader& shader);
    ~WaterRenderer();

    void drawWater(glm::vec3 position,
        glm::vec3 size, 
        glm::vec3 color = glm::vec3(1.0f));

    GLuint framebuffer;
private:
	unsigned int textureColorbuffer;
};

class ModelRenderer : public Renderer {
public:
    ModelRenderer(Shader& shader);

    void render(Model* m, glm::vec3 position, glm::vec3 size, glm::vec3 rotate);
};
