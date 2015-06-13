#include "Shapes/ParticleSystem.h"

ParticleSystem::~ParticleSystem()
{
    std::cout << "Averge fps : " << average_fps / nb_frames << std::endl;
    delete m_particle_container;
}

void ParticleSystem::initSystem()
{
    _lastTime = std::clock();
    _fpsTime = std::clock();

    m_particle_container = new Particle[MAX_PARTICLES];

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

    GLuint image;
    if (m_texture_url != NULL) {
        image = SOIL_load_OGL_texture
        (
         m_texture_url,
         SOIL_LOAD_AUTO,
         SOIL_CREATE_NEW_ID,
         SOIL_FLAG_INVERT_Y
        );

        glBindTexture(GL_TEXTURE_2D, image);
    }

    glEnable( GL_BLEND );
    glDepthMask(GL_FALSE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glGenerateMipmap(GL_TEXTURE_2D);

    glEnable(GL_POINT_SPRITE);
    glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
    glDrawArrays(GL_POINTS, 0, _particlesCount);
    glDisable(GL_POINT_SPRITE);
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);

    glDisableVertexAttribArray( var1 );
    glDisableVertexAttribArray( var2 );

    delete [] m_vertex_data;
    delete [] m_color_data;
    glDeleteTextures( 1, &image );
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


    current_fps = 0.060 / deltaTime*10;
//    std::cout << current_fps << std::endl;
    average_fps += current_fps;
    nb_frames++;

    // uncomment this if you want to quit the program when _particlesCount
    // reach the maximum
//    if (_particlesCount >= MAX_PARTICLES) {
//        this->~ParticleSystem();
//    }

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

            updateParticle(p);

            if (p.life > 0.0f) {

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

