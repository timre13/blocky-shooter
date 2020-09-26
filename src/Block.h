#ifndef BLOCK_H_
#define BLOCK_H_

#include <SDL2/SDL.h>
#include <vector>

#include "ImageLoader.h"
#include "GameObject.h"

class Block final : public GameObject
{
protected:
    // The ImageLoader object where we get the textures from.
    ImageLoader        *m_imageLoader;
    // Marks whether the block is physically broken (objects fall through it).
    bool                m_isBroken{};
    // Whether the object started to break, it only appears as the texture, not physically (objects do not fall through it).
    // FIXME: the block does not always get broken when clicked on it.
    bool                m_isPartlyBroken{};
    // The current animation frame of the breaking. Not used when m_isPartlyBroken is false.
    int                 m_brokenAnimationFrame{};
    // The delay until the next animation frame in screen updates. Not used when m_isPartlyBroken is false.
    int                 m_brokenAnimationDelay{10};

public:
    Block(int x, int y, int w, int h, ImageLoader *imageLoader);

    virtual void render(SDL_Renderer *renderer) const override;
    virtual void update();

    virtual inline void breakIt() { m_isPartlyBroken = true; }

    virtual inline bool isBroken() const { return m_isBroken; }

    virtual inline ~Block() override {}
};

using blockVector_t = std::vector<Block*>;

#endif /* BLOCK_H_ */
