#ifndef GlFramework_h
#define GlFramework_h


#include "AbstractFramework.h"

#include <QLinkedList>
#include <QImage>
#include <vector>
#include <string>


struct GLMatrix
{
    union
    {
        GLfloat m[4][4];
        GLfloat data[16];
    };

    void setIdentity();
};

GLMatrix operator*(const GLMatrix &, const GLMatrix &);
GLMatrix inverse( const GLMatrix & );


class GlFramework : public AbstractFramework
{
    public: // methods
        GlFramework();
        ~GlFramework();

		ABSTRACT_FRAMEWORK_INTERFACE


        /*!
        *\brief Fonction de création d'un shader.
        */
        GLint createShader( const char* shader_prefix );

		/*!
		*\brief Recalcule la matrice de projection en utilisant les valeurs \a fovY
		*c'est à dire l'angle d'ouverture de la caméra selon l'axe Y (en degrés), le
		*\a ratio entre la longueur et la largeur de la caméra, et les distances
		*\a zNear et \a zFar correspondant respectivement aux distances de clipping
		*proches et éloignées.
		*/
		void setPerspective(GLfloat fovY, GLfloat ratio, GLfloat zNear, GLfloat zFar);

        void setOrtho(GLfloat fovY, GLfloat ratio, GLfloat zNear, GLfloat zFar);

        /*!
        *\brief Recalcule la matrive de vue en utilisant les coordonnées \a eyeX,
        *\a eyeY et \a eyeZ correspondant à la position de la caméra, les
        *coordonnées \a targetX, \a targetY et \a targetZ du point visé par la
        *caméra et les coordonnées \a upX, \a upY et \a upZ du vecteur représentant
        *l'axe vertical de la caméra.
        */
        void lookAt(GLfloat eyeX, GLfloat eyeY, GLfloat eyeZ, GLfloat targetX, GLfloat targetY, GLfloat targetZ, GLfloat upX = 0.0f, GLfloat upY = 1.0f, GLfloat upZ = 0.0f);


    protected:
		/*!
		*\brief Fonction de chargement d'un shader.
		*/
		char* loadShader( const char* file_name );

		/*!
        *\brief Fonction d'initialization d'OpenGL, appelée à la création du
        *contexte de rendu.
        */
        bool init();


	protected:
		GLMatrix pProjMatrix, pViewMatrix, pModelMatrix;
		GLMatrix pModelViewMatrix, pNormalMatrix, pMVPMatrix;
		QLinkedList<GLMatrix> pMatrixStack;
		std::vector<std::string> m_ShaderNames;
		std::vector<GLint> m_Shader;
		GLint m_CurrentShader;
};


#endif
