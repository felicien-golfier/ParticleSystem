#include "Fire.h"

Fire::Fire(const glm::vec3 &camera_position) : ParticleSystem(camera_position)
{
    m_texture_url = "../../textures/fire.png";
}


Fire::~Fire()
{

}

void Fire::initializeParticle(Particle & p) {
    p.life = 2.0f; // This particle will live 5 seconds.
    p.pos = glm::vec3(0,0,0); // and begin from center

    float spread = 1.0f;
    glm::vec3 maindir = glm::vec3(0.0f, 2.0f, 0.0f);

    glm::vec3 randomdir = glm::vec3(
        (rand()%2000 - 1000.0f)/1000.0f,
        (rand()%2000 - 1000.0f)/1000.0f,
        (rand()%2000 - 1000.0f)/1000.0f
    );

    p.speed = maindir + randomdir * spread;

    p.r = 1.0f;
    p.g = 0.0f;
    p.b = 0.0f;
    p.a = 1.0f;//(rand()%10)/10.0f;
}

// Update particle : called each frame
void Fire::updateParticle(Particle & p){
    // Simulate simple physics : gravity only, no collisions
    p.speed += glm::vec3(0.0f,1.81f, 0.0f) * (float)deltaTime;
    p.pos += p.speed * (float)deltaTime;

    p.a -= 0.001f;
}
