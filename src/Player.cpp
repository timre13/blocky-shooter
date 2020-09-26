#include "Player.h"

Player::Player(int x, int y, ImageLoader *imageLoader, const blockVector_t *blockVector)
    : GameObject{x, y, 32, 64}, m_imageLoaderPtr{imageLoader}, m_blockVectorPtr{blockVector}
{
}

void Player::update(int windowHeight)
{
    m_x += m_xForce;
    m_y += m_yForce*GRAVITY;

    if (m_xForce > 0)
        m_lastHorizontalMovingDirection = 1;
    else if (m_xForce < 0)
        m_lastHorizontalMovingDirection = -1;

    if (isOnTheGround(windowHeight))
        m_yForce = 0;
    else if (m_yForce <= 3)
        m_yForce += 0.2;
}

void Player::render(SDL_Renderer *renderer) const
{
    SDL_Rect rect{m_x-8, m_y, m_w+16, m_h};
    //SDL_Rect outlineRect{m_x, m_y, m_w, m_h};

    if (m_lastHorizontalMovingDirection < 0)
        SDL_RenderCopy(renderer, m_imageLoaderPtr->getImage("player_left"), nullptr, &rect);
    else
        SDL_RenderCopy(renderer, m_imageLoaderPtr->getImage("player_right"), nullptr, &rect);

    /*
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &outlineRect);
    */
}

bool Player::isOnTheGround(int windowHeight) const
{
    if (m_y >= windowHeight-m_h)
        return true;

    for (const Block *block: *m_blockVectorPtr)
        if (!block->isBroken() && block->getY() <= m_y+m_h && block->getY()+block->getH() >= m_y && block->getX()+block->getW() >= m_x && block->getX() <= m_x+m_w)
            return true;

    return false;
}

void Player::jump(int windowHeight)
{
    if (isOnTheGround(windowHeight))
        m_yForce -= 3;
}

