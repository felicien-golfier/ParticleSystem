//*****************************************************************************
//
// Class: GlFramework
// Authors: Fabrice LAURI (fabrice.lauri@utbm.fr)
//          (Associate Professor at the
//          "Université de Technologie de Belfort-Montbéliard", France)
//          Jocelyn BUISSON (jocelyn.buisson@voxelia.com)
// Version: 1.0
// Last update: 2012-05-01
//
//*****************************************************************************


#include "GlFramework.h"

#include <QMessageBox>
#include <QDebug>
#include <QGLWidget>
#include <limits>
#include <cmath>
#include "LF_String.h"
#include "Object3D.h"

#include <iostream>

using namespace std;


void
GLMatrix::setIdentity()
{
	m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
	m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
	m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
	m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
}

GLMatrix
operator*( const GLMatrix & mat1, const GLMatrix & mat2 )
{
    GLMatrix result;

    for(int idx = 0; idx < 4; idx++)
    {
        for(int idy = 0; idy < 4; idy++)
        {
            result.m[idy][idx] = 0.0f;
            for(int idz = 0; idz < 4; idz++)
            {
                result.m[idy][idx] += mat1.m[idy][idz] * mat2.m[idz][idx];
            }
        }
    }
    return result;
}

GLfloat
det( const GLMatrix & mat )
{
	GLfloat det;

	det = mat.data[0] * (mat.data[5] * mat.data[10] - mat.data[6] * mat.data[9])
		- mat.data[1] * (mat.data[4] * mat.data[10] - mat.data[6] * mat.data[8])
		+ mat.data[2] * (mat.data[4] * mat.data[9] - mat.data[5] * mat.data[8]);

	return det;
}


GLMatrix
inverse( const GLMatrix & mat )
{
	GLMatrix result;
	GLfloat d = det(mat);

	if (fabs(d) < 0.0005)
	{
		result.setIdentity();
	}
	else
	{
		d = 1.0f/d;

		result.data[0] =  (mat.data[5] * mat.data[10] - mat.data[6] * mat.data[9]) * d;
		result.data[1] = -(mat.data[1] * mat.data[10] - mat.data[9] * mat.data[2]) * d;
		result.data[2] =  (mat.data[1] * mat.data[6] - mat.data[5] * mat.data[2]) * d;

		result.data[3] = -(mat.data[4] * mat.data[10] - mat.data[6] * mat.data[8]) * d;
		result.data[4] =  (mat.data[0] * mat.data[10] - mat.data[2] * mat.data[8]) * d;
		result.data[5] = -(mat.data[0] * mat.data[6] - mat.data[2] * mat.data[4]) * d;

		result.data[6] =  (mat.data[4] * mat.data[9] - mat.data[5] * mat.data[8]) * d;
		result.data[7] = -(mat.data[0] * mat.data[9] - mat.data[1] * mat.data[8]) * d;
		result.data[8] =  (mat.data[0] * mat.data[5] - mat.data[1] * mat.data[4]) * d;
	}

	return result;
}


GlFramework::GlFramework()
{
    pViewMatrix.setIdentity();
    loadIdentity();

    m_CurrentShader = -1;
}

GlFramework::~GlFramework()
{
    for( GLuint i = 0; i < m_Shader.size(); ++i )
    {
        glDeleteProgram( m_Shader[i] );
    }
}


bool
GlFramework::init()
{
    cout << "Init GLEW" << endl;

    glewExperimental = GL_TRUE;

    GLenum error = glewInit();
    if(error != GLEW_OK)
    {
        return false;
//        QMessageBox::critical(this, trUtf8("Erreur"), trUtf8("Echec de l'initialization de GLEW: %1").arg(reinterpret_cast<const char *>(glewGetErrorString(error))));
//        exit(-1);
    }

    Object3D::setFramework( this );
}


char*
GlFramework::loadShader( const char* file_name )
{
    FILE* fp;
    char* content = NULL;
    long length;

    fp = fopen( file_name, "rb" );
    if (fp)
    {
        fseek( fp, 0, SEEK_END );
        length = ftell( fp );
        fseek( fp, 0, SEEK_SET );
        content = new char [length+1];
        fread( content, sizeof( char ), length, fp );
        fclose( fp );
        content[length] = '\0';
    }

    return content;
}

