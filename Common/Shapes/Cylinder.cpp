//*****************************************************************************
//
// Class: Cylinder
// Author: Fabrice LAURI (fabrice.lauri@utbm.fr)
//         (Associate Professor at the
//          "Université de Technologie de Belfort-Montbéliard", France)
// Version: 1.0
// Last update: 2012-05-01
//
//*****************************************************************************


#include "Shapes/Cylinder.h"


Cylinder::Cylinder( int basis_nbr_edges, GLfloat radius, GLfloat y_low, GLfloat y_high ) : ParametricShape( (basis_nbr_edges+1)*2 )
{
    m_BasisNbrEdges = basis_nbr_edges;

    // Génération des vertices de la base du haut
    generatePointsOnCircle( 0, 1, basis_nbr_edges, radius, 0.0f, y_low, true );
    // Génération des vertices de la base du bas
    generatePointsOnCircle( basis_nbr_edges+1, 1, basis_nbr_edges, radius, 0.0f, y_high, true );

    // Génération des couleurs de la base du haut
    generateColors( 0, basis_nbr_edges+1, 1.0f, 1.0f, 0.0f );
    // Génération des couleurs de la base du bas
    generateColors( basis_nbr_edges+1, basis_nbr_edges+1, 0.0f, 1.0f, 1.0f );

    // Génération des indices pour construire la base du haut du cylindre
    createTabIndices( m_TabTopBasisIndices, m_BasisNbrEdges+2 );
    generateCircleIndices( m_TabTopBasisIndices, 0, 1, 1, basis_nbr_edges );
    // Génération des indices pour construire la base du bas du cylindre
    createTabIndices( m_TabBottomBasisIndices, m_BasisNbrEdges+2 );
    generateCircleIndices( m_TabBottomBasisIndices, basis_nbr_edges+1, basis_nbr_edges+2, 1, basis_nbr_edges );
    // Génération des indices des côtés du cylindre (extrusion)
    createTabIndices( m_TabSidesIndices, (m_BasisNbrEdges+2)*2 );
    generateExtrusionIndices( m_TabSidesIndices, 1, basis_nbr_edges+1, basis_nbr_edges );
}


void Cylinder::drawShape( const char* shader_name )
{
    glEnableVertexAttribArray( 0 );
    glEnableVertexAttribArray( 1 );
    initArrays();
    glDrawElements( GL_TRIANGLE_FAN, m_BasisNbrEdges+2, GL_UNSIGNED_INT, m_TabTopBasisIndices );
    glDrawElements( GL_TRIANGLE_FAN, m_BasisNbrEdges+2, GL_UNSIGNED_INT, m_TabBottomBasisIndices );
    glDrawElements( GL_TRIANGLE_STRIP, (m_BasisNbrEdges+1)*2, GL_UNSIGNED_INT, m_TabSidesIndices );
    glDisableVertexAttribArray( 0 );
    glDisableVertexAttribArray( 1 );
}
