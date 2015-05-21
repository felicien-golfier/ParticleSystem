//*****************************************************************************
//
// Class: Pyramid
// Author: Fabrice LAURI (fabrice.lauri@utbm.fr)
//         (Associate Professor at the
//          "Université de Technologie de Belfort-Montbéliard", France)
// Version: 1.0
// Last update: 2012-05-01
//
//*****************************************************************************


#include "Shapes/Pyramid.h"


Pyramid::Pyramid( int basis_nbr_edges, GLfloat radius, GLfloat y_high ) : ParametricShape( basis_nbr_edges+2 )
{
    m_BasisNbrEdges = basis_nbr_edges;


    // Génération des vertices de la base
    generatePointsOnCircle( 0, 1, basis_nbr_edges, radius, 0.0f, 0.0f, true );
    // Génération du sommet de la pyramide
    initVertex( basis_nbr_edges+1, 0.0f, y_high, 0.0f );


    // Génération des couleurs de la base
    generateColors( 0, basis_nbr_edges+1, 1.0f, 0.0f, 0.0f );
    // Génération de la couleur du sommet de la pyramide
    generateColors( basis_nbr_edges+1, 1, 0.0f, 0.0f, 1.0f );


    // Génération des indices pour construire la base de la pyramide
    createTabIndices( m_TabBasisIndices, m_BasisNbrEdges+2 );
    generateCircleIndices( m_TabBasisIndices, 0, 1, 1, basis_nbr_edges );
    // Génération des indices pour construire le chapeau de la pyramide
    createTabIndices( m_TabHatIndices, m_BasisNbrEdges+2 );
    generateCircleIndices( m_TabHatIndices, m_BasisNbrEdges+1, 1, 1, basis_nbr_edges );
}


void Pyramid::drawShape( const char* shader_name )
{
    glEnableVertexAttribArray( 0 );
    glEnableVertexAttribArray( 1 );
    initArrays();
    glDrawElements( GL_TRIANGLE_FAN, m_BasisNbrEdges+2, GL_UNSIGNED_INT, m_TabBasisIndices );
    glDrawElements( GL_TRIANGLE_FAN, m_BasisNbrEdges+2, GL_UNSIGNED_INT, m_TabHatIndices );
    glDisableVertexAttribArray( 0 );
    glDisableVertexAttribArray( 1 );
}
