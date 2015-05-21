//*****************************************************************************
//
// Classes: MulticolorCube, TwoColorCube, MultipleColorCube
// Author: Fabrice LAURI (fabrice.lauri@utbm.fr)
//         (Associate Professor at the
//          "Université de Technologie de Belfort-Montbéliard", France)
// Version: 1.0
// Last update: 2012-05-01
//
//*****************************************************************************


#include "Shapes/Cubes.h"

#include "GlFramework.h"
#include <stdio.h>
#include <string.h>
#include <iostream>

GlFramework framework;
const GLfloat size = 0.5f;


GLfloat mc_tab_vertices[] =
{
    -size, -size,  size,
     size, -size,  size,
    -size,  size,  size,
     size,  size,  size,
    -size, -size, -size,
     size, -size, -size,
    -size,  size, -size,
     size,  size, -size
};

GLfloat mc_tab_colors[] =
{
    1,0,0,	// Red
    0,1,0,	// Green
    0,0,1,	// Blue
    0,1,1,	// Cyan
    1,1,0,	// Yellow
    1,0,1,	// Purple
    0,0,0,	// Black
    1,1,1	// White
};

GLuint mc_tab_indices[] =
{
    0, 1, 2, 3, 7, 1, 5, 4, 7, 6, 2, 4, 0, 1
};

GLuint mc_buffers[3];


GLuint g_CubeFaces[] =
{
    4, 0, 6, 2, // Left
    1, 5, 3, 7, // Right
    4, 5, 0, 1,	// Down
    2, 3, 6, 7, // Up
    4, 5, 6, 7,	// Back
    0, 1, 2, 3	// Front
};

GLfloat g_TabTexCoords[] =
{
    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,
};


MulticolorCube::MulticolorCube()
{
    m_VBO = false;
    std::cout << "Multi" << std::endl;
}

void MulticolorCube::initVBO()
{
    glGenBuffers( 3, mc_buffers );
    glBindBuffer( GL_ARRAY_BUFFER, mc_buffers[0] );
    glBufferData( GL_ARRAY_BUFFER, 8*3*sizeof(GLfloat), mc_tab_vertices, GL_STATIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, mc_buffers[1] );
    glBufferData( GL_ARRAY_BUFFER, 8*3*sizeof(GLfloat), mc_tab_colors, GL_STATIC_DRAW );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, mc_buffers[2] );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, 14*sizeof(GLuint), mc_tab_indices, GL_STATIC_DRAW );
    m_VBO = true;
}

void MulticolorCube::drawShape( const char* shader_name )
{
    glEnableVertexAttribArray( 0 );
    glEnableVertexAttribArray( 1 );

    if (m_VBO)
    {
        glBindBuffer( GL_ARRAY_BUFFER, mc_buffers[0] );
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, 0 );
        glBindBuffer( GL_ARRAY_BUFFER, mc_buffers[1] );
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, 0 );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, mc_buffers[2] );
        glDrawElements( GL_TRIANGLE_STRIP, 14, GL_UNSIGNED_INT, 0 );
    }
    else
    {
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, mc_tab_vertices );
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, mc_tab_colors );
        glDrawElements( GL_TRIANGLE_STRIP, 14, GL_UNSIGNED_INT, mc_tab_indices );
    }

    glDisableVertexAttribArray( 0 );
    glDisableVertexAttribArray( 1 );
}


GLfloat tfcc_tab_vertices[] =
{
    -size, -size,  size,
     size, -size,  size,
    -size,  size,  size,
     size,  size,  size,
    -size, -size, -size,
     size, -size, -size,
    -size,  size, -size,
     size,  size, -size,

     -size, -size,  size,
      size, -size,  size,
     -size,  size,  size,
      size,  size,  size,
     -size, -size, -size,
      size, -size, -size,
     -size,  size, -size,
      size,  size, -size
};

