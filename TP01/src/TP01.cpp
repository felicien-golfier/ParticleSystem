#include "TP01.h"


#include "Shapes/Basis.h"
#include "Shapes/Cubes.h"
#include "Shapes/Pyramid.h"
#include "Shapes/Cylinder.h"
#include "Shapes/Star.h"
#include "Shapes/ParticleSystem.h"

#include <iostream>

using namespace std;

GLfloat angle1 = 30.0f;
GLfloat angle2 = 20.0f;
GLfloat zoom = 30.0f;

const GLfloat g_AngleSpeed = 10.0f;
const GLfloat g_zoomSpeed = 1.0f;

Basis* basis;
ParticleSystem* particle;


TP01::TP01()
{
	setWindowTitle(trUtf8("IN55-TP01"));

    basis = new Basis( 10.0 );
    particle = new ParticleSystem();
}

TP01::~TP01()
{
    delete basis;
    delete particle;
}


bool
TP01::initializeObjects()
{
	// Fond gris
	glClearColor( 0.2f, 0.2f, 0.2f, 1.0f );
	glEnable( GL_DEPTH_TEST );
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

    // Chargement des shaders
    createShader( "Shaders/color" );
    createShader( "Shaders/particle" );

    logShader("color");
    logShader("particle");

    cout << "press z and s to zoom and arrows to turn" << endl;
	return true;
}

void
TP01::logShader(char* shader_name) {

    cout << "Shader " + std::string(shader_name) + " : ";
    if (useShader(shader_name))
    {
        cout << "Loaded!" << endl;
    }
    else
    {
        cout << "NOT Loaded!" << endl;
    }
}


void
TP01::render()
{
	// Initialisation de la caméra
    lookAt( 0, 5, zoom, 0, 0, 0 );

	// Rendu des objets
    pushMatrix();
        // Basis
        rotate( angle1, 0, 1, 0 );
        rotate( angle2, 1, 0, 0 );
        basis->draw();

        // Particle system
        pushMatrix();
        scale( 5, 3, 3 );
        particle->update();
        particle->draw();
        popMatrix();

    popMatrix();
}


void
TP01::keyPressEvent( QKeyEvent* event )
{
	switch( event->key())
	{
		case Qt::Key_Escape:
			close();
			break;

		case Qt::Key_Left:
			angle1 -= g_AngleSpeed;
			break;

		case Qt::Key_Right:
			angle1 += g_AngleSpeed;
			break;

		case Qt::Key_Up:
			angle2 -= g_AngleSpeed;
			break;

		case Qt::Key_Down:
			angle2 += g_AngleSpeed;
			break;

        case Qt::Key_Z:
            zoom -= g_zoomSpeed;
            break;

        case Qt::Key_S:
            zoom += g_zoomSpeed;
            break;

		case Qt::Key_R:
			angle1 = angle2 = 0.0f;
			break;
	}
}
