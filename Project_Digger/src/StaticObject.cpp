#include "StaticObject.h"

StaticObject::StaticObject(const sf::Texture& texture, sf::Vector2f location, char name, const sf::Vector2i sizeOfTexture) :Object(texture, location, sizeOfTexture) ,m_name(name) {}

StaticObject::~StaticObject()
{
}
