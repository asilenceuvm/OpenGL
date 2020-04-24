#pragma once

#include "Shader.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Renderer {
public:
    Renderer(Shader& shader) {
        this->shader = shader;
        GLuint VBO;
        /*float vertices[] = {
            // positions          // texture coords
             0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
             0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
        };*/
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
        glGenVertexArrays(1, &this->quadVAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &this->EBO);

        

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glBindVertexArray(this->quadVAO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        
        
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    ~Renderer() {
        glDeleteVertexArrays(1, &this->quadVAO);
    }


    void drawSprite(Texture texture, glm::vec3 position, glm::vec3 size = glm::vec3(10, 10, 10), glm::vec3 rotate = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 color = glm::vec3(1.0f)) {
        this->shader.use();
        glm::mat4 model = glm::mat4(1.0f);

        model = glm::translate(model, position);

        model = glm::rotate(model, glm::radians(rotate.x), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotate.y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotate.z), glm::vec3(0.0f, 0.0f, 1.0f));

        model = glm::scale(model, size);
        this->shader.setMat4("model", model);

        glActiveTexture(GL_TEXTURE0);
        texture.bind();

        glBindVertexArray(this->quadVAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
    void drawSprite(Texture texture, Texture spec, glm::vec3 position, glm::vec3 size = glm::vec3(10, 10, 10), glm::vec3 rotate = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 color = glm::vec3(1.0f)) {
        this->shader.use();
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

        glBindVertexArray(this->quadVAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
private:
    GLuint quadVAO, EBO;
    Shader shader;
};