#include "Game.h"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../scene/Scene.h"

#include "../system/collision/CollisionSystem.h"

Game::Game(int screenWidth, int screenHeight, const std::string &title):
    mWindow       (nullptr),
    mRenderer     (nullptr),
    mTitle        (title),
    mWidth        (screenWidth),
    mHeight       (screenHeight),
    mTicksCounter (0.0f),
    mIsRunning    (true),
    mIsPaused     (false),
    sInputSystem  (InputSystem::GetInstance()),
    sScene        (SceneManager::GetInstance())
{

}

/* game basic commands */
bool Game::Start()
{
    if( SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    SDL_DisplayMode dm;
    SDL_GetCurrentDisplayMode(0, &dm);

    int windowX = (dm.w - ScreenWidth() ) / 2;
    int windowY = (dm.h - ScreenHeight()) / 2;

    mWindow = SDL_CreateWindow(mTitle.c_str(), windowX, windowY, ScreenWidth(), ScreenHeight(), 0);
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

    if(IMG_Init(IMG_INIT_PNG) == 0)
    {
        SDL_Log("Unable to initialize SDL_image: %s", IMG_GetError());
        return false;
    }

    if(TTF_Init() < 0)
    {
        SDL_Log("Unable to initialize TTF: %s", TTF_GetError());
        return false;
    }

    StartScene();

    return true;
}

void Game::Run()
{
    while(mIsRunning)
    {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::Shutdown()
{   
    delete sScene;
    delete sInputSystem;

    CollisionSystem *csys = CollisionSystem::GetInstance();

    delete csys;

    IMG_Quit();
    TTF_Quit();
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}


void Game::Quit()
{
    mIsRunning = false;
}

void Game::Pause()
{
    mIsPaused = true;
}

void Game::Resume()
{
    mIsPaused = false;
}

/* game info */
int Game::ScreenWidth() const
{
    return mWidth;
}

int Game::ScreenHeight() const
{
    return mHeight;
}

/* main loop */
void Game::ProcessInput()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_QUIT:
            Quit();
            break;
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            sInputSystem->HandleKeyboard(event);
            break;
        }
    }
}

void Game::UpdateGame()
{
    while( !SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCounter + 16) );

    float deltaTime = (float)(SDL_GetTicks() - mTicksCounter) / 1000.0f;
    
    if(deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }

    mTicksCounter = SDL_GetTicks();

    // SDL_Log("Delta Time : %f", deltaTime);

    sScene->Update(deltaTime);
}

void Game::GenerateOutput()
{
    SDL_RenderClear(mRenderer);
    SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xff);

    sScene->Draw();

    SDL_RenderPresent(mRenderer);
}

/* specific for every game */
void Game::StartScene()
{
    sScene->ChangeScene( new Scene(this, mRenderer) );
}