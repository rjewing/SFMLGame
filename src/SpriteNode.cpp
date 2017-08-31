#include "SpriteNode.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

SpriteNode::SpriteNode(const sf::Texture& texture) {
	this->sprite.setTexture(texture);
}

SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect) {
	this->sprite.setTexture(texture);
	this->sprite.setTextureRect(textureRect);
}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(this->sprite, states);
}
