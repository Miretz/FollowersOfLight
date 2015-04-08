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
    virtual ~Game() = default;
    void run();

protected:
private:

    const float ftStep = 1.f;
    const float ftSlice = 1.f;
    FrameTime lastFt = 0.f;
    FrameTime currentSlice = 0.f;

    unsigned int windowWidth;
    unsigned int windowHeight;
    int walkerCount;

    std::string shaderFile;
    sf::Shader* shader;

    bool running;

    sf::RenderWindow window;
    sf::RenderTexture myRenderTexture;
    sf::Sprite spriteWorld;

    std::vector<Walker> walkers;
    std::vector<sf::Vertex> vertices;

private:
    void initializeWalkers();
    void checkInput();
    void update();
    void draw();

};

#endif // GAME_H
