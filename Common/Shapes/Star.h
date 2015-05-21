#ifndef Shape_Star_h
#define Shape_Star_h


#include "Shapes/ParametricShape.h"


class Star : public ParametricShape
{
    public:
        Star( int nbr_arms, GLfloat radius1, GLfloat radius2, GLfloat y_high );

    protected:
        void drawShape( const char* shader_name );

    protected:
        int m_NbrArms;
        GLuint* m_TabTopBasisIndices;
        GLuint* m_TabTopBasisArmsIndices;
        GLuint* m_TabBottomBasisIndices;
        GLuint* m_TabBottomBasisArmsIndices;
        GLuint* m_TabSidesIndices;
};


#endif
