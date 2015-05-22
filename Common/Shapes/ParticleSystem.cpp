#include "Shapes/ParticleSystem.h"

ParticleSystem::ParticleSystem()
{

    _lastTime = std::clock();

    for(int i=0; i < MAX_PARTICLES; i++){
        m_particle_container[i].life = -1.0f;
    }
}


void ParticleSystem::drawShape( const char* shader_name ){


    GLint var1 = glGetAttribLocation( m_Framework->getCurrentShaderId(), "position" );
    glEnableVertexAttribArray( var1 );
    glVertexAttribPointer( var1, 3, GL_FLOAT, GL_FALSE, 0, m_vertex_data );

    GLint var2 = glGetAttribLocation( m_Framework->getCurrentShaderId(), "color" );
    glEnableVertexAttribArray( var2 );
    glVertexAttribPointer( var2, 4, GL_FLOAT, GL_FALSE, 0, m_color_data );

    if (m_texture_url != NULL) {
        GLuint image = ParticleSystem::bmp_texture_load(m_texture_url);
        glBindTexture(GL_TEXTURE_2D, image);
    }

    glEnable( GL_BLEND );
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_POINT_SPRITE);
    glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
    glDrawArrays(GL_POINTS, 0, _particlesCount);
    glDisable(GL_POINT_SPRITE);
    glDisable(GL_BLEND);

    glDisableVertexAttribArray( var1 );
    glDisableVertexAttribArray( var2 );

    delete [] m_vertex_data;
    delete [] m_color_data;
}

void ParticleSystem::draw()
{
    if (m_Framework->useShader( "particle" ))
    {

        m_Framework->computeAncillaryMatrices();
        GLint var_id = glGetUniformLocation( m_Framework->getCurrentShaderId(), "MVP" );
        m_Framework->transmitMVP( var_id );

        drawShape("particle");
    }
}

void ParticleSystem::render() {

    // Update delta time
    clock_t currentTime = std::clock();
    deltaTime = (currentTime - _lastTime) / (double) CLOCKS_PER_SEC;
    _lastTime = currentTime;

    // Generate a number of particule each millisecond,
    // but limit this to 16 ms (60 fps), or if you have 1 long frame (1sec),
    // newparticles will be huge and the next frame even longer.
    int newparticles = (int)(deltaTime * NEW_PARTICLES_PER_MILLISEC * 1000.0);
    if (newparticles > (int)(0.016f* NEW_PARTICLES_PER_MILLISEC * 1000.0))
        newparticles = (int)(0.016f* NEW_PARTICLES_PER_MILLISEC * 1000.0);

    // Initialize all new particles
    for(int i=0; i<newparticles; i++){
        int particleIndex = FindUnusedParticle();

        initializeParticle(m_particle_container[particleIndex]);
    }



    // Initialize vertex and color buffers
    m_vertex_data   = new GLfloat[MAX_PARTICLES * 3];
    m_color_data    = new GLfloat[MAX_PARTICLES * 4];

    // Bind particles to the vertex and color buffers
    _particlesCount = 0;
    for (int i=0; i < MAX_PARTICLES; i++) {

        Particle& p = m_particle_container[i]; // shortcut

        if(p.life > 0.0f){

            // Decrease life
            p.life -= deltaTime * 10.0f;

            if (p.life > 0.0f) {

                updateParticle(p);

                // Fill the GPU buffer
                m_vertex_data[3*_particlesCount+0] = p.pos.x;
                m_vertex_data[3*_particlesCount+1] = p.pos.y;
                m_vertex_data[3*_particlesCount+2] = p.pos.z;

                m_color_data[4*_particlesCount+0] = p.r;
                m_color_data[4*_particlesCount+1] = p.g;
                m_color_data[4*_particlesCount+2] = p.b;
                m_color_data[4*_particlesCount+3] = p.a;

                _particlesCount++;

            }

        }
    }

    // Finally we draw the vertex and color buffer
    this->draw();
}

/**
 * @brief ParticleSystem::FindUnusedParticle
 * Finds a Particle in ParticlesContainer which isn't used yet.(i.e. life < 0);
 * @return the last used particle index (int)
 */
int ParticleSystem::FindUnusedParticle(){

    for(int i = _lastUsedParticle; i < MAX_PARTICLES; i++){
        if (m_particle_container[i].life < 0){
            _lastUsedParticle = i;
            return i;
        }
    }

    for(int i = 0; i < _lastUsedParticle; i++){
        if (m_particle_container[i].life < 0){
            _lastUsedParticle = i;
            return i;
        }
    }

    return (_lastUsedParticle) % MAX_PARTICLES;
}


GLuint ParticleSystem::bmp_texture_load(const char *imagepath)
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

