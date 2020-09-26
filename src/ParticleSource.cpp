#include "ParticleSource.h"
#include <cstdlib>
#include <ctime>
#include <cassert>

ParticleSource::ParticleSource(
        SDL_Window *window, SDL_Renderer *renderer,
        int x, int y,
        const SDL_Color &initialParticleColor, const SDL_Color &finalParticleColor,
        int maxParticleLifeLength, int maxParticleSpawnAmount, int maxParticleSpawnDistance,
        double particleYSpeed, double minParticleXMovement, double maxParticleXMovement)
    : m_windowPtr{window}, m_rendererPtr{renderer},
      m_x{x}, m_y{y},
      m_initialParticleColorR{initialParticleColor.r}, m_initialParticleColorG{initialParticleColor.g}, m_initialParticleColorB{initialParticleColor.b}, m_initialParticleColorA{initialParticleColor.a},
      m_finalParticleColorR{finalParticleColor.r}, m_finalParticleColorG{finalParticleColor.g}, m_finalParticleColorB{finalParticleColor.b}, m_finalParticleColorA{finalParticleColor.a},
      m_maxParticleLifeLength{maxParticleLifeLength}, m_maxParticleSpawnAmount{maxParticleSpawnAmount}, m_maxParticleSpawnDistance{maxParticleSpawnDistance},
      m_particleYSpeed{particleYSpeed}, m_minParticleXMovement{minParticleXMovement}, m_maxParticleXMovement{maxParticleXMovement}
{
    assert(maxParticleLifeLength > 0);
    assert(maxParticleSpawnAmount > 0);
    assert(minParticleXMovement <= maxParticleXMovement);

    // Seed the random number generator.
    std::srand(std::time(nullptr));

    // Set the blend mode to blend, so we can use transparency.
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

void ParticleSource::update()
{
    for (int i{}; i < rand() % m_maxParticleSpawnAmount + 1; ++i)
    {
        // Create new particle
        m_particles.push_back(
            new Particle{
                m_x + rand() % m_maxParticleSpawnDistance - m_maxParticleSpawnDistance / 2 + 1,
                m_y + rand() % m_maxParticleSpawnDistance - m_maxParticleSpawnDistance / 2 + 1,
                rand() % m_maxParticleLifeLength + 1,
                {m_initialParticleColorR, m_initialParticleColorG, m_initialParticleColorB, m_initialParticleColorA},
                {m_finalParticleColorR, m_finalParticleColorG, m_finalParticleColorB, m_finalParticleColorA}
            }
        );
    }

    // Update the particles
    for (Particle *particle : m_particles)
        particle->update();

    // Move the particles in the y axis.
    for (Particle *particle : m_particles)
        particle->moveY(m_particleYSpeed + rand() % 2);

    // Move the particles in the x axis.
    for (Particle *particle : m_particles)
        particle->moveX(rand() / (RAND_MAX + 1.0) * (m_maxParticleXMovement - m_minParticleXMovement) + m_minParticleXMovement);
}

void ParticleSource::render()
{
    int winW;
    int winH;

    SDL_GetWindowSize(m_windowPtr, &winW, &winH);

    for (Particle *particle : m_particles)
    {
        int particleX{particle->getX()};
        int particleY{particle->getY()};

        // If the particle is not on the screen, don't render it.
        if (particleX < 0 || particleX > winW || particleY < 0 || particleY > winH)
            continue;

        particle->render(m_rendererPtr);
    }
}

ParticleSource::~ParticleSource()
{
    for (Particle *particle : m_particles)
        delete particle;
}
