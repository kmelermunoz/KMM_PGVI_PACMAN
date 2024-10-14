#include "Player.h"

Player::Player()
    : mPlayerShape(sf::Vector2f(150.f, 150.f))  // Inicialitza el jugador com un quadrat de 200x200
    , mIsMovingUp(false)
    , mIsMovingDown(false)
    , mIsMovingLeft(false)
    , mIsMovingRight(false)
{
    // Carregar la textura del personatge
    if (!mPlayerTexture.loadFromFile("E:/AluCiclesGS2/KMM/PGVI/UF1/KMM_PGVI_PACMAN/x64/Debug/Personatge.png"))
    {
        // Manejar l'error
    }
    mPlayerShape.setTexture(&mPlayerTexture);  // Estableix la textura al jugador
    mPlayerShape.setPosition(100.f, 100.f);    // Posició inicial del jugador
}

void Player::handleInput(sf::Keyboard::Key key, bool isPressed)
{
    if (key == sf::Keyboard::W)
        mIsMovingUp = isPressed;               // Moviment amunt
    else if (key == sf::Keyboard::S)
        mIsMovingDown = isPressed;             // Moviment avall
    else if (key == sf::Keyboard::A)
        mIsMovingLeft = isPressed;             // Moviment a l'esquerra
    else if (key == sf::Keyboard::D)
        mIsMovingRight = isPressed;            // Moviment a la dreta
}

sf::FloatRect Player::getBounds() const
{
    return mPlayerShape.getGlobalBounds();  // Retorna els límits del jugador
}

void Player::update(sf::Time deltaTime)
{
    sf::Vector2f movement(0.f, 0.f);

    if (mIsMovingUp)
        movement.y -= PlayerSpeed;             // Actualitza el moviment amunt
    if (mIsMovingDown)
        movement.y += PlayerSpeed;             // Actualitza el moviment avall
    if (mIsMovingLeft)
        movement.x -= PlayerSpeed;             // Actualitza el moviment a l'esquerra
    if (mIsMovingRight)
        movement.x += PlayerSpeed;             // Actualitza el moviment a la dreta

    // Mou el jugador
    mPlayerShape.move(movement * deltaTime.asSeconds());
}

void Player::render(sf::RenderWindow& window)
{
    window.draw(mPlayerShape);  // Dibuixa el jugador a la finestra
}

void Player::setPosition(const sf::Vector2f& position)
{
    mPlayerShape.setPosition(position);  // Estableix la nova posició del jugador
}
