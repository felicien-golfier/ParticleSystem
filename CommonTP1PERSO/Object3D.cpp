#include "Object3D.h"


AbstractFramework* Object3D::m_Framework = NULL;


void
Object3D::setFramework( AbstractFramework* fw )
{
	m_Framework = fw;
}


void
Object3D::draw()
{
    if (m_Framework->useShader( "color" ))
    {
        m_Framework->computeAncillaryMatrices();
        GLint var_id = glGetUniformLocation( m_Framework->getCurrentShaderId(), "MVP" );
        m_Framework->transmitMVP( var_id );

        drawShape();
    }
}
