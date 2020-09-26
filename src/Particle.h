#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <SDL2/SDL.h>

/*
 * A particle.
 * Used by the ParticleSource class.
 * Cannot and should not be instantiated by any other class or function.
 */
class Particle final
{
private:
    double  m_x;
    double  m_y;
    int     m_maxLife;
    int     m_remainingLife;

    Uint8   m_initialColorR;
    Uint8   m_initialColorG;
    Uint8   m_initialColorB;
    Uint8   m_initialColorA;

    Uint8   m_finalColorR;
    Uint8   m_finalColorG;
    Uint8   m_finalColorB;
    Uint8   m_finalColorA;

    Uint8   m_currentColorR{};
    Uint8   m_currentColorG{};
    Uint8   m_currentColorB{};
    Uint8   m_currentColorA{};

    friend class ParticleSource;

    Particle(
            int x, int y,
            int lifeLength,
            const SDL_Color &initialColor, const SDL_Color &finalColor);

    inline int getX() const { return m_x; }
    inline int getY() const { return m_y; }
    inline void moveX(double plusX) { m_x += plusX; }
    inline void moveY(double plusY) { m_y += plusY; }

    inline int getRemainingLife() const { return m_remainingLife; }
    inline int isDead() const { return m_remainingLife <= 0; }

    void update();
    void render(SDL_Renderer *renderer) const;
};

#endif /* PARTICLE_H_ */
