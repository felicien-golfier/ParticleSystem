#ifndef Basis_h
#define Basis_h


#include "Object3D.h"


class Basis : public Object3D
{
    public:
        Basis( GLfloat length );

    protected:
        void drawShape( const char* shader_name );


    protected:
        GLfloat m_TabVertices[6*3];
};


#endif