GLint
GlFramework::createShader( const char* shader_prefix )
{
    char shader_name[128];

    sprintf( shader_name, "%s.vs", shader_prefix );
    const GLchar* vs_content = loadShader( shader_name );

    sprintf( shader_name, "%s.fs", shader_prefix );
    const GLchar* fs_content = loadShader( shader_name );

    if (vs_content == NULL)
    {
        return -1;
//        QMessageBox::critical(this, trUtf8("Erreur"), trUtf8("Echec du chargement d'un shader\n"));
    }

    GLint status, logSize;
    QByteArray log;
    GLuint pProgram;

    pProgram = glCreateProgram();

    GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vshader, 1, &vs_content, NULL);
    glCompileShader(vshader);
    glGetShaderiv(vshader, GL_COMPILE_STATUS, &status);
    if(status != GL_TRUE)
    {
        glGetShaderiv(vshader, GL_INFO_LOG_LENGTH, &logSize);
        log.resize(logSize - 1);
        glGetShaderInfoLog(vshader, logSize, &logSize, log.data());

		cout << "Error: " << QString(log).toStdString().c_str() << endl;

        return -1;
//        QMessageBox::critical(this, trUtf8("Erreur"), trUtf8("Echec de la compilation du vertex shader:\n\n%1").arg(QString(log)));
//        exit(-1);
    }
    glAttachShader(pProgram, vshader);

    GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fshader, 1, &fs_content, NULL);
    glCompileShader(fshader);
    if(status != GL_TRUE)
    {
        glGetShaderiv(fshader, GL_INFO_LOG_LENGTH, &logSize);
        log.resize(logSize - 1);
        glGetShaderInfoLog(fshader, logSize, &logSize, log.data());

		cout << "Error: " << QString(log).toStdString().c_str() << endl;

		return -1;
//        QMessageBox::critical(this, trUtf8("Erreur"), trUtf8("Echec de la compilation du fragment shader:\n\n%1").arg(QString(log)));
//        exit(-1);
    }
    glAttachShader(pProgram, fshader);

    glLinkProgram(pProgram);
    glGetProgramiv(pProgram, GL_LINK_STATUS, &status);
    if(status != GL_TRUE)
    {
        glGetProgramiv(pProgram, GL_INFO_LOG_LENGTH, &logSize);
        log.resize(logSize - 1);
        glGetProgramInfoLog(pProgram, logSize, &logSize, log.data());

		cout << "Error: " << QString(log).toStdString().c_str() << endl;

		return -1;

//        QMessageBox::critical(this, trUtf8("Erreur"), trUtf8("Echec du linkage du programme:\n\n%1").arg(QString(log)));
//        exit(-1);
    }

    delete [] vs_content;
    delete [] fs_content;

    m_ShaderNames.push_back( shader_prefix );
    m_Shader.push_back( pProgram );

    return m_Shader.size()-1;
}


bool
GlFramework::useShader( GLint shader_id )
{
    if (shader_id < m_Shader.size())
    {
        if (m_CurrentShader != shader_id)
        {
//            std::cout << "Use shader: " << shader_id << std::endl;
            m_CurrentShader = shader_id;
            glUseProgram( m_Shader[shader_id] );
        }

        return true;
    }
    else
    {
        m_CurrentShader = -1;
        glUseProgram( 0 );

        return false;
    }
}

bool
GlFramework::useShader( const char* shader_name )
{
    for( GLuint id = 0; id < m_ShaderNames.size(); ++id )
    {
        if (strstr( m_ShaderNames[id].c_str(), shader_name ))
        {
            if (m_CurrentShader != id)
            {
//                std::cout << "Use shader: " << id << std::endl;
                m_CurrentShader = id;
                glUseProgram( m_Shader[id] );
            }

            return true;
        }
    }

    m_CurrentShader = -1;
    glUseProgram( 0 );

    return false;
}

GLint
GlFramework::getCurrentShaderId() const
{
    return m_Shader[m_CurrentShader];
}


void
GlFramework::transmitMVP( GLuint var_id )
{
	glUniformMatrix4fv( var_id, 1, GL_TRUE, pMVPMatrix.data );
}

void
GlFramework::transmitMV( GLuint var_id )
{
	glUniformMatrix4fv( var_id, 1, GL_TRUE, pModelViewMatrix.data );
}

