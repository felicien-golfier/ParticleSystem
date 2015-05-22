#ifndef FIRE_H
#define FIRE_H

#include "Shapes/ParticleSystem.h"

class Fire : public ParticleSystem
{
public:
    Fire();
    ~Fire();

    static const int MAX_PARTICLES = 1000000;
    static const int NEW_PARTICLES_PER_MILLISEC = 10000;

protected:
    void initializeParticle(Particle &p);
    void updateParticle(Particle &p);
};

#endif // FIRE_H