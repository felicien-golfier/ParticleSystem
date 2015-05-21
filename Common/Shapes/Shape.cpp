//*****************************************************************************
//
// Class: Shape
// Author: Fabrice LAURI (fabrice.lauri@utbm.fr)
//         (Associate Professor at the
//          "Université de Technologie de Belfort-Montbéliard", France)
// Version: 1.0
// Last update: 2012-08-09
//
//*****************************************************************************


#include "Shapes/Shape.h"
#include "MemDefns.h"


Shape::Shape() :
    m_NbrVertices( 0 ),
    m_TabVertices( NULL ),
    m_TabNormals( NULL ),
    m_TabTexCoords( NULL ),
    m_NbrIndices( 0 ),
    m_TabIndices( NULL ),
    m_DynamicVertices( true ),
    m_DynamicIndices( true )
{
}

Shape::~Shape()
{
    clear();
}


uint32
Shape::getNbrVertices() const
{
    return m_NbrVertices;
}

const GLfloat*
Shape::vertices() const
{
    return m_TabVertices;
}

const GLfloat*
Shape::normals() const
{
    return m_TabNormals;
}

const GLfloat*
Shape::textureCoordinates() const
{
    return m_TabTexCoords;
}


uint32
Shape::getNbrIndices() const
{
    return m_NbrIndices;
}

const GLuint*
Shape::indices() const
{
    return m_TabIndices;
}


void
Shape::clear()
{
    if (m_DynamicVertices)
    {
        SafeDeleteArray( m_TabVertices );
        SafeDeleteArray( m_TabNormals );
        SafeDeleteArray( m_TabTexCoords );
    }

    if (m_DynamicIndices)
    {
        SafeDeleteArray( m_TabIndices );
    }
}
