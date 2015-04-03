#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <chrono>

#include "Walker.h"
#include "ShaderLoader.h"

typedef float FrameTime;

class Game
{
public:
    Game();
    virtual ~Game();
     void run();

protected:
private:
    const unsigned int windowWidth = 800;
    const unsigned int windowHeight = 600;
    const int walkerCount = 15;
    const float ftStep = 1.f;
    const float ftSlice = 1.f;

    const std::string shaderFile = "shaders/lightShader.frag";

    int frag_LightAttenuation = 50;

    sf::RenderWindow window { sf::VideoMode(windowWidth, windowHeight),"Followers!" };

    FrameTime lastFt = 0.f;
    FrameTime currentSlice = 0.f;
    bool running = false;

    sf::RenderTexture myRenderTexture;
    sf::Sprite spriteWorld;

    std::vector<Walker> walkers;

    private:
    void initializeWalkers();
    void checkInput();
    void update();
    void draw();

};

#endif // GAME_H
