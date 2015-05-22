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

    void render();

    static const int MAX_PARTICLES = 1000;
    static const int NEW_PARTICLES_PER_MILLISEC = 1;
    static const char* TEXTURE_URL;


protected:

    GLfloat* m_color_data;
    GLfloat* m_vertex_data;
    Particle m_particle_container[MAX_PARTICLES];
    double deltaTime;

    void initializeParticle(Particle &p);
    void updateParticle(Particle &p);
    void draw();
    void drawShape( const char* shader_name );

private:
    std::clock_t _lastTime;

    int _lastUsedParticle = 0;
    int _particlesCount = 0;
    int FindUnusedParticle();

public :
    static GLuint bmp_texture_load(const char *filename);


};

#endif // PARTICLE_H
