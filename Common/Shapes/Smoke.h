#ifndef SMOKE_H
#define SMOKE_H

#include "Shapes/ParticleSystem.h"

class Smoke : public ParticleSystem
{
public:
    Smoke();
    ~Smoke();


protected:
    void initializeParticle(Particle &p);
    void updateParticle(Particle &p);
};

#endif // SMOKE_H
