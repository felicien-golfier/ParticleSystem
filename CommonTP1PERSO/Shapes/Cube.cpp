#include "Shapes/Cube.h"


GLfloat g_CubeTabColors[] =
{
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f
};

GLfloat    c_TabVertices[] =
{
    0.0f, 0.0f, 0.0f, //0
    10.0f, 0.0f, 0.0f, // 1
    0.0f, 10.0f, 0.0f, // 2
    0.0f, 0.0f, 10.0f, // 3
    10.0f, 10.0f, 0.0f,// 4
    10.0f, 0.0f, 10.0f,// 5
    0.0f, 10.0f, 10.0f,// 6
    10.0f, 10.0f, 10.0f,// 7

};

GLuint indices[] =
{
    0,1,4,
    4,2,0,
    0,1,5,
    5,3,0,
    1,4,7,
    7,5,1,
    7,6,2,
    2,4,7,
    2,6,3,
    3,0,2,
    6,7,5,
    5,3,6
};


Cube::Cube()
{

}


void
Cube::drawShape()
{
    GLint var1 = glGetAttribLocation( m_Framework->getCurrentShaderId(), "position" );
    glEnableVertexAttribArray( var1 );
    glVertexAttribPointer( var1, 3, GL_FLOAT, GL_FALSE, 0, c_TabVertices );
    GLint var2 = glGetAttribLocation( m_Framework->getCurrentShaderId(), "color" );
    glEnableVertexAttribArray( var2 );
    glVertexAttribPointer( var2, 3, GL_FLOAT, GL_FALSE, 0, g_CubeTabColors );
    glDrawElements(GL_TRIANGLES,3*12,GL_UNSIGNED_INT,indices);
    glDisableVertexAttribArray( var1 );
    glDisableVertexAttribArray( var2 );
}
