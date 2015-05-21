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
    GLfloat p_TabColors[12*3];
};

#endif // PARTICLE_H
