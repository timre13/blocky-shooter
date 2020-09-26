#ifndef PARTICLESOURCE_H_
#define PARTICLESOURCE_H_

#include <SDL2/SDL.h>
#include <vector>

#include "Particle.h"

/*
 * A particle system for SDL2.
 */
class ParticleSource final
{
private:
    SDL_Window              *m_windowPtr;
    SDL_Renderer            *m_rendererPtr;

    int                     m_x;
    int                     m_y;

    Uint8                   m_initialParticleColorR;
    Uint8                   m_initialParticleColorG;
    Uint8                   m_initialParticleColorB;
    Uint8                   m_initialParticleColorA;

    Uint8                   m_finalParticleColorR;
    Uint8                   m_finalParticleColorG;
    Uint8                   m_finalParticleColorB;
    Uint8                   m_finalParticleColorA;

    int                     m_maxParticleLifeLength;
    int                     m_maxParticleSpawnAmount;
    int                     m_maxParticleSpawnDistance;

    double                  m_particleYSpeed;
    double                  m_minParticleXMovement;
    double                  m_maxParticleXMovement;


    std::vector<Particle*>  m_particles;

public:
    /*
     * Initializes the particle system.
     *
     * window:                      the window where to draw the particles. This must not be a nullptr.
     * renderer:                    the renderer of the window. This must not be a nullptr.
     * x and y:                     the coordinates of the source.
     * initialParticleColor:        the color of the particles when they are created.
     * finalParticleColor:          the color of the particles at the end of their lives.
     * maxParticleLifeLength:       the maximum number of frames to live each particle.
     * maxParticleSpawnAmount:      maximum number of particles to spawn in one frame.
     * maxParticleSpawnDistance:    maximum distance from the center of the ParticleSource to spawn particles.
     * particleYSpeed:              speed of the particles in the y axis. Specify a negative value to make them fly up.
     * minParticleXMovement:        minimum speed of the particles in the x axis. Usually negative.
     * maxParticleXMovement:        maximum speed of the particles in the x axis. Usually positive.
     */
    ParticleSource(
            SDL_Window *window, SDL_Renderer *renderer,
            int x, int y,
            const SDL_Color &initialParticleColor, const SDL_Color &finalParticleColor,
            int maxParticleLifeLength, int maxParticleSpawnAmount, int maxParticleSpawnDistance,
            double particleYSpeed, double minParticleXMovement, double maxParticleXMovement);

    /*
     * Updates the particles.
     */
    void update();

    /*
     * Renders the particles to the renderer specified in the constructor.
     */
    void render();

    inline void setPos(int newX, int newY) { m_x = newX; m_y = newY; }

    /*
     * Destructor for ParticleSystem objects.
     *
     * Does not free the window and the renderer.
     */
    ~ParticleSource();
};

#endif /* PARTICLESOURCE_H_ */
