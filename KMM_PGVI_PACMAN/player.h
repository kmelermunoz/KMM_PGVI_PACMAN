#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player
{
public:
    Player();    // Constructor
    void handleInput(sf::Keyboard::Key key, bool isPressed); // Processa l'entrada del jugador
    void update(sf::Time deltaTime);  // Actualitza la posició del jugador
    void render(sf::RenderWindow& window);  // Renderitza el jugador a la finestra

    sf::FloatRect getBounds() const;  // Retorna els límits del jugador
    void setPosition(const sf::Vector2f& position); // Estableix la posició del jugador

private:
    sf::RectangleShape mPlayerShape;  // Forma que representa al jugador
    sf::Texture mPlayerTexture;       // Textura del jugador

    // Senyals de moviment
    bool mIsMovingUp;                 // Moviment amunt
    bool mIsMovingDown;               // Moviment avall
    bool mIsMovingLeft;               // Moviment a l'esquerra
    bool mIsMovingRight;              // Moviment a la dreta

    const float PlayerSpeed = 400.f;  // Velocitat del jugador
};

#endif
