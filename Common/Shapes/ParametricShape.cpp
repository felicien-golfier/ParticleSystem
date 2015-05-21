//*****************************************************************************
//
// Class: ParametricShape
// Author: Fabrice LAURI (fabrice.lauri@utbm.fr)
//         (Associate Professor at the
//          "Université de Technologie de Belfort-Montbéliard", France)
// Version: 1.0
// Last update: 2012-05-01
//
//*****************************************************************************


#include "Shapes/ParametricShape.h"

#include "MemDefns.h"

#include <stdio.h>
#include <string.h>
#include <cmath>


ParametricShape::ParametricShape( int nbr_vertices )
{
    m_TabVertices = new GLfloat [nbr_vertices*3];
    memset( m_TabVertices, 0.0f, nbr_vertices*3*sizeof( GLfloat ) );

    m_TabColors = new GLfloat [nbr_vertices*3];
    memset( m_TabColors, 0.0f, nbr_vertices*3*sizeof( GLfloat ) );
}

ParametricShape::~ParametricShape()
{
    SafeDeleteArray( m_TabVertices );
    SafeDeleteArray( m_TabColors );

    for( unsigned int i = 0; i < m_TabIndices.size(); ++i )
    {
        SafeDeleteArray( m_TabIndices[i] );
    }
}


void
ParametricShape::initArrays()
{
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, m_TabVertices );
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, m_TabColors );
}


void ParametricShape::initVertex( int pos, GLfloat x, GLfloat y, GLfloat z )
{
    pos *= 3;

    m_TabVertices[pos+0] = x;
    m_TabVertices[pos+1] = y;
    m_TabVertices[pos+2] = z;
}

void ParametricShape::generatePointsOnCircle( int pos, int stride, int nbr_edges, GLfloat radius, GLfloat angle_shift, GLfloat y, bool include_center )
{
    GLfloat angle;
    GLfloat shift = (2.0f*M_PI)/nbr_edges;
    GLfloat x, z;
    int i;

    pos *= 3;
    stride *= 3;

    if (include_center)
    {
        // centre du cercle
        m_TabVertices[pos++] = 0.0f;
        m_TabVertices[pos++] = y;
        m_TabVertices[pos++] = 0.0f;
    }

    angle = angle_shift;

    // points sur le cercle
    for( i = 0; i < nbr_edges; ++i )
    {
        x = radius*std::cos(angle);
        z = radius*std::sin(angle);
        angle += shift;

        m_TabVertices[pos+0] = x;
        m_TabVertices[pos+1] = y;
        m_TabVertices[pos+2] = z;

        pos += stride;
    }
}

void ParametricShape::generateColors( int first_index, int nbr_colors, GLfloat r, GLfloat g, GLfloat b )
{
    int pos = first_index*3;

    for( int i = 0; i < nbr_colors; ++i )
    {
        m_TabColors[pos++] = r;
        m_TabColors[pos++] = g;
        m_TabColors[pos++] = b;
    }
}

void ParametricShape::createTabIndices( GLuint* & tab_indices, int size )
{
    tab_indices = new GLuint [size];
    m_TabIndices.push_back( tab_indices );
}

void ParametricShape::generateCircleIndices( GLuint* tab_indices, GLuint center_index, GLuint first_index, GLuint stride, int nbr_edges )
{
    int i;

    tab_indices[0] = center_index;
    for( i = 1; i <= nbr_edges; ++i )
    {
        tab_indices[i] = first_index+(i-1)*stride;
    }
    tab_indices[i] = first_index;
}

void ParametricShape::generateExtrusionIndices( GLuint* tab_indices, GLuint first_index, GLuint stride, int nbr_edges )
{
    GLuint down = first_index+1;
    GLuint up = first_index+stride;
    GLuint max_down = first_index+nbr_edges;
    GLuint max_up = max_down+stride;
    int i = 0;
    int nbr;

    nbr = (nbr_edges+1)*2;
    --nbr;

    tab_indices[i++] = up++;
    while( i < nbr )
    {
        tab_indices[i++] = up++;
        tab_indices[i++] = down++;

        if (down >= max_down)
        {
            down = first_index;
        }
        if (up >= max_up)
        {
            up = first_index+stride;
        }
    }
    tab_indices[i++] = down;

//	printf( "%d,%d,%d\n", first_index, first_index+stride, nbr_edges );
//	for( i = 0; i < (nbr_edges+1)*2; ++i )
//	{
//		printf( "%d ", tab_indices[i] );
//	}
//	printf( "\n" );
}

void ParametricShape::generateArmsIndices( GLuint* tab_indices, GLuint first_index, int nbr_arms )
{
    int pos = 0;
    int arm_index = first_index;
    int i;

    for( i = 0; i < nbr_arms-1; ++i )
    {
        tab_indices[pos++] = arm_index;
        tab_indices[pos++] = arm_index-1;
        tab_indices[pos++] = arm_index+1;

        arm_index += 2;
    }
    tab_indices[pos++] = arm_index;
    tab_indices[pos++] = arm_index-1;
    tab_indices[pos++] = first_index-1;

//	printf( "Arms (%d): ", first_index );
//	for( i = 0; i < nbr_arms*3; ++i )
//	{
//		printf( "%d ", tab_indices[i] );
//	}
//	printf( "\n" );
}
