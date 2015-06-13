#ifndef PROJET_IN55_H
#define PROJET_IN55_H


#include "GlWindow.h"


class Projet_IN55 : public GlWindow
{
	public:
        Projet_IN55();
        ~Projet_IN55();

		/*!
		*\brief Initialization des objets.
		*/
		bool initializeObjects();

        void logShader(char* shader_name);
		/*!
		*\brief Rendu de la scène.
		*/
		void render();

		void keyPressEvent(QKeyEvent *);
};


#endif