void
GlFramework::transmitNM( GLuint var_id )
{
	glUniformMatrix3fv( var_id, 1, GL_FALSE, pNormalMatrix.data );
}

void
GlFramework::transmitM( GLuint var_id )
{
    glUniformMatrix4fv( var_id, 1, GL_TRUE, pModelMatrix.data );
}

void
GlFramework::transmitV( GLuint var_id )
{
	glUniformMatrix4fv( var_id, 1, GL_TRUE, pViewMatrix.data );
}

void
GlFramework::transmitP( GLuint var_id )
{
   glUniformMatrix4fv( var_id, 1, GL_TRUE, pProjMatrix.data );
}


void
GlFramework::setPerspective(GLfloat fovY, GLfloat ratio, GLfloat zNear, GLfloat zFar)
{
    GLfloat thetaY = 0.5f * (M_PI * fovY / 180.0f);
    GLfloat tanThetaY = tan(thetaY);
    GLfloat tanThetaX = tanThetaY * ratio;
    GLfloat halfW   =  tanThetaX * zNear;
    GLfloat halfH   =  tanThetaY * zNear;
    GLfloat left    = -halfW;
    GLfloat right   =  halfW;
    GLfloat bottom  = -halfH;
    GLfloat top     =  halfH;
    GLfloat iWidth  = 1.0f / (right - left);
    GLfloat iHeight = 1.0f / (top - bottom);
    GLfloat iDepth  = 1.0f / (zFar - zNear);

    pProjMatrix.m[0][0] = 2.0f * zNear * iWidth; pProjMatrix.m[0][1] = 0.0f;                   pProjMatrix.m[0][2] =  (right + left) * iWidth;  pProjMatrix.m[0][3] =  0.0f;
    pProjMatrix.m[1][0] = 0.0f;                  pProjMatrix.m[1][1] = 2.0f * zNear * iHeight; pProjMatrix.m[1][2] =  (top + bottom) * iHeight; pProjMatrix.m[1][3] =  0.0f;
    pProjMatrix.m[2][0] = 0.0f;                  pProjMatrix.m[2][1] = 0.0f;                   pProjMatrix.m[2][2] = -(zFar + zNear) * iDepth;  pProjMatrix.m[2][3] = -2.0f * (zFar * zNear) * iDepth;
    pProjMatrix.m[3][0] = 0.0f;                  pProjMatrix.m[3][1] = 0.0f;                   pProjMatrix.m[3][2] = -1.0f;                     pProjMatrix.m[3][3] =  0.0f;
}


void
GlFramework::setOrtho(GLfloat fovY, GLfloat ratio, GLfloat zNear, GLfloat zFar)
{
    GLfloat thetaY = 0.5f * (M_PI * fovY / 180.0f);
    GLfloat tanThetaY = tan(thetaY);
    GLfloat tanThetaX = tanThetaY * ratio;
    GLfloat halfW   =  tanThetaX * zNear;
    GLfloat halfH   =  tanThetaY * zNear;
    GLfloat left    = -halfW;
    GLfloat right   =  halfW;
    GLfloat bottom  = -halfH;
    GLfloat top     =  halfH;
    GLfloat iWidth  = 1.0f / (right - left);
    GLfloat iHeight = 1.0f / (top - bottom);
    GLfloat iDepth  = 1.0f / (zNear - zFar);

    pProjMatrix.m[0][0] = 2.0f * iWidth;    pProjMatrix.m[0][1] = 0.0f;             pProjMatrix.m[0][2] = 0.0f;             pProjMatrix.m[0][3] = -(right+left) * iWidth;
    pProjMatrix.m[1][0] = 0.0f;             pProjMatrix.m[1][1] = 2.0f * iHeight;   pProjMatrix.m[1][2] = 0.0f;             pProjMatrix.m[1][3] =  -(top+bottom) * iHeight;
    pProjMatrix.m[2][0] = 0.0f;             pProjMatrix.m[2][1] = 0.0f;             pProjMatrix.m[2][2] = 2.0f * iDepth;    pProjMatrix.m[2][3] = (zFar+zNear) * iDepth;
    pProjMatrix.m[3][0] = 0.0f;             pProjMatrix.m[3][1] = 0.0f;             pProjMatrix.m[3][2] = 0.0f;             pProjMatrix.m[3][3] =  1.0f;
}


