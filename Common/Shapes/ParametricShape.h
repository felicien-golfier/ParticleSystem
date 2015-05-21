#ifndef Shape_ParametricShape_h
#define Shape_ParametricShape_h


#include "Shapes/Shape.h"

#include <vector>


class ParametricShape : public Shape
{
    public:
        ParametricShape( int nbr_vertices );
        ~ParametricShape();

    protected:
        void initArrays();

        void initVertex( int pos, GLfloat x, GLfloat y, GLfloat z );
        void generatePointsOnCircle( int pos, int shift, int nbr_edges, GLfloat radius, GLfloat angle_shift, GLfloat y, bool include_center );

        void generateColors( int first_index, int nbr_colors, GLfloat r, GLfloat g, GLfloat b );

        void createTabIndices( GLuint* & tab_indices, int size );

        void generateCircleIndices( GLuint* tab_indices, GLuint center_index, GLuint first_index, GLuint stride, int nbr_edges );
        void generateExtrusionIndices( GLuint* tab_indices, GLuint first_index, GLuint stride, int nbr_edges );
        void generateArmsIndices( GLuint* tab_indices, GLuint first_index, int nbr_arms );


    protected:
        GLfloat* m_TabVertices;
        GLfloat* m_TabColors;
        std::vector<GLuint*> m_TabIndices;
};


#endif
