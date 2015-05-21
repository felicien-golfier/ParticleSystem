#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include "Object3D.h"
#include <glm/glm.hpp>
#include <ctime>
#include "GlFramework.h"
#include <cstdio>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <time.h>

static const int MaxParticles = 100000;

// CPU representation of a particle
struct Particle{
    glm::vec3 pos, speed;
    float r,g,b,a; // Color
    float life; // Remaining life of the particle. if <0 : dead and unused.
};



class ParticleSystem : public Object3D
{
public:
    ParticleSystem();
    void draw();
    void update();
    int FindUnusedParticle();

protected:
    void drawShape( const char* shader_name );
    GLfloat m_TabColors[8*3];
    GLfloat m_TabVertices[8*3] = {
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
         1.0f, 1.0f,1.0f,    // triangle 1 : end
         1.0f, 1.0f,-1.0f,   // triangle 2 : begin
         1.0f, -1.0f,-1.0f,
         1.0f, -1.0f,1.0f,
        -1.0f, 1.0f,-1.0f
    };

public :
    static GLuint bmp_texture_load(const char *filename);


private :
    std::clock_t _lastTime;

    GLfloat* g_particule_position_size_data;
    GLfloat* g_particule_color_data;

    Particle ParticlesContainer[MaxParticles];

    int LastUsedParticle = 0;
    int ParticlesCount = 0;

};

#endif // PARTICLE_H
