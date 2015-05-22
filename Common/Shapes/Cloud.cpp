#include "Cloud.h"

Cloud::Cloud()
{
    m_texture_url = "../../textures/fog2.bmp";
}

Cloud::~Cloud()
{

}


void Cloud::initializeParticle(Particle & p) {
    p.life = 10.0f; // This particle will live 5 seconds.
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
    p.g = 1.0f;
    p.b = 1.0f;
    p.a = 0.5f;//(rand()%10)/10.0f;
}

// Update particle : called each frame
void Cloud::updateParticle(Particle & p){
    // Simulate simple physics : gravity only, no collisions
//    p.speed += glm::vec3(0.0f,-9.81f, 0.0f) * (float)deltaTime;
    p.pos += p.speed * (float)deltaTime;

    p.a -= 0.001f;
}
