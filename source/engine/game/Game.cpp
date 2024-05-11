#include "Game.h"

#include "../scene/Scene.h"

#include <iostream>

Game::Game(int screenWidth, int screenHeight, const std::string &title):
    mWindow       (nullptr),
    mRenderer     (nullptr),
    mScene        (nullptr),
    mTitle        (title),
    mWidth        (screenWidth),
    mHeight       (screenHeight),
    mTicksCounter (0.0f),
    mIsRunning    (true),
    mIsPaused     (false)
{
    std::cout << "create 'Game'.\n";
}

Game::~Game()
{
    std::cout << "delete 'Game'.\n";
    delete mScene;
}

/* game basic commands */
bool Game::start()
{
    if( SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    SDL_DisplayMode dm;
    SDL_GetCurrentDisplayMode(0, &dm);

    int windowX = (dm.w - screenWidth() ) / 2;
    int windowY = (dm.h - screenHeight()) / 2;

    mWindow = SDL_CreateWindow(mTitle.c_str(), windowX, windowY, screenWidth(), screenHeight(), 0);
    if(!mWindow)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!mRenderer)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    Game::startScene();

    return true;
}

void Game::run()
{
    while(mIsRunning)
    {
        processInput();
        updateGame();
        generateOutput();
    }
}

void Game::shutdown()
{
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Game::quit()
{
    mIsRunning = false;
}

void Game::pause()
{
    mIsPaused = true;
}

void Game::resume()
{
    mIsPaused = false;
}

/* game info */
int Game::screenWidth() const
{
    return mWidth;
}

int Game::screenHeight() const
{
    return mHeight;
}

/* main loop */
void Game::processInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                quit();
                break;
        }
    }

    if(mScene != nullptr)
    {
        const Uint8 *keyboard = SDL_GetKeyboardState(nullptr);
        mScene->processInput(keyboard);
    }
}

void Game::updateGame()
{
    while( !SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCounter + 16) );

    float dt = (float)(SDL_GetTicks() - mTicksCounter) / 1000.0f;
    
    if(dt > 0.05f)
    {
        dt = 0.05f;
    }

    mTicksCounter = SDL_GetTicks();

    if(mScene != nullptr)
    {
        mScene->update(dt);
    }

    // SDL_Log("Delta Time : %f", dt);
}

void Game::generateOutput()
{
    SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(mRenderer);

    if(mScene != nullptr)
    {
        mScene->draw(mRenderer);
    }

    SDL_RenderPresent(mRenderer);
}

/* specific for every game */
void Game::startScene()
{
    mScene = new Scene(this);
    mScene->action();
}