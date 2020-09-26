#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>
#include <algorithm>

#include "Logger.h"
#include "Player.h"
#include "Block.h"
#include "ImageLoader.h"
#include "Timer.h"
#include "ParticleSource.h"

#define WINDOW_WIDTH                1536 // px
#define WINDOW_HEIGHT               1024 // px
#define BLOCK_WIDTH                 64   // px
#define BLOCK_HEIGHT                64   // px
#define PISTOL_SHOOTING_DISTANCE    64*5 // px
#define PISTOL_SHOOTING_WIDTH       1    // blocks

double GRAVITY{3.5};

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window{SDL_CreateWindow(
            "Blocky Shooter",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            0
    )};
    
    if (!window)
        std::cerr << "Failed to create window: " << SDL_GetError() << '\n';

    SDL_Renderer *renderer{SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)};

    if (!renderer)
        std::cerr << "Failed to create renderer: " << SDL_GetError() << '\n';

    SDL_Cursor *waitCursor{SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_WAIT)};
    SDL_SetCursor(waitCursor);

    //SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    ImageLoader *imageLoader{new ImageLoader{window, renderer, "img"}};
    /*
    imageLoader->loadImage("logo.bmp");
    SDL_RenderCopy(renderer, imageLoader->getImage("logo"), nullptr, nullptr);
    SDL_RenderPresent(renderer);
    */
    imageLoader->loadImage("crate.bmp");
    imageLoader->loadImage("crate.bmp", "crate_placement_allowed");
    SDL_SetTextureColorMod(imageLoader->getImage("crate_placement_allowed"), 0, 255, 0);
    SDL_SetTextureAlphaMod(imageLoader->getImage("crate_placement_allowed"), 100);
    imageLoader->loadImage("crate.bmp", "crate_placement_disallowed");
    SDL_SetTextureColorMod(imageLoader->getImage("crate_placement_disallowed"), 255, 0, 0);
    SDL_SetTextureAlphaMod(imageLoader->getImage("crate_placement_disallowed"), 100);
    for (int i{}; i < 3; ++i)
    imageLoader->loadImage("crate_broken_"+std::to_string(i)+".bmp");
    imageLoader->loadImage("player_left.bmp");
    imageLoader->loadImage("player_right.bmp");
    imageLoader->loadImage("sky.bmp");
    imageLoader->loadImage("aim_cursor.bmp");

    Timer *timer{new Timer};

    std::srand(std::time(nullptr));

    blockVector_t blockVector;

    for (int i{}; i < 300; ++i)
        blockVector.push_back(new Block{rand()%WINDOW_WIDTH, rand()%WINDOW_HEIGHT, BLOCK_WIDTH, BLOCK_HEIGHT, imageLoader});
    
    Player *player{new Player{100, 100, imageLoader, &blockVector}};

    bool isRunning{true};
    const Uint8 *keyState{SDL_GetKeyboardState(nullptr)};
    int mouseX, mouseY;
    double pistolAngle{};
    bool isBlockAtCursorPosition{};
    //Block* blockAtCursorPosition{nullptr};

    /*
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 10);
    for (int i{}; i < 50; ++i)
    {
        SDL_Delay(100);
        SDL_RenderFillRect(renderer, nullptr);
        SDL_RenderPresent(renderer);
    }
    */

//
//    auto smokeParticleSource{
//        new ParticleSource{
//            window, renderer,
//            0, 0,
//            {50, 50, 50, 255}, {100, 100, 100, 150},
//            200, 500, 40,
//            -1, -6, 6
//        }
//    };

