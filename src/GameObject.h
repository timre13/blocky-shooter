#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <SDL2/SDL.h>

class GameObject
{
protected:
    // X position.
    int m_x;
    // Y position.
    int m_y;
    // Width.
    int m_w;
    // Height.
    int m_h;

public:
    GameObject(int x, int y, int w, int h);

    // Updates the object, for example updates the physics and animation.
    virtual inline void update() {};
    // Renders the object on the passed renderer.
    virtual void render(SDL_Renderer *renderer) const;

    virtual inline int getX() const { return m_x; }
    virtual inline int getY() const { return m_y; }
    virtual inline int getW() const { return m_w; }
    virtual inline int getH() const { return m_h; }

    virtual inline ~GameObject() {}
};

#endif /* GAMEOBJECT_H_ */
