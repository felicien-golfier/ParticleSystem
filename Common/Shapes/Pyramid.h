#ifndef Shape_Pyramid_h
#define Shape_Pyramid_h


#include "Shapes/ParametricShape.h"


class Pyramid : public ParametricShape
{
    public:
        Pyramid( int basis_nbr_edges, GLfloat radius, GLfloat y_high );

    protected:
        void drawShape( const char* shader_name );

    protected:
        int m_BasisNbrEdges;
        GLuint* m_TabBasisIndices;
        GLuint* m_TabHatIndices;
};


#endif
