//*****************************************************************************
//
// Program: TP01 (IN55)
// Author: Fabrice LAURI (fabrice.lauri@utbm.fr)
//          (Associate Professor at the
//          "Université de Technologie de Belfort-Montbéliard", France)
// Version: 1.0
// Last update: 2012-05-01
//
//*****************************************************************************


#include "GlWindow.h"


GlWindow::GlWindow()
{
    resize(1024, 768);
    startTimer(30);
}

GlWindow::~GlWindow()
{
}


void
GlWindow::initializeGL()
{
    init();
    initializeObjects();
}


void
GlWindow::timerEvent(QTimerEvent *)
{
    update();
}


void
GlWindow::paintGL()
{
    // Nettoyage du Color Buffer et du Depth Buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    render();
}


void
GlWindow::resizeGL( int w, int h )
{
    glViewport( 0, 0, w, h );

    float a = w / static_cast<GLfloat>(h);
//	printf( "Size: (%d,%d) - AspectRatio: %f\n", w, h, a );

    setPerspective( 45.0f, a, 0.1f, 100.0f );
}
