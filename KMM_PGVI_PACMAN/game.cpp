#include "Game.h"
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>

Game::Game()
    : mWindow(sf::VideoMode::getDesktopMode(), "KMM_PGVI_PACMAN", sf::Style::Fullscreen)
{
    // Carregar la imatge de fons
    mBackgroundSprite = sf::Sprite(TextureHolder::GetTexture("E:/AluCiclesGS2/KMM/PGVI/UF1/KMM_PGVI_PACMAN/x64/Debug/fons.jpg"));

    // Configuraci� de les barreres
    mBarrierTop.setSize(sf::Vector2f(100.f, 800.f)); // Dimensions de la barrera superior
    mBarrierTop.setFillColor(sf::Color::Blue); // Color de la barrera superior
    mBarrierTop.setPosition(1000.f, 0.f); // Posici� de la barrera superior

    mBarrierMiddle.setSize(sf::Vector2f(100.f, 800.f)); // Dimensions de la barrera mitjana
    mBarrierMiddle.setFillColor(sf::Color::Red); // Color de la barrera mitjana
    mBarrierMiddle.setPosition(250.f, -50.f); // Posici� de la barrera mitjana

    mBarrierBottom.setSize(sf::Vector2f(100.f, 1050.f)); // Dimensions de la barrera inferior
    mBarrierBottom.setFillColor(sf::Color::Black); // Color de la barrera inferior
    mBarrierBottom.setPosition(1400.f, mWindow.getSize().y - 750.f); // Posici� de la barrera inferior

    mBarrierBottom2.setSize(sf::Vector2f(100.f, 1050.f)); // Dimensions de la segona barrera inferior
    mBarrierBottom2.setFillColor(sf::Color::Magenta); // Color de la segona barrera inferior
    mBarrierBottom2.setPosition(600.f, mWindow.getSize().y - 750.f); // Posici� de la segona barrera inferior

    mBarrierBottom3.setSize(sf::Vector2f(100.f, 800.f)); // Dimensions de la nova barrera superior
    mBarrierBottom3.setFillColor(sf::Color::Cyan); // Color de la nova barrera superior
    mBarrierBottom3.setPosition(1900.f, 0.f); // Posici� de la nova barrera superior

    // Configuraci� de l'objectiu del joc
    mGoal.setSize(sf::Vector2f(100.f, mWindow.getSize().y)); // Dimensions de l'objectiu
    mGoal.setFillColor(sf::Color::Green); // Color de l'objectiu
    mGoal.setPosition(mWindow.getSize().x - 150.f, 0.f); // Posici� de l'objectiu

    // C�rrega de la font per al text
    if (!mFont.loadFromFile("font.ttf")) {
        std::cout << "Error al carregar la font" << std::endl; // Missatge d'error si no es pot carregar la font
    }

    // Obtenir la mida de la finestra
    sf::Vector2u windowSize = mWindow.getSize(); // Utilitzar mWindow en lloc de window

    // Configuraci� del text final del joc "Has guanyat!"
    mEndText.setFont(mFont); // Assignar la font al text
    mEndText.setString("Has guanyat!"); // Establir el contingut del text
    mEndText.setCharacterSize(200); // Mida del text
    mEndText.setFillColor(sf::Color::Green); // Color del text

    // Centrar el text "Has guanyat!"
    sf::FloatRect textBounds = mEndText.getLocalBounds(); // Obtenir les dimensions del text
    mEndText.setOrigin(textBounds.width / 2, textBounds.height / 2); // Ajustar l'origen al centre del text
    mEndText.setPosition(windowSize.x / 2, windowSize.y / 2); // Posici� del text al centre de la finestra

    // Configuraci� del text de p�rdua "Has Perdut!"
    mLostText.setFont(mFont); // Assignar la font al text de p�rdua
    mLostText.setString("Has Perdut!"); // Establir el contingut del text de p�rdua
    mLostText.setCharacterSize(200); // Mida del text de p�rdua
    mLostText.setFillColor(sf::Color::Red); // Color del text de p�rdua

    // Centrar el text "Has Perdut!"
    textBounds = mLostText.getLocalBounds(); // Obtenir les dimensions del text de p�rdua
    mLostText.setOrigin(textBounds.width / 2, textBounds.height / 2); // Ajustar l'origen al centre del text de p�rdua
    mLostText.setPosition(windowSize.x / 2, windowSize.y / 2); // Posici� del text de p�rdua al centre de la finestra

    // Posici� inicial del jugador
    sf::Vector2f playerStartPosition(100.f, 500.f); // Posici� inicial del jugador
    mPlayer.setPosition(playerStartPosition); // Assignar la posici� al jugador

    // Crear enemics a la mateixa posici� X que el jugador, en fila vertical
    float distanceBetweenEnemies = 100.f; // Dist�ncia entre els enemics
    float enemyStartOffset = -400.f; // Offset inicial ajustat perqu� estiguin m�s amunt

    // Posicionem els enemics en fila vertical, per davant del jugador
    mEnemies.emplace_back(playerStartPosition + sf::Vector2f(0.f, enemyStartOffset), 100.f); // Enemic 1
    mEnemies.emplace_back(playerStartPosition + sf::Vector2f(0.f, enemyStartOffset + distanceBetweenEnemies), 150.f); // Enemic 2
    mEnemies.emplace_back(playerStartPosition + sf::Vector2f(0.f, enemyStartOffset + 2 * distanceBetweenEnemies), 200.f); // Enemic 3
}

