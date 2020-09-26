#include "Particle.h"

Particle::Particle(
        int x, int y,
        int lifeLength,
        const SDL_Color &initialColor, const SDL_Color &finalColor)
    : m_x{static_cast<double>(x)}, m_y{static_cast<double>(y)},
      m_maxLife{lifeLength}, m_remainingLife{lifeLength},
      m_initialColorR{initialColor.r}, m_initialColorG{initialColor.g}, m_initialColorB{initialColor.b}, m_initialColorA{initialColor.a},
      m_finalColorR{finalColor.r}, m_finalColorG{finalColor.g}, m_finalColorB{finalColor.b}, m_finalColorA{finalColor.a}
{
}

void Particle::update()
{
    --m_remainingLife;

    double initialColorRatio{static_cast<double>(m_remainingLife) / m_maxLife};
    double finalColorRatio{1.0 - initialColorRatio};

    m_currentColorR = m_initialColorR * initialColorRatio + m_finalColorR * finalColorRatio;
    m_currentColorG = m_initialColorG * initialColorRatio + m_finalColorG * finalColorRatio;
    m_currentColorB = m_initialColorB * initialColorRatio + m_finalColorB * finalColorRatio;
    m_currentColorA = m_initialColorA * initialColorRatio + m_finalColorA * finalColorRatio;
}

void Particle::render(SDL_Renderer *renderer) const
{
    if (isDead())
        return;

    SDL_SetRenderDrawColor(renderer, m_currentColorR, m_currentColorG, m_currentColorB, m_currentColorA);
    SDL_RenderDrawPoint(renderer, m_x, m_y);
}
