#ifndef AbstractFramework_h
#define AbstractFramework_h


#include <GL/glew.h>


class AbstractFramework
{
    public:
		/*!
		*\brief Utilisation d'un shader.
		*/
		virtual bool useShader( GLint shader_id ) = 0;
        virtual bool useShader( const char* shader_name ) = 0;

		/*!
		*\brief Id du shader actuel.
		*/
		virtual GLint getCurrentShaderId() const = 0;

		/*!
		*\brief Transmet la matrice MVP = P*V*M au shader actif.
		*/
		virtual void transmitMVP( GLuint var_id ) = 0;

		/*!
		*\brief Transmet la matrice MV = V*M au shader actif.
		*/
		virtual void transmitMV( GLuint var_id ) = 0;

		/*!
		*\brief Transmet la transposée inverse de la matrice MV = ((V*M)^-1)T au shader actif.
		*/
		virtual void transmitNM( GLuint var_id ) = 0;

		/*!
		*\brief Transmet la matrice M au shader actif.
		*/
		virtual void transmitM( GLuint var_id ) = 0;

		/*!
		*\brief Transmet la matrice V au shader actif.
		*/
		virtual void transmitV( GLuint var_id ) = 0;

		/*!
		*\brief Transmet la matrice P au shader actif.
		*/
		virtual void transmitP( GLuint var_id ) = 0;

		/*!
		*\brief Enregistre la matrice de transformation courante sur le sommet de la
		*pile de matrices.
		*/
		virtual void pushMatrix() = 0;

		/*!
		*\brief Remplace la matrice de transformation courante par celle se trouvant
		*au sommet de la pile de matrices.
		*/
		virtual void popMatrix() = 0;

		/*!
		*\brief Remplace la matrice de transformation courante par une matrice
		*identité.
		*/
		virtual void loadIdentity() = 0;

		/*!
		*\brief Multiplie la matrice de transformation courante par une matrice de
		*translation utilisant le vecteur de coordonnées \a x, \a y et \a z.
		*/
        virtual void translate(GLfloat x, GLfloat y, GLfloat z) = 0;

		/*!
		*\brief Multiplie la matrice de transformation courante par une matrice de
		*rotation utilisant l'angle \a angle (en degrés) et l'axe représenté par le
		*vecteur de coordonnées \a x, \a y et \a z.
		*/
		virtual void rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z) = 0;

		/*!
		*\brief Multiplie la matrice de transformation courante par une matrice de
		*changement d'échelle utilisant les facteurs \a x, \a y et \a z.
		*/
		virtual void scale(GLfloat x, GLfloat y, GLfloat z) = 0;

		virtual void computeAncillaryMatrices() = 0;

		virtual GLuint createTexture( const char* filename ) = 0;
};


#define ABSTRACT_FRAMEWORK_INTERFACE \
	bool useShader( GLint shader_id ); \
	bool useShader( const char* shader_name ); \
	GLint getCurrentShaderId() const; \
	void transmitMVP( GLuint var_id ); \
	void transmitMV( GLuint var_id ); \
	void transmitNM( GLuint var_id ); \
	void transmitM( GLuint var_id ); \
	void transmitV( GLuint var_id ); \
	void transmitP( GLuint var_id ); \
	void pushMatrix(); \
	void popMatrix(); \
	void loadIdentity(); \
	void translate(GLfloat x, GLfloat y, GLfloat z); \
	void rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z); \
	void scale(GLfloat x, GLfloat y, GLfloat z); \
	void computeAncillaryMatrices(); \
	GLuint createTexture( const char* filename ); \


#endif