void Game::run()
{
    sf::Clock clock; // Temporitzador per controlar el temps
    sf::Time timeSinceLastUpdate = sf::Time::Zero; // Temps transcorregut

    while (mWindow.isOpen()) // Mentre la finestra estigui oberta
    {
        sf::Time deltaTime = clock.restart(); // Reiniciar el temporitzador
        timeSinceLastUpdate += deltaTime; // Afegir el temps transcorregut

        // Actualitzar el joc en funci� del temps transcorregut
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame; // Reduir el temps acumulat
            processEvents(); // Processar esdeveniments (tecles, tancament de finestra, etc.)
            update(TimePerFrame); // Actualitzar l'estat del joc
        }

        render(); // Renderitzar la finestra
    }
}

void Game::processEvents()
{
    sf::Event event; // Crear un esdeveniment per a la detecci�
    while (mWindow.pollEvent(event)) // Processar esdeveniments
    {
        switch (event.type)
        {
        case sf::Event::KeyPressed: // Si es prem una tecla
            mPlayer.handleInput(event.key.code, true); // Manejar la tecla premuda
            if (event.key.code == sf::Keyboard::Escape) // Si es prem Escape
            {
                mWindow.close(); // Tancar la finestra
            }
            break;
        case sf::Event::KeyReleased: // Si es deixa de premre una tecla
            mPlayer.handleInput(event.key.code, false); // Manejar la tecla alliberada
            break;
        case sf::Event::Closed: // Si es tanca la finestra
            mWindow.close(); // Tancar la finestra
            break;
        }
    }
}

void Game::update(sf::Time deltaTime)
{
    if (mGameWon || mGameLost) // Si el joc ha acabat
    {
        mEndTextTimer += deltaTime; // Temporitzador per mostrar el text final
        if (mEndTextTimer >= sf::seconds(3)) // Tancar la finestra despr�s de 3 segons
        {
            mWindow.close(); // Tancar la finestra
        }
        return; // Sortir de l'actualitzaci�
    }

    sf::Vector2f previousPosition = mPlayer.getBounds().getPosition(); // Guardar la posici� anterior del jugador
    mPlayer.update(deltaTime); // Actualitzar la posici� del jugador

    // Comprovar si el jugador col�lideix amb barreres
    if (mPlayer.getBounds().intersects(mBarrierTop.getGlobalBounds()) ||
        mPlayer.getBounds().intersects(mBarrierMiddle.getGlobalBounds()) ||
        mPlayer.getBounds().intersects(mBarrierBottom.getGlobalBounds()) ||
        mPlayer.getBounds().intersects(mBarrierBottom2.getGlobalBounds()) ||
        mPlayer.getBounds().intersects(mBarrierBottom3.getGlobalBounds()))
    {
        mPlayer.setPosition(previousPosition); // Retornar a la posici� anterior si hi ha col�lisi�
    }

    checkCollisions(); // Comprovar col�lisions amb els enemics

    // Actualitzar la posici� dels enemics per perseguir al jugador
    for (auto& enemy : mEnemies)
    {
        enemy.update(deltaTime, mPlayer.getBounds().getPosition()); // Actualitzar cada enemic
    }

    checkWinCondition(); // Comprovar si el jugador ha guanyat
}

void Game::checkCollisions()
{
    for (const auto& enemy : mEnemies) // Iterar sobre els enemics
    {
        if (mPlayer.getBounds().intersects(enemy.getBounds())) // Si el jugador col�lideix amb un enemic
        {
            mGameLost = true; // Marcar que el jugador ha perdut
            mShowEndText = true; // Mostrar el text de p�rdua
            mEndTextTimer = sf::Time::Zero; // Reiniciar el temporitzador
            std::cout << "Has Perdut!" << std::endl; // Missatge de p�rdua
            break; // Sortir del bucle
        }
    }
}

void Game::checkWinCondition()
{
    if (mPlayer.getBounds().intersects(mGoal.getGlobalBounds())) // Si el jugador arriba a l'objectiu
    {
        mGameWon = true; // Marcar que el jugador ha guanyat
        mShowEndText = true; // Mostrar el text de vict�ria
        mEndTextTimer = sf::Time::Zero; // Reiniciar el temporitzador
        std::cout << "Fi partida!" << std::endl; // Missatge de vict�ria
    }
}

void Game::render()
{
    mWindow.clear(); // Netejar la finestra

    // Dibuixar els elements del joc
    mWindow.draw(mBackgroundSprite);
    mWindow.draw(mBarrierTop); // Dibuixar la barrera superior
    mWindow.draw(mBarrierMiddle); // Dibuixar la barrera mitjana
    mWindow.draw(mBarrierBottom); // Dibuixar la barrera inferior
    mWindow.draw(mBarrierBottom2); // Dibuixar la segona barrera inferior
    mWindow.draw(mBarrierBottom3); // Dibuixar la nova barrera superior
    mWindow.draw(mGoal); // Dibuixar l'objectius

    // Renderitzar els enemics
    for (const auto& enemy : mEnemies)
    {
        enemy.render(mWindow); // Dibuixar cada enemic
    }

    mPlayer.render(mWindow); // Renderitzar el jugador

    // Mostrar el text final o de p�rdua si cal
    if (mGameWon)
    {
        mWindow.draw(mEndText); // Dibuixar el text de vict�ria
    }

    if (mGameLost)
    {
        mWindow.draw(mLostText); // Dibuixar el text de p�rdua
    }

    mWindow.display(); // Actualitzar la finestra
}
