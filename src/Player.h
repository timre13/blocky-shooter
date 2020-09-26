#ifndef PLAYER_H_
#define PLAYER_H_

#include <SDL2/SDL.h>

#include "ImageLoader.h"
#include "GameObject.h"
#include "Block.h"

extern double GRAVITY;

class Player final : public GameObject
{
protected:
    double              m_xForce{};
    double              m_yForce{1};
    int                 m_lastHorizontalMovingDirection{};

    ImageLoader         *m_imageLoaderPtr;

    const blockVector_t *m_blockVectorPtr;

public:
    Player(int x, int y, ImageLoader *imageLoader, const blockVector_t *blockVector);

    // The default update function is not used.
    virtual void update() override {};
    // Updates the physics of the player.
    virtual void update(int windowheight);
    virtual void render(SDL_Renderer *renderer) const override;

    // Returns true if the player is on the ground or touches a crate.
    virtual bool isOnTheGround(int windowHeight) const;

    virtual void jump(int windowHeight);
    virtual inline void moveRight()                 { m_xForce =  4; }
    virtual inline void moveLeft()                  { m_xForce = -4; }
    virtual inline void stopHorizontalMovement()    { m_xForce =  0; }

    virtual inline ~Player() override {}
};

#endif /* PLAYER_H_ */
