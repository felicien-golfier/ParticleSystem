#ifndef Shape_Cylinder_h
#define Shape_Cylinder_h


#include "Shapes/ParametricShape.h"


class Cylinder : public ParametricShape
{
    public:
        Cylinder( int basis_nbr_edges, GLfloat radius, GLfloat y_low, GLfloat y_high );

    protected:
        void drawShape( const char* shader_name );

    protected:
        int m_BasisNbrEdges;
        GLuint* m_TabTopBasisIndices;
        GLuint* m_TabBottomBasisIndices;
        GLuint* m_TabSidesIndices;
};


#endif
