/**
 * @author Robin Kantor
 * @login KAN0310
 */

#pragma once

#include <glad/gl.h>

class Texture
{
private:
    GLuint textureID = 0;

public:
    explicit Texture(const char* path);
    ~Texture();

    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    void bind(int unit = 0) const;
};