GLfloat tfcc_tab_colors[] =
{
    1,0,0,
    1,0,0,
    1,0,0,
    1,0,0,
    1,0,0,
    1,0,0,
    1,0,0,
    1,0,0,

    0,0,1,
    0,0,1,
    0,0,1,
    0,0,1,
    0,0,1,
    0,0,1,
    0,0,1,
    0,0,1
};

GLuint tfcc_tab1_indices[] =
{
    0,1,2,
    1,2,3,
    4,5,6,
    5,6,7,
};

GLuint tfcc_tab2_indices[] =
{
    12,9,13,11,15,10,14,8,12,9
};


void TwoColorCube::drawShape( const char* shader_name )
{
    glEnableVertexAttribArray( 0 );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, tfcc_tab_vertices );
    glEnableVertexAttribArray( 1 );
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, tfcc_tab_colors );
    glDrawElements( GL_TRIANGLES, 12, GL_UNSIGNED_INT, tfcc_tab1_indices );
    glDrawElements( GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_INT, tfcc_tab2_indices );
    glDisableVertexAttribArray( 0 );
    glDisableVertexAttribArray( 1 );
}


MultipleColorCube::MultipleColorCube() : ParametricShape( 24 )
{
    int i;
    int n;
    int face_id;
    int vertex_id;

    m_TabTexCoords = new GLfloat [24*2];

    for( i = 0; i < 24; ++i )
    {
        n = g_CubeFaces[i]*3;
        m_TabVertices[i*3+0] = mc_tab_vertices[n+0];
        m_TabVertices[i*3+1] = mc_tab_vertices[n+1];
        m_TabVertices[i*3+2] = mc_tab_vertices[n+2];

        vertex_id = i % 4;
        vertex_id *= 2;
        m_TabTexCoords[i*2+0] = g_TabTexCoords[vertex_id+0];
        m_TabTexCoords[i*2+1] = g_TabTexCoords[vertex_id+1];

        face_id = i/4;
        face_id *= 3;
        m_TabColors[i*3+0] = mc_tab_colors[face_id+0];
        m_TabColors[i*3+1] = mc_tab_colors[face_id+1];
        m_TabColors[i*3+2] = mc_tab_colors[face_id+2];
    }

    m_NbrIndices = 3*2*6;
    m_TabIndices = new GLuint [m_NbrIndices];

    int face;
    int shift;
    face_id = 0;
    for( i = 0; i < 12; ++i )
    {
        face = face_id/2;
        shift = face_id % 2;
        m_TabIndices[i*3+0] = face*4+shift+0;
        m_TabIndices[i*3+1] = face*4+shift+1;
        m_TabIndices[i*3+2] = face*4+shift+2;

        ++face_id;
    }

    m_Border = 0.0f;
}

MultipleColorCube::~MultipleColorCube()
{
    delete [] m_TabIndices;
    delete [] m_TabTexCoords;
}


void
MultipleColorCube::setBorder( GLfloat border )
{
    m_Border = border;
}


void
MultipleColorCube::setFaceColor( int face_id, GLfloat r, GLfloat g, GLfloat b )
{
    face_id *= 12;
    for( int i = 0; i < 12; i += 3 )
    {
        m_TabColors[face_id+i+0] = r;
        m_TabColors[face_id+i+1] = g;
        m_TabColors[face_id+i+2] = b;
    }
}


void
MultipleColorCube::initArrays()
{
    ParametricShape::initArrays();
    glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 0, m_TabTexCoords );
}


