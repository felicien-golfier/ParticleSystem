#ifndef CLOUD_H
#define CLOUD_H

#include "Shapes/ParticleSystem.h"

class Cloud : public ParticleSystem
{
public:
    Cloud();
    ~Cloud();

    static const int MAX_PARTICLES = 1000;
    static const int NEW_PARTICLES_PER_MILLISEC = 1;


protected:
    void initializeParticle(Particle &p);
    void updateParticle(Particle &p);
};

#endif // CLOUD_H
