#include "Fire.h"

Fire::Fire()
{
    m_texture_url = "../../textures/fire5.png";
}


Fire::~Fire()
{

}

void Fire::initializeParticle(Particle & p) {
    p.life = 0.5f; // This particle will live 5 seconds.
    p.pos = glm::vec3(0,0,0); // and begin from center

    float spread = 1.0f;
    glm::vec3 maindir = glm::vec3(0.0f, 1.0f, 0.0f);

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
    // Decrease life
    p.life -= deltaTime *3.0f * glm::distance(p.pos, glm::vec3(0, p.pos.y, 0));

    if (p.life < 0.1f || glm::distance(p.pos, glm::vec3(0, 0, 0)) > 2.0f) {
        p.life = -1;
    }
    float d = 2.0f * glm::distance(p.pos, glm::vec3(0, p.pos.y, 0));
    // Simulate simple physics : gravity only, no collisions
    p.speed += glm::vec3(-d, 1.0f, -d) * (float)deltaTime;
//    p.speed -= glm::vec3(1.0f, 0.0f, 1.0f) * (float)deltaTime;
    p.pos += p.speed * (float)deltaTime;

    p.g = 1.0f - 2.0f * (
        0.8f * glm::distance(p.pos, glm::vec3(0, p.pos.y, 0)) +
        0.2f * glm::distance(p.pos, glm::vec3(0, 0, 0))
    );
    p.a = 1.0f - 1.8f*glm::distance(p.pos, glm::vec3(0, p.pos.y, 0)) ;
}
