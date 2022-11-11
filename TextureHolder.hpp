#pragma once
#ifndef TEXTURE_HOLDER_H
#define TEXTURE_HOLDER_H
#include <SFML/Graphics.hpp>
#include <map>
 /*TextureHolder singleton as a neat way to hold just three textures that
can be used for dozens or even thousands of zombies*/
using namespace sf;
using namespace std;

class TextureHolder
{
private:
    // A map container from the STL,
    // that holds related pairs of String and Texture
    map<string, Texture> m_Textures;
    // A pointer of the same type as the class itself
    // the one and only instance
    static TextureHolder* m_s_Instance;
public:
    TextureHolder();
    static Texture& GetTexture(string const& filename);
};
#endif  //TEXTURE_HOLDER_H