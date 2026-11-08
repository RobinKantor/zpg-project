/**
 * @author Robin Kantor
 * @login KAN0310
 */

#pragma once

#include "ShaderProgram.h"

class Skybox
{
private:
    ShaderProgram* shader;
    GLuint VAO = 0;
    GLuint VBO = 0;
    GLuint textureID = 0;

public:
    Skybox(ShaderProgram* shader, const char* folder);
    ~Skybox();

    Skybox(const Skybox&) = delete;
    Skybox& operator=(const Skybox&) = delete;

    void draw() const;
};
