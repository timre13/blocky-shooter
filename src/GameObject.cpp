#include "GameObject.h"

GameObject::GameObject(int x, int y, int w, int h)
    : m_x{x}, m_y{y}, m_w{w}, m_h{h}
{
}

void GameObject::render(SDL_Renderer *renderer) const
{
    SDL_Rect rect{m_x, m_y, m_w, m_h};

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}
