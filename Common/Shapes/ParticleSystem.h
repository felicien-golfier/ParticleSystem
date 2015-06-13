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
#include "SOIL.h"

// CPU representation of a particle
struct Particle{
    glm::vec3 pos, speed;
    float r,g,b,a; // Color
    float life; // Remaining life of the particle. if <0 : dead and unused.

    bool operator<(const Particle& that) const {
        // Sort in reverse order : far particles drawn first.
        return this->a < that.a;
    }
};

class ParticleSystem : public Object3D
{

//Absract class does not need constructor
public:
    ~ParticleSystem();

    void render();

protected:
    int MAX_PARTICLES;
    int NEW_PARTICLES_PER_MILLISEC;
    void initSystem();


protected:

    GLfloat* m_vertex_data;
    GLfloat* m_color_data;
    Particle* m_particle_container;
    double deltaTime;
    double current_fps;
    double average_fps = 0;
    long nb_frames = 0;
    const char* m_texture_url;

    virtual void initializeParticle(Particle &p) = 0;
    virtual void updateParticle(Particle &p) = 0;
    void draw();
    void drawShape( const char* shader_name );

private:
    std::clock_t _lastTime;
    std::clock_t _fpsTime;
    int _frames_count = 0;

    int _lastUsedParticle = 0;
    int _particlesCount = 0;
    int FindUnusedParticle();

};

#endif // PARTICLE_H
