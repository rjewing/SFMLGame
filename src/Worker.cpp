#include "Worker.hpp"
#include "ResourceHolder.hpp"
#include "Vecmath.hpp"


#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>

Textures::ID toTextureID(Worker::Type type) {
	switch (type) {
		case Worker::Caveman:
			return Textures::Caveman;
			break;
		case Worker::Farmer:
			return Textures::Farmer;
			break;
	}
	return Textures::Caveman;
}

void Worker::updateCurrent(sf::Time dt) {
	if (this->working) {
		if (mag(this->getWorldPosition() -  this->workLocation) < 1)
			this->setTargetLocation(this->homeLocation);
		else if (mag(this->getWorldPosition() -  this->homeLocation) < 1)
			this->setTargetLocation(this->workLocation);
	}
	move(this->getVelocity() * dt.asSeconds());
}

unsigned int Worker::getCategory() const
{
	switch (this->type)
	{
		case Caveman:
			return Category::Player;

		case SelectedWorker:
			return Category::SelectedWorker;

		default:
			return Category::Worker;
	}
}

unsigned int Worker::getDefaultCategory() const
{
	return this->defaultType;
}

void Worker::select()
{
	this->type = Type::SelectedWorker;
}


void Worker::deselect()
{
	this->type = this->defaultType;
}

Worker::Worker(Type type, const TextureHolder& textures) {
	this->type = type;
	this->defaultType = type;
	this->sprite.setTexture(textures.get(toTextureID(type)));

	sf::FloatRect bounds = this->sprite.getGlobalBounds();
	this->sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	this->working = false;
}

void Worker::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(this->sprite, states);

	sf::RectangleShape shape;
	shape.setPosition(sf::Vector2f(this->targetLocation.x, this->targetLocation.y));
	shape.setSize(sf::Vector2f(5, 5));
	shape.setOutlineColor(sf::Color::Red);
	shape.setOutlineThickness(1.f);

	target.draw(this->sprite, states);
}

void Worker::setWorkLocation(sf::Vector2f pos) {
	this->working = true;
	this->workLocation = pos;
	this->setTargetLocation(this->workLocation);
}

void Worker::setWorkLocation(float x, float y) {
	this->setWorkLocation(sf::Vector2f(x, y));
}

void Worker::setHomeLocation(sf::Vector2f pos) {
	this->homeLocation = pos;
	this->setTargetLocation(this->homeLocation);
}

void Worker::setTargetLocation(sf::Vector2f pos) {
	this->targetLocation = pos;
	this->setVelocity(norm(this->targetLocation - this->getWorldPosition()).x * 50, norm(this->targetLocation - this->getWorldPosition()).y * 50);
}

sf::FloatRect Worker::getBoundingRect() const
{
    return getWorldTransform().transformRect(sprite.getGlobalBounds());
}
