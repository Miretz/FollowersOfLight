#include "Game.h"

Game::Game()
{
    window.setFramerateLimit(500);
    initializeWalkers();

    //preload shader
    ShaderLoader::getShader(shaderFile);
}

Game::~Game()
{
    //dtor
}


void Game::run()
{
    myRenderTexture.create(windowWidth, windowHeight);
    spriteWorld.setTexture(myRenderTexture.getTexture());
    spriteWorld.setOrigin(spriteWorld.getTextureRect().width / 2.f, spriteWorld.getTextureRect().height / 2.f);
    spriteWorld.setPosition(windowWidth / 2.f, windowHeight / 2.f);

    running = true;

    while (running)
    {

        auto time1(std::chrono::high_resolution_clock::now());

        window.clear(sf::Color::Black);
        myRenderTexture.clear();

        checkInput();
        update();
        draw();

        auto time2(std::chrono::high_resolution_clock::now());
        auto elapsedTime(time2 - time1);
        FrameTime ft { std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(elapsedTime).count() };

        lastFt = ft;

        auto ftSeconds(ft / 1000.f);
        if (ftSeconds > 0.f)
        {
            auto fps(1.f / ftSeconds);
            window.setTitle("FT: " + std::to_string(ft) + "\tFPS: " + std::to_string(fps));
        }
    }
}



//private


void Game::initializeWalkers()
{
    walkers.clear();
    for (int a { 0 }; a < walkerCount; ++a)
    {

        walkers.emplace_back(window.getSize().x / 2.f,
                             window.getSize().y / 2.f);
    }
}

void Game::checkInput()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            running = false;
        }
        else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
        {
            running = false;
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            Walker::changeStrenght();
        }
    }

}

void Game::update()
{
    currentSlice += lastFt;

    //update multiple times based on fps
    for (; currentSlice >= ftSlice; currentSlice -= ftSlice)
    {
        for (auto& walker : walkers)
        {
            walker.update(ftStep, window);
        }
    }
}

void Game::draw()
{
    for (auto& walker : walkers)
    {

        walker.draw(myRenderTexture);

        sf::Shader* shader = ShaderLoader::getShader(shaderFile);
        shader->setParameter("frag_ScreenResolution", sf::Vector2f(static_cast<float>(windowWidth), static_cast<float>(windowHeight)));
        shader->setParameter("frag_LightOrigin", walker.getPosition());
        shader->setParameter("frag_LightColor", walker.getColor());
        shader->setParameter("frag_LightAttenuation", frag_LightAttenuation);

        sf::RenderStates states;
        states.shader = shader;
        states.blendMode = sf::BlendAdd;

        myRenderTexture.draw(spriteWorld, states);

    }

    myRenderTexture.display();
    window.draw(spriteWorld);
    window.display();
}