//    int smokeParticleSourceRemainingLife{0};

    SDL_ShowCursor(false);

    while (isRunning)
    {
        timer->reset();

        SDL_GetMouseState(&mouseX, &mouseY);

        isBlockAtCursorPosition = false;
        for (Block *block : blockVector)
        {
            if (!block->isBroken() && block->getX() == mouseX/BLOCK_WIDTH*BLOCK_WIDTH && block->getY() == mouseY/BLOCK_HEIGHT*BLOCK_HEIGHT)
            {
                isBlockAtCursorPosition = true;
                //blockAtCursorPosition = block;
                break;
            }
        }

        pistolAngle = std::atan2(mouseY-(player->getY()+player->getH()/2), mouseX-(player->getX()+player->getW()/2));

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    isRunning = false;
                    break;

                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        isRunning = false;
                break;

                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_RIGHT && !isBlockAtCursorPosition)
                        blockVector.push_back(new Block{event.motion.x, event.motion.y, BLOCK_WIDTH, BLOCK_HEIGHT, imageLoader});
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        for (int i{30}; i < PISTOL_SHOOTING_DISTANCE; i += 10)
                        {
                            int currentlyCheckedX{static_cast<int>(player->getX()+player->getW()/2+std::cos(pistolAngle)*i)};
                            int currentlyCheckedY{static_cast<int>(player->getY()+player->getH()/2+std::sin(pistolAngle)*i)};

                            for (Block *block : blockVector)
                            {
                                if (abs(block->getX() - currentlyCheckedX) < BLOCK_WIDTH/2*PISTOL_SHOOTING_WIDTH &&
                                    abs(block->getY() - currentlyCheckedY) < BLOCK_HEIGHT/2*PISTOL_SHOOTING_WIDTH)
                                {
                                    block->breakIt();
//                                    smokeParticleSource->setPos(block->getX()+BLOCK_WIDTH/2, block->getY()+BLOCK_HEIGHT/2);
//                                    smokeParticleSourceRemainingLife = 300;
//
//                                    smokeParticleSource->update();
                                }
                            }
                        }
                    }
                break;
            }
        }

        if (keyState[SDL_SCANCODE_SPACE])
            player->jump(WINDOW_HEIGHT);
        if (keyState[SDL_SCANCODE_A])
            player->moveLeft();
        else if (keyState[SDL_SCANCODE_D])
            player->moveRight();
        else
            player->stopHorizontalMovement();

        player->update(WINDOW_HEIGHT);

//        if (smokeParticleSourceRemainingLife > 0)
//            smokeParticleSource->update();
//
//        if (smokeParticleSourceRemainingLife == 299)
//            smokeParticleSource->setPos(-100, -100);

        //SDL_SetRenderDrawColor(renderer, 135, 206, 250, 255);
        //SDL_RenderClear(renderer);
        
        SDL_RenderCopy(renderer, imageLoader->getImage("sky"), nullptr, nullptr);
        
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderDrawLine(renderer,
                player->getX()+player->getW()/2,
                player->getY()+player->getH()/2,
                player->getX()+player->getW()/2+PISTOL_SHOOTING_DISTANCE*std::cos(pistolAngle),
                player->getY()+player->getH()/2+PISTOL_SHOOTING_DISTANCE*std::sin(pistolAngle));

        player->render(renderer);

        for (Block *block: blockVector)
        {
            block->update();
            block->render(renderer);
        }
        
//        if (smokeParticleSourceRemainingLife > 0)
//        {
//            smokeParticleSource->render();
//            --smokeParticleSourceRemainingLife;
//        }

        {
            SDL_Rect placementHelperRect{mouseX/BLOCK_WIDTH*BLOCK_WIDTH, mouseY/BLOCK_HEIGHT*BLOCK_HEIGHT, BLOCK_WIDTH, BLOCK_HEIGHT};

            if (!isBlockAtCursorPosition)
                SDL_RenderCopy(renderer, imageLoader->getImage("crate_placement_allowed"), nullptr, &placementHelperRect);
            else
                SDL_RenderCopy(renderer, imageLoader->getImage("crate_placement_disallowed"), nullptr, &placementHelperRect);
        }

        {
            SDL_Rect aimCursorRect{mouseX-16, mouseY-16, 32, 32};

            SDL_RenderCopy(renderer, imageLoader->getImage("aim_cursor"), nullptr, &aimCursorRect);
        }

        SDL_RenderPresent(renderer);
        
        SDL_Delay(16);

        SDL_SetWindowTitle(window, ("Blocky Jumper - "+std::to_string(static_cast<int>(std::round(1.0/(timer->get()/1000000.0))))+" FPS").c_str());
    }
    
    delete player;
    for (const Block *block: blockVector)
        delete block;

    delete imageLoader;
    delete timer;

    SDL_FreeCursor(waitCursor);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
