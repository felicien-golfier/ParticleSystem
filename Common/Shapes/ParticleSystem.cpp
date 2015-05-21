#include "Shapes/ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
    for( GLuint i = 0; i < 8*3; ++i )
    {
        m_TabColors[i] = 1.0f;
    }

    _lastTime = std::clock();

    for(int i=0; i<MaxParticles; i++){
        ParticlesContainer[i].life = -1.0f;
    }
}


void ParticleSystem::drawShape( const char* shader_name ){

    GLuint image = ParticleSystem::bmp_texture_load("../../textures/test.bmp");

    GLint var1 = glGetAttribLocation( m_Framework->getCurrentShaderId(), "position" );
    glEnableVertexAttribArray( var1 );
//    glVertexAttribPointer( var1, 3, GL_FLOAT, GL_FALSE, 0, m_TabVertices );
    glVertexAttribPointer( var1, 3, GL_FLOAT, GL_FALSE, 0, g_particule_position_size_data );

    GLint var2 = glGetAttribLocation( m_Framework->getCurrentShaderId(), "color" );
    glEnableVertexAttribArray( var2 );
    glVertexAttribPointer( var2, 3, GL_FLOAT, GL_FALSE, 0, g_particule_color_data );

    glBindTexture(GL_TEXTURE_2D, image);

    glEnable(GL_POINT_SPRITE);
    glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
    glDrawArrays(GL_POINTS, 0, ParticlesCount);
    glDisable(GL_POINT_SPRITE);

    glDisableVertexAttribArray( var1 );
    glDisableVertexAttribArray( var2 );

    delete [] g_particule_position_size_data;
    delete [] g_particule_color_data;
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

void ParticleSystem::update() {
//    std::cout << "test" << std::endl;
//    m_TabVertices[0] += 0.001;

    // Update delta time
    clock_t currentTime = std::clock();
    double delta = (currentTime - _lastTime) / (double) CLOCKS_PER_SEC;
    _lastTime = currentTime;


    g_particule_position_size_data = new GLfloat[MaxParticles ];
    g_particule_color_data         = new GLfloat[MaxParticles];

//    std::cout << delta << std::endl;
    // Generate 10 new particule each millisecond,
    // but limit this to 16 ms (60 fps), or if you have 1 long frame (1sec),
    // newparticles will be huge and the next frame even longer.
    int newparticles = (int)(delta*10000.0);
    if (newparticles > (int)(0.016f*10000.0))
        newparticles = (int)(0.016f*10000.0);

    for(int i=0; i<newparticles; i++){
        int particleIndex = FindUnusedParticle();
        ParticlesContainer[particleIndex].life = 5.0f; // This particle will live 5 seconds.
        ParticlesContainer[particleIndex].pos = glm::vec3(0,0,0); // and begin from center

        float spread = 1.2f;
        glm::vec3 maindir = glm::vec3(0.0f, 10.0f, 0.0f);
        // Very bad way to generate a random direction;
        // See for instance http://stackoverflow.com/questions/5408276/python-uniform-spherical-distribution instead,
        // combined with some user-controlled parameters (main direction, spread, etc)
        glm::vec3 randomdir = glm::vec3(
            (rand()%2000 - 1000.0f)/1000.0f,
            (rand()%2000 - 1000.0f)/1000.0f,
            (rand()%2000 - 1000.0f)/1000.0f
        );

        ParticlesContainer[particleIndex].speed = maindir + randomdir * spread;


        // Very bad way to generate a random color
        ParticlesContainer[particleIndex].r = 1.0f;
        ParticlesContainer[particleIndex].g = 1.0f;
        ParticlesContainer[particleIndex].b = 1.0f;
        ParticlesContainer[particleIndex].a = 1.0f;

    }



    // Simulate all particles
    ParticlesCount = 0;
    for(int i=0; i<MaxParticles; i++){

        Particle& p = ParticlesContainer[i]; // shortcut

//        std::cout << p.life << std::endl;
        if(p.life > 0.0f){

            // Decrease life
            p.life -= delta;
            if (p.life > 0.0f){

                // Simulate simple physics : gravity only, no collisions
                p.speed += glm::vec3(0.0f,-9.81f, 0.0f) * (float)delta;
                p.pos += p.speed * (float)delta * 0.5f;
//                ParticlesContainer[i].pos += glm::vec3(0.0f,10.0f, 0.0f) * (float)delta;

                // Fill the GPU buffer
                g_particule_position_size_data[3*ParticlesCount+0] = p.pos.x;
                g_particule_position_size_data[3*ParticlesCount+1] = p.pos.y;
                g_particule_position_size_data[3*ParticlesCount+2] = p.pos.z;

                g_particule_color_data[3*ParticlesCount+0] = p.r;
                g_particule_color_data[3*ParticlesCount+1] = p.g;
                g_particule_color_data[3*ParticlesCount+2] = p.b;

            }

            ParticlesCount++;

        }
    }

//    std::cout << ParticlesCount << std::endl;
}

/**
 * @brief ParticleSystem::FindUnusedParticle
 * Finds a Particle in ParticlesContainer which isn't used yet.(i.e. life < 0);
 * @return the last used particle index (int)
 */
int ParticleSystem::FindUnusedParticle(){

    for(int i=LastUsedParticle; i<MaxParticles; i++){
        if (ParticlesContainer[i].life < 0){
            LastUsedParticle = i;
            return i;
        }
    }

    for(int i=0; i<LastUsedParticle; i++){
        if (ParticlesContainer[i].life < 0){
            LastUsedParticle = i;
            return i;
        }
    }

    return 0; // All particles are taken, override the first one
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

