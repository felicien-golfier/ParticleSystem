#include "TP01.h"


#include "Shapes/Basis.h"
#include "Shapes/Cubes.h"
#include "Shapes/Pyramid.h"
#include "Shapes/Cylinder.h"
#include "Shapes/Star.h"
#include "Shapes/Particle.h"

#include <iostream>

using namespace std;


GLfloat angle1 = 30.0f;
GLfloat angle2 = 20.0f;
GLfloat zoom = 30.0f;

const GLfloat g_AngleSpeed = 10.0f;
const GLfloat g_zoomSpeed = 1.0f;

Basis* basis;
Pyramid* pyr;
Cylinder* cyl;
Star* star;
MultipleColorCube* cube;
Particle* particle;
//Rubik* guss;


TP01::TP01()
{
	setWindowTitle(trUtf8("IN55-TP01"));


    basis = new Basis( 10.0 );
    star = new Star( 6, 1.0, 1.4, 1.0 );
    pyr = new Pyramid( 5, 2.0, 10.0 );
    cyl = new Cylinder( 32, 1.5, 0.0, 10.0 );
    cube = new MultipleColorCube();
    particle = new Particle();

}


TP01::~TP01()
{
    delete basis;
    delete star;
    delete pyr;
    delete cyl;
    delete cube;
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
    createShader( "Shaders/points" );
    createShader( "Shaders/particle" );

    cout << "Shader color: ";

    if (useShader( "color" ))
    {
        cout << "Loaded!" << endl;
    }
    else
    {
        cout << "NOT Loaded!" << endl;
    }
    cout << "press z and s to zoom and arrows to turn" << endl;
	return true;
}


void
TP01::render()
{
	// Initialisation de la caméra
    lookAt( 0, 5, zoom, 0, 0, 0 );


	// Rendu des objets
    pushMatrix();
        rotate( angle1, 0, 1, 0 );
        rotate( angle2, 1, 0, 0 );
        basis->draw();

        // particle système

        pushMatrix();
        scale( 5, 3, 3 );
        particle->draw();
        popMatrix();

        // Points
        pushMatrix();
        translate( 0, 0, 0 );
        scale( 5, 3, 3 );
        cube->draw(false);
        popMatrix();

//        pushMatrix();
//        translate( 0, 0, 0 );
//        scale( 2, 3, 3 );
//        cube->draw(true);
//        popMatrix();

//        //star
//        pushMatrix();
//        translate( -20.0, 0, 0 );
//        star->draw();
//        popMatrix();


//        pushMatrix();
//        translate( 20.0, 0, 0 );
//        pyr->draw();
//        popMatrix();

//        pushMatrix();
//        translate( -15.0, 0, 0 );
//        cyl->draw();
//        popMatrix();


//         //Bonhomme
//        pushMatrix();
//            translate( 6 , 11.5, 0 );
//            scale( 0.1, 0.1, 0.1);

//            // bras droit
//            pushMatrix();
//            translate( 10 + 2.5, 0, 0 );
//            scale( 1, 4, 1 );
//            cube->draw();
//            popMatrix();

//            // bras gauche
//            pushMatrix();
//            translate( 10 -2.5, 0, 0 );
//            scale( 1, 4, 1 );
//            cube->draw();
//            popMatrix();

//            // corps
//            pushMatrix();
//            translate( 10 + 0, 4, 0 );
//            scale( 2, 2, 2 );
//            cube->draw();
//            popMatrix();

//            //tête
//            pushMatrix();
//            translate( 10 + 0, 0, 0 );
//            scale( 3, 5, 2 );
//            cube->draw();
//            popMatrix();

//            // jambe gauche
//            pushMatrix();
//            translate( 10 -1, -5, 0 );
//            scale( 1, 5, 1 );
//            cube->draw();
//            popMatrix();

//            // jambe droite
//            pushMatrix();
//            translate( 10 + 1, -5, 0 );
//            scale( 1, 5, 1 );
//            cube->draw();
//            popMatrix();

//        popMatrix();

//       //Grue
//        // Pied
//        pushMatrix();
//        translate( 0, 0, 0 );
//        scale( 4, 2, 2 );
//        cube->draw();
//        popMatrix();

//        //tronc
//        pushMatrix();
//        translate( 0, 0.5, 0 );
//        scale( 0.5, 1, 0.5);
//        cyl->draw();
//        popMatrix();

//        //fil
//        pushMatrix();
//        translate( -7, 1.5, 0 );
//        scale( 0.1, 0.8, 0.1);
//        cyl->draw();
//        popMatrix();

//        //bras
//        pushMatrix();
//        translate( 0, 10, 0 );
//        scale( 15, 1.5, 1.5);
//        cube->draw();
//        popMatrix();

//        //contre-poid
//        pushMatrix();
//        translate( 6.5, 8.5, 0 );
//        scale( 2, 1.5, 1.5);
//        cube->draw();
//        popMatrix();

//    //Rubik's Cube
//        //guss->draw();

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