void
GlFramework::lookAt(GLfloat eyeX, GLfloat eyeY, GLfloat eyeZ, GLfloat targetX, GLfloat targetY, GLfloat targetZ, GLfloat upX, GLfloat upY, GLfloat upZ)
{
    GLfloat forwardX = targetX - eyeX;
    GLfloat forwardY = targetY - eyeY;
    GLfloat forwardZ = targetZ - eyeZ;

    GLfloat forwardLen = std::sqrt(forwardX * forwardX + forwardY * forwardY + forwardZ * forwardZ);
    if(forwardLen > std::numeric_limits<GLfloat>::epsilon())
    {
    forwardX /= forwardLen;
    forwardY /= forwardLen;
    forwardZ /= forwardLen;
    }

    GLfloat upLen = std::sqrt(upX * upX + upY * upY + upZ * upZ);
    if(upLen > std::numeric_limits<GLfloat>::epsilon())
    {
    upX /= upLen;
    upY /= upLen;
    upZ /= upLen;
    }

    GLfloat sX = forwardY * upZ - forwardZ * upY;
    GLfloat sY = forwardZ * upX - forwardX * upZ;
    GLfloat sZ = forwardX * upY - forwardY * upX;

    GLfloat uX = sY * forwardZ - sZ * forwardY;
    GLfloat uY = sZ * forwardX - sX * forwardZ;
    GLfloat uZ = sX * forwardY - sY * forwardX;

    pViewMatrix.m[0][0] = sX;        pViewMatrix.m[0][1] = sY;        pViewMatrix.m[0][2] = sZ;        pViewMatrix.m[0][3] = 0.0f;
    pViewMatrix.m[1][0] = uX;        pViewMatrix.m[1][1] = uY;        pViewMatrix.m[1][2] = uZ;        pViewMatrix.m[1][3] = 0.0f;
    pViewMatrix.m[2][0] = -forwardX; pViewMatrix.m[2][1] = -forwardY; pViewMatrix.m[2][2] = -forwardZ; pViewMatrix.m[2][3] = 0.0f;
    pViewMatrix.m[3][0] = 0.0f;      pViewMatrix.m[3][1] = 0.0f;      pViewMatrix.m[3][2] = 0.0f;      pViewMatrix.m[3][3] = 1.0f;

    GLMatrix t;
    t.m[0][0] = 1.0f; t.m[0][1] = 0.0f; t.m[0][2] = 0.0f; t.m[0][3] = -eyeX;
    t.m[1][0] = 0.0f; t.m[1][1] = 1.0f; t.m[1][2] = 0.0f; t.m[1][3] = -eyeY;
    t.m[2][0] = 0.0f; t.m[2][1] = 0.0f; t.m[2][2] = 1.0f; t.m[2][3] = -eyeZ;
    t.m[3][0] = 0.0f; t.m[3][1] = 0.0f; t.m[3][2] = 0.0f; t.m[3][3] = 1.0f;

    pViewMatrix = pViewMatrix * t;
}


void
GlFramework::pushMatrix()
{
    pMatrixStack.append(pModelMatrix);
}

void
GlFramework::popMatrix()
{
    pModelMatrix = pMatrixStack.takeLast();
}

void
GlFramework::loadIdentity()
{
    pModelMatrix.setIdentity();
}

void
GlFramework::translate(GLfloat x, GLfloat y, GLfloat z)
{
    GLMatrix t;
    t.m[0][0] = 1.0f; t.m[0][1] = 0.0f; t.m[0][2] = 0.0f; t.m[0][3] = x;
    t.m[1][0] = 0.0f; t.m[1][1] = 1.0f; t.m[1][2] = 0.0f; t.m[1][3] = y;
    t.m[2][0] = 0.0f; t.m[2][1] = 0.0f; t.m[2][2] = 1.0f; t.m[2][3] = z;
    t.m[3][0] = 0.0f; t.m[3][1] = 0.0f; t.m[3][2] = 0.0f; t.m[3][3] = 1.0f;
    pModelMatrix = pModelMatrix * t;
}

