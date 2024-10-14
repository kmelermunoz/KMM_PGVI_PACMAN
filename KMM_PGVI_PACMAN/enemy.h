#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

class Enemy
{
public:
    // Constructor de la classe Enemy
    Enemy(sf::Vector2f startPosition, float speed);

    // Actualitzar l'enemic, rebent el temps transcorregut i la posici� del jugador
    void update(sf::Time deltaTime, sf::Vector2f playerPosition);

    // Renderitzar l'enemic a la finestra
    void render(sf::RenderWindow& window) const;

    // Retornar el rectangle que envolta l'enemic per a la detecci� de col�lisions
    sf::FloatRect getBounds() const;

private:
    sf::CircleShape mEnemyShape; // Forma circular de l'enemic
    sf::Vector2f mPosition;      // Posici� de l'enemic
    float mSpeed;                // Velocitat de l'enemic

    // Moure l'enemic cap a la posici� del jugador
    void moveTowardsPlayer(sf::Vector2f playerPosition, sf::Time deltaTime);
};

#endif
