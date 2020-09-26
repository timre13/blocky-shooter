#include "Block.h"

Block::Block(int x, int y, int w, int h, ImageLoader *imageLoader)
    : GameObject{0, 0, w, h}, m_imageLoader{imageLoader}
{
    m_x = x/m_w*m_w;
    m_y = y/m_h*m_h;
}

void Block::render(SDL_Renderer *renderer) const
{
    SDL_Rect dstRect{m_x, m_y, m_w, m_h};

    if (!m_isPartlyBroken)
        SDL_RenderCopy(renderer, m_imageLoader->getImage("crate"), nullptr, &dstRect);
    else if (m_brokenAnimationFrame != 3)
    {
        SDL_RenderCopy(renderer, m_imageLoader->getImage("crate_broken_"+std::to_string(m_brokenAnimationFrame)), nullptr, &dstRect);
    }
}

void Block::update()
{
    if (m_isPartlyBroken)
    {
        if (m_brokenAnimationDelay == 0)
        {
            if (m_brokenAnimationFrame < 3)
            {
                ++m_brokenAnimationFrame;
                m_brokenAnimationDelay = 10;
            }
        }
        else
            --m_brokenAnimationDelay;

        if (m_brokenAnimationFrame > 0)
            m_isBroken = true;
    }
}
