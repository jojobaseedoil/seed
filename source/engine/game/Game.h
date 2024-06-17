#ifndef GAME_H
#define GAME_H

#include "../system/input/InputSystem.h"
#include "../utils/SceneManager.h"
#include <SDL2/SDL.h>
#include <string>

class Scene;

class Game
{
public:
    Game(int screenWidth, int screenHeight, const std::string &title="");

    /* game basic commands */
    bool Start();
    void Run();
    void Shutdown();
    void Quit();
    void Pause();
    void Resume();

    /* game info */
    int ScreenWidth() const;
    int ScreenHeight() const;

private:
    /* main loop */
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();

protected:
    /* specific for every game */
    virtual void StartScene();

protected:
    /* 'Game' params */
    SDL_Window   *mWindow;
    SDL_Renderer *mRenderer;

    std::string mTitle;
    int mWidth;
    int mHeight;

    Uint32 mTicksCounter;

    bool mIsRunning;
    bool mIsPaused;

    SceneManager *sScene;
    InputSystem  *sInputSystem;
};

#endif // GAME_H