void
GlFramework::rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
    GLfloat rAngle = M_PI * angle / 180.0f;
    GLfloat c = std::cos(rAngle);
    GLfloat s = std::sin(rAngle);

    GLfloat axisLen = std::sqrt(x * x + y * y + z * z);
    if(axisLen > std::numeric_limits<GLfloat>::epsilon())
    {
		x /= axisLen;
		y /= axisLen;
		z /= axisLen;
    }

    GLMatrix r;
    r.m[0][0] = x * x * (1.0f - c) + c;     r.m[0][1] = x * y * (1.0f - c) - z * s; r.m[0][2] = x * z * (1.0f - c) + y * s; r.m[0][3] = 0.0f;
    r.m[1][0] = y * x * (1.0f - c) + z * s; r.m[1][1] = y * y * (1.0f - c) + c;     r.m[1][2] = y * z * (1.0f - c) - x * s; r.m[1][3] = 0.0f;
    r.m[2][0] = z * x * (1.0f - c) - y * s; r.m[2][1] = y * z * (1.0f - c) + x * s; r.m[2][2] = z * z * (1.0f - c) + c;     r.m[2][3] = 0.0f;
    r.m[3][0] = 0.0f;                       r.m[3][1] = 0.0f;                       r.m[3][2] = 0.0f;                       r.m[3][3] = 1.0f;
    pModelMatrix = pModelMatrix * r;
}

void
GlFramework::scale(GLfloat x, GLfloat y, GLfloat z)
{
    GLMatrix s;
    s.m[0][0] = x;    s.m[0][1] = 0.0f; s.m[0][2] = 0.0f; s.m[0][3] = 0.0f;
    s.m[1][0] = 0.0f; s.m[1][1] = y;    s.m[1][2] = 0.0f; s.m[1][3] = 0.0f;
    s.m[2][0] = 0.0f; s.m[2][1] = 0.0f; s.m[2][2] = z;    s.m[2][3] = 0.0f;
    s.m[3][0] = 0.0f; s.m[3][1] = 0.0f; s.m[3][2] = 0.0f; s.m[3][3] = 1.0f;
    pModelMatrix = pModelMatrix * s;
}


void
GlFramework::computeAncillaryMatrices()
{
	pModelViewMatrix = pViewMatrix * pModelMatrix;
	pNormalMatrix = inverse( pModelViewMatrix );
	pMVPMatrix = pProjMatrix * pModelViewMatrix;
}


char* cubemaps[] =
{
  "_pX",
  "_nX",
  "_pY",
  "_nY",
  "_pZ",
  "_nZ"
};


GLuint
GlFramework::createTexture( const char* filename )
{
	GLuint texId = 0;
	QImage image;

	if (strstr( filename, "cubemap_" ))
	{
		lf::String name;

		glGenTextures( 1, &texId );
		cout << "Texture #" << texId << ": " << filename << " loaded!" << endl;

//		glEnable( GL_TEXTURE_CUBE_MAP );
		glBindTexture( GL_TEXTURE_CUBE_MAP, texId );
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP);

		for( uint32 i = 0; i < 6; ++i )
		{
			name = filename;
			name += cubemaps[i];

			if (image.load( name.c_str() ))
			{
				cout << name.c_str() << " (" << image.width() << "," << image.height() << ") loaded!" << endl;

				image = QGLWidget::convertToGLFormat( image );
				glTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits() );
			}
		}
	}
	else if (strstr( filename, "tex2d_" ))
	{
		if (image.load( filename ))
		{
			image = QGLWidget::convertToGLFormat( image );

			glGenTextures( 1, &texId );
			cout << "Texture #" << texId << ": " << filename << " (" << image.width() << "," << image.height() << ") loaded!" << endl;

//			glEnable( GL_TEXTURE_2D );
			glBindTexture( GL_TEXTURE_2D, texId );
			glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits() );
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
	}
	else if (strstr( filename, "tex1d_" ))
	{
		if (image.load( filename ))
		{
			image = QGLWidget::convertToGLFormat( image );

			glGenTextures( 1, &texId );
			cout << "Texture #" << texId << ": " << filename << " (" << image.width() << "," << image.height() << ") loaded!" << endl;

//			glDisable( GL_TEXTURE_CUBE_MAP );
//			glEnable( GL_TEXTURE_1D );
			glBindTexture( GL_TEXTURE_1D, texId );
			glTexImage1D( GL_TEXTURE_1D, 0, GL_RGBA, image.width(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits() );
			glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP );
		}
	}

	return texId;
}
