#pragma once

#include <GL/glew.h>

class Texture {
public:
    GLuint ID;
    GLuint width, height;

    GLuint internal_Format;
    GLuint image_Format;

    GLuint wrap_S;
    GLuint wrap_T;
    GLuint filter_Min;
    GLuint filter_Max;

    Texture() : width(0), height(0), internal_Format(GL_RGB), image_Format(GL_RGB), wrap_S(GL_REPEAT), wrap_T(GL_REPEAT), filter_Min(GL_LINEAR), filter_Max(GL_LINEAR) {
        glGenTextures(1, &this->ID);
    }

    void generate(GLuint width, GLuint height, unsigned char* data) {
        this->width = width;
        this->height = height;

        glBindTexture(GL_TEXTURE_2D, this->ID);
        glTexImage2D(GL_TEXTURE_2D, 0, this->internal_Format, width, height, 0, this->image_Format, GL_UNSIGNED_BYTE, data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrap_S);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrap_T);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filter_Min);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filter_Max);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void bind() const {
        glBindTexture(GL_TEXTURE_2D, this->ID);
    }
};
