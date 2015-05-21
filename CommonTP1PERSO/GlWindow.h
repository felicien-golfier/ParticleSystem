#ifndef GlWindow_h
#define GlWindow_h


#include "GlFramework.h"

#include <QGLWidget>
#include <QKeyEvent>


class GlWindow : public QGLWidget, public GlFramework
{
	public: // methods
		GlWindow();
		~GlWindow();

	private: // methods
		/*!
		*\brief Fonction d'initialization des structures des objets.
		*/
		virtual bool initializeObjects() = 0;

		virtual void render() = 0;

		/*!
		*\brief Fonction d'initialization d'OpenGL, appelée à la création du
		*contexte de rendu.
		*/
		void initializeGL();
		/*!
		*\brief Appelé chaque fois que la fenêtre est redimensionnée.
		*/
		void resizeGL(int w, int h);

		void paintGL();


	private: // methods
		void timerEvent(QTimerEvent *);
};


#define INTERFACE_GLWINDOW \
	bool initializeObjects(); \
	void render(); \
	void keyPressEvent( QKeyEvent* event ); \


#endif
