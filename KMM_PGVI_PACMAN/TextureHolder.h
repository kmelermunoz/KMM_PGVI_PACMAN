#ifndef TEXTURE_HOLDER_H
#define TEXTURE_HOLDER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class TextureHolder
{
public:
    TextureHolder(); // Constructor
    static sf::Texture& GetTexture(std::string const& filename); // Mètode públic per obtenir la textura

private:
    std::map<std::string, sf::Texture> m_Textures; // Mapa per mantenir textures
    static TextureHolder* m_s_Instance; // Instància estàtica de TextureHolder (patró Singleton)
};

#endif // TEXTURE_HOLDER_H
