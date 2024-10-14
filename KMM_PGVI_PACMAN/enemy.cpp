#include "Enemy.h"
#include <cmath>

Enemy::Enemy(sf::Vector2f startPosition, float speed)
    : mPosition(startPosition), mSpeed(speed)
{
    // Configurar la forma de l'enemic
    mEnemyShape.setRadius(50.f); // Radi de la forma de l'enemic
    mEnemyShape.setFillColor(sf::Color::Yellow); // Color de l'enemic
    mEnemyShape.setPosition(startPosition); // Posició inicial de l'enemic
}

void Enemy::update(sf::Time deltaTime, sf::Vector2f playerPosition)
{
    // Actualitzar la posició de l'enemic per moure's cap al jugador
    moveTowardsPlayer(playerPosition, deltaTime);
}

void Enemy::moveTowardsPlayer(sf::Vector2f playerPosition, sf::Time deltaTime)
{
    // Calcular la direcció cap al jugador
    sf::Vector2f direction = playerPosition - mPosition;

    // Normalitzar el vector de direcció
    float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (magnitude != 0)
    {
        direction /= magnitude; // Normalització del vector de direcció
    }

    // Moure l'enemic cap al jugador
    mPosition += direction * mSpeed * deltaTime.asSeconds(); // Actualitzar la posició de l'enemic
    mEnemyShape.setPosition(mPosition); // Actualitzar la posició de la forma de l'enemic
}

void Enemy::render(sf::RenderWindow& window) const
{
    // Renderitzar l'enemic a la finestra
    window.draw(mEnemyShape);
}

sf::FloatRect Enemy::getBounds() const
{
    // Retornar el rectangle que envolta l'enemic per a la detecció de col·lisions
    return mEnemyShape.getGlobalBounds();
}
