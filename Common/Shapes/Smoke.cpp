#include "Smoke.h"

Smoke::Smoke()
{
    m_texture_url = "../../textures/smoke1.png";
    MAX_PARTICLES = 5000;
    NEW_PARTICLES_PER_MILLISEC = 20;

    initSystem();
}

Smoke::~Smoke()
{

}


void Smoke::initializeParticle(Particle & p) {
    p.life = 10; // This particle will live 10 seconds.
    double theta = (rand()%(int)(2*M_PI*1000))/1000.0f;
    double r = (rand()%500)/1000.0f;
    p.pos = glm::vec3(r*cos(theta),0,r*sin(theta)); // and begin from center

    float spread = 1.0f;

    glm::vec3 maindir = glm::vec3(0.0f, 2.0f, 0.0f);

    glm::vec3 randomdir = glm::vec3(
        (rand()%2000 - 1000.0f)/1000.0f,
        (rand()%2000 - 1000.0f)/1000.0f,
        (rand()%2000 - 1000.0f)/1000.0f
    );

    p.speed = maindir + randomdir * spread;

    p.r = 0.1f;
    p.g = 0.1f;
    p.b = 0.1f;
    p.a = 0.1f;
}

// Update particle : called each frame
void Smoke::updateParticle(Particle & p){
    // Decrease life
    p.life -= deltaTime * 10.0f;

    // Simulate simple physics : gravity only, no collisions
    p.pos += p.speed * (float)deltaTime;

    p.a -= 0.0005f;
}