void
MultipleColorCube::drawShape( const char* shader_name )
{


    if (!strcmp( (char*) shader_name, "colorntex" ))
    {
        GLuint n = glGetUniformLocation( m_Framework->getCurrentShaderId(), "border" );
        glUniform1f( n, m_Border );

        glEnableVertexAttribArray( 0 );
        glEnableVertexAttribArray( 1 );
        glEnableVertexAttribArray( 2 );
        initArrays();
        glDrawElements( GL_TRIANGLES, m_NbrIndices, GL_UNSIGNED_INT, m_TabIndices );
        glDisableVertexAttribArray( 0 );
        glDisableVertexAttribArray( 1 );
        glDisableVertexAttribArray( 2 );
    }
    else if (!strcmp( (char*) shader_name, "point" ))
    {

        glEnableVertexAttribArray( 0 );
        glEnableVertexAttribArray( 1 );
        initArrays();
        glDrawElements( GL_POINTS, m_NbrIndices, GL_UNSIGNED_INT, m_TabIndices );
        glDisableVertexAttribArray( 0 );
        glDisableVertexAttribArray( 1 );

    } else if(!strcmp( (char*) shader_name, "particle")) {

        GLuint image = bmp_texture_load("C:\\Users\\Sarry\\Documents\\Taf\\IN55\\TP1\\textures\\test.bmp");

        glEnableVertexAttribArray( 0 );
        glEnableVertexAttribArray( 1 );
        glBindTexture(GL_TEXTURE_2D, image);
        glEnable(GL_POINT_SPRITE);
        glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
        initArrays();
        glDrawElements( GL_POINTS, m_NbrIndices, GL_UNSIGNED_INT, m_TabIndices );
        glDisableVertexAttribArray( 0 );
        glDisableVertexAttribArray( 1 );

        glDisable(GL_POINT_SPRITE);


    }
      else {

            glEnableVertexAttribArray( 0 );
            glEnableVertexAttribArray( 1 );
            initArrays();
            glDrawElements( GL_TRIANGLES, m_NbrIndices, GL_UNSIGNED_INT, m_TabIndices );
            glDisableVertexAttribArray( 0 );
            glDisableVertexAttribArray( 1 );
    }
}

GLuint MultipleColorCube::bmp_texture_load(const char *imagepath)
{
    // Data read from the header of the BMP file
    unsigned char header[54]; // Each BMP file begins by a 54-bytes header
    unsigned int dataPos;     // Position in the file where the actual data begins
    unsigned int width, height;
    unsigned int imageSize;   // = width*height*3
    // Actual RGB data
    unsigned char * data;

    // Open the file
    FILE * file = fopen(imagepath,"rb");
    if (!file){
        printf("Image could not be opened\n"); return 0;
    }

    if ( fread(header, 1, 54, file)!=54 ){ // If not 54 bytes read : problem
        printf("Not a correct BMP file\n");
        std::cout << "nop" << std::endl;
        return false;
    }
    if ( header[0]!='B' || header[1]!='M' ){
        printf("Not a correct BMP file\n");
        return 0;
    }

    // Read ints from the byte array
    dataPos    = *(int*)&(header[0x0A]);
    imageSize  = *(int*)&(header[0x22]);
    width      = *(int*)&(header[0x12]);
    height     = *(int*)&(header[0x16]);

    // Some BMP files are misformatted, guess missing information
    if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
    if (dataPos==0)      dataPos=54; // The BMP header is done that way

    // Create a buffer
    data = new unsigned char [imageSize];

    // Read the actual data from the file into the buffer
    fread(data,1,imageSize,file);

    //Everything is in memory now, the file can be closed
    fclose(file);

    // Create one OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    return textureID;
}


void
MultipleColorCube::draw()
{
    if (m_Framework->useShader( "color" ))
    {
        m_Framework->computeAncillaryMatrices();
        GLint var_id = glGetUniformLocation( m_Framework->getCurrentShaderId(), "MVP" );
        m_Framework->transmitMVP( var_id );

        drawShape( "color" );
    }
}

void
 MultipleColorCube::draw(bool isPoint)
 {
    if (isPoint){
         if (m_Framework->useShader( "point" ))
         {

             m_Framework->computeAncillaryMatrices();
             GLint var_id = glGetUniformLocation( m_Framework->getCurrentShaderId(), "MVP" );
             m_Framework->transmitMVP( var_id );

             drawShape("point");

         }
    }else {

        if (m_Framework->useShader( "particle" ))
        {

            m_Framework->computeAncillaryMatrices();
            GLint var_id = glGetUniformLocation( m_Framework->getCurrentShaderId(), "MVP" );
            m_Framework->transmitMVP( var_id );

            drawShape("particle");
        }
    }
 }

