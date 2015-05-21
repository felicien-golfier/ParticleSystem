#ifndef PARTICLE_H
#define PARTICLE_H

#include "Object3D.h"

class Particle : public Object3D
{
public:
    Particle();
    void draw();
protected:
    GLuint bmp_texture_load(const char *filename);
    void drawShape( const char* shader_name );
    GLfloat p_TabColors[8*3];
    GLfloat mTabVertices[8*3] = {
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
         1.0f, 1.0f,1.0f,    // triangle 1 : end
         1.0f, 1.0f,-1.0f,   // triangle 2 : begin
         1.0f, -1.0f,-1.0f,
         1.0f, -1.0f,1.0f,
        -1.0f, 1.0f,-1.0f
    };

public:
    void update();
};

#endif // PARTICLE_H
