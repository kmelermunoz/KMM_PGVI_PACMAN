#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "TextureHolder.h"
#include "Enemy.h"
#include <vector>

class Game
{
public:
    Game();        // Constructor de la classe Game
    void run();    // Bucle principal del joc

private:
    void processEvents();    // Processar els esdeveniments del joc
    void update(sf::Time deltaTime);  // Actualitzar la lògica del joc
    void render();           // Renderitzar la escena
    void checkWinCondition(); // Comprovar si el jugador ha arribat a la meta
    void checkCollisions();  // Comprovar les col·lisions amb enemics i barreres

private:
    sf::RenderWindow mWindow;           // Finestra principal del joc
    TextureHolder holder;                // Gestor de textures

    // Objectes del joc
    Player mPlayer;                     // Jugador encapsulat en la classe
    std::vector<Enemy> mEnemies;        // Vector d'enemics

    // Textures i sprites
    sf::Texture mBackgroundTexture;     // Textura de fons
    sf::Sprite mBackgroundSprite;       // Sprite de fons

    // Barreres
    sf::RectangleShape mBarrierTop;     // Barrera superior
    sf::RectangleShape mBarrierMiddle;  // Barrera del mig
    sf::RectangleShape mBarrierBottom;  // Barrera inferior dreta
    sf::RectangleShape mBarrierBottom2; // Barrera inferior esquerra
    sf::RectangleShape mBarrierBottom3; // Barrera superior nova
    sf::RectangleShape mExtraSquare;    // Quadrado addicional a la dreta

    // Meta
    sf::RectangleShape mGoal;           // Meta del joc

    // Text de fi de partida
    sf::Font mFont;                    // Font per al text
    sf::Text mEndText;                 // Text de fi de partida
    sf::Text mLostText;                // Text de derrota
    bool mShowEndText = false;         // Estat per mostrar el text de fi de partida
    bool mGameLost = false;             // Estat del joc perdut
    sf::Time mEndTextTimer;             // Temporitzador per al text de fi de partida

    const sf::Time TimePerFrame = sf::seconds(1.f / 60.f); // Temps per fotograma per a 60 FPS
    bool mGameWon = false;              // Estat del joc guanyat
};

#endif
