//*****************************************************************************
//
// Class: Star
// Author: Fabrice LAURI (fabrice.lauri@utbm.fr)
//         (Associate Professor at the
//          "Université de Technologie de Belfort-Montbéliard", France)
// Version: 1.0
// Last update: 2012-05-01
//
//*****************************************************************************


#include "Shapes/Star.h"

#include <stdio.h>
#include <string.h>
#include <cmath>


Star::Star( int nbr_arms, GLfloat radius1, GLfloat radius2, GLfloat y_high ) : ParametricShape( ((nbr_arms*2)+1)*2 )
{
    m_NbrArms = nbr_arms;

    // Génération des vertices de la base du haut
    generatePointsOnCircle( 0, 2, nbr_arms, radius1, 0.0f, y_high, true );
    // Génération des vertices des bras de la base du haut
    generatePointsOnCircle( 2, 2, nbr_arms, radius2, M_PI/nbr_arms, y_high, false );

    // Génération des couleurs de la base du haut
    generateColors( 0, nbr_arms*2+1, 1.0f, 0.0f, 1.0f );

    // Génération des indices pour construire la base du haut du cylindre
    createTabIndices( m_TabTopBasisIndices, nbr_arms+2 );
    generateCircleIndices( m_TabTopBasisIndices, 0, 1, 2, nbr_arms );
    // Génération des indices pour construire la base du haut du cylindre
    createTabIndices( m_TabTopBasisArmsIndices, nbr_arms*3 );
    generateArmsIndices( m_TabTopBasisArmsIndices, 2, nbr_arms );

    // Génération des vertices de la base du bas
    generatePointsOnCircle( (nbr_arms*2)+1, 2, nbr_arms, radius1, 0.0f, 0.0f, true );
    // Génération des vertices des bras de la base du haut
    generatePointsOnCircle( (nbr_arms*2)+3, 2, nbr_arms, radius2, M_PI/nbr_arms, 0.0f, false );

    // Génération des couleurs de la base du bas
    generateColors( nbr_arms*2+1, nbr_arms*2+1, 0.5f, 0.0f, 0.5f );

    // Génération des indices pour construire la base du haut du cylindre
    createTabIndices( m_TabBottomBasisIndices, nbr_arms+2 );
    generateCircleIndices( m_TabBottomBasisIndices, (nbr_arms*2)+1, (nbr_arms*2)+2, 2, nbr_arms );
    // Génération des indices pour construire la base du haut du cylindre
    createTabIndices( m_TabBottomBasisArmsIndices, nbr_arms*3 );
    generateArmsIndices( m_TabBottomBasisArmsIndices, (nbr_arms*2)+3, nbr_arms );

    // Génération des indices des côtés du cylindre (extrusion)
    createTabIndices( m_TabSidesIndices, ((nbr_arms*2)+2)*2 );
    generateExtrusionIndices( m_TabSidesIndices, 1, (nbr_arms*2)+1, nbr_arms*2 );
}


void
Star::drawShape( const char* shader_name )
{
    glEnableVertexAttribArray( 0 );
    glEnableVertexAttribArray( 1 );
    initArrays();
    glDrawElements( GL_TRIANGLE_FAN, m_NbrArms+2, GL_UNSIGNED_INT, m_TabTopBasisIndices );
    glDrawElements( GL_TRIANGLES, m_NbrArms*3, GL_UNSIGNED_INT, m_TabTopBasisArmsIndices );
    glDrawElements( GL_TRIANGLE_FAN, m_NbrArms+2, GL_UNSIGNED_INT, m_TabBottomBasisIndices );
    glDrawElements( GL_TRIANGLES, m_NbrArms*3, GL_UNSIGNED_INT, m_TabBottomBasisArmsIndices );
    glDrawElements( GL_TRIANGLE_STRIP, ((m_NbrArms*2)+1)*2, GL_UNSIGNED_INT, m_TabSidesIndices );
    glDisableVertexAttribArray( 0 );
    glDisableVertexAttribArray( 1 );
}
