#pragma once

#include <SDL2/SDL.h>
#include <string>

class Scene;

class Game
{
public:
    Game(int screenWidth, int screenHeight, const std::string &title="");
    ~Game();

    /* game basic commands */
    bool start();
    void run();
    void shutdown();
    void quit();
    void pause();
    void resume();

    /* game info */
    int screenWidth() const;
    int screenHeight() const;

private:
    /* main loop */
    void processInput();
    void updateGame();
    void generateOutput();

protected:
    /* specific for every game */
    virtual void startScene();

    /* 'Game' params */
    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;

    Scene *mScene;

    std::string mTitle;
    int mWidth;
    int mHeight;

    Uint32 mTicksCounter;

    bool mIsRunning;
    bool mIsPaused;
};