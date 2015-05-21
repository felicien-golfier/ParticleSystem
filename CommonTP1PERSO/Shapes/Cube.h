#ifndef CUBE_H
#define CUBE_H

#include "Object3D.h"

class Cube : public Object3D
{
    public:
        Cube( );

    protected:
        void drawShape();

protected:
//    GLfloat m_TabVertices[6*3];

};


#endif // CUBE_H
