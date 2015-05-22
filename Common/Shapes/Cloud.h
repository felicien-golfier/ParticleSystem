#ifndef CLOUD_H
#define CLOUD_H

#include "Shapes/ParticleSystem.h"

class Cloud : public ParticleSystem
{
public:
    Cloud();
    ~Cloud();

    static const int MAX_PARTICLES = 1000000;
    static const int NEW_PARTICLES_PER_MILLISEC = 10000;


protected:
    void initializeParticle(Particle &p);
    void updateParticle(Particle &p);
};

#endif // CLOUD_H
