#ifndef Object3D_h
#define Object3D_h


#include "AbstractFramework.h"


class Object3D
{
	public:
        static void setFramework( AbstractFramework* );

	public:
        void draw();
        void draw( const char* shader_name );

	protected:
        virtual void drawShape( const char* = NULL ) = 0;


	protected:
		static AbstractFramework* m_Framework;
};


#endif
