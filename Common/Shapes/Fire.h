#ifndef FIRE_H
#define FIRE_H

#include "Shapes/ParticleSystem.h"

class Fire : public ParticleSystem
{
public:
    Fire();
    ~Fire();

protected:
    void initializeParticle(Particle &p);
    void updateParticle(Particle &p);
};

#endif // FIRE_H
