#include "TextureHolder.h"
#include <assert.h>

using namespace sf;
using namespace std;

// Inicialització de la instància única de TextureHolder
TextureHolder* TextureHolder::m_s_Instance = nullptr;

TextureHolder::TextureHolder()
{
    // Comprovar que no hi hagi una instància existent
    assert(m_s_Instance == nullptr);
    // Assignar aquesta instància com la instància única
    m_s_Instance = this;
}

sf::Texture& TextureHolder::GetTexture(std::string const& filename)
{
    // Obtenim una referència a m_Textures utilitzant l'instància única
    auto& m = m_s_Instance->m_Textures;
    // 'auto' és equivalent a std::map<string, Texture>

    // Creem un iterador per emmagatzemar un parell clau-valor (kvp)
    // i cerquem el kvp necessari
    // utilitzant el nom de fitxer passat
    auto keyValuePair = m.find(filename);
    // 'auto' és equivalent a std::map<string, Texture>::iterator

    // Hem trobat una coincidència?
    if (keyValuePair != m.end())
    {
        // Sí, hem trobat la textura
        // Retornem la textura, que és la segona part del kvp
        return keyValuePair->second;
    }
    else
    {
        // El nom del fitxer no es va trobar
        // Creem un nou parell clau-valor utilitzant el nom del fitxer
        auto& texture = m[filename];
        // Carreguem la textura des del fitxer de la manera habitual
        texture.loadFromFile(filename);

        // Retornem la textura al codi que l'ha cridat
        return texture;
    }
}
