#include "Entity.hpp"

void Entity::setVelocity(sf::Vector2f velocity) {
	this->velocity = velocity;
}

void Entity::setVelocity(float vx, float vy) {
	this->velocity.x = vx;
	this->velocity.y = vy;
}

sf::Vector2f Entity::getVelocity() const {
	return this->velocity;
}

void Entity::updateCurrent(sf::Time dt) {
	move(this->velocity * dt.asSeconds());
}
