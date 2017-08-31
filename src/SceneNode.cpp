#include "SceneNode.hpp"
#include "Command.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <algorithm>
#include <cassert>

SceneNode::SceneNode() {
	this->parent = nullptr;
}

void SceneNode::attachChild(Ptr child) {
	child->parent = this;
	this->children.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node) {
	auto found = std::find_if(this->children.begin(), this->children.end(),[&] (Ptr& p) { return p.get() == &node; });
	assert(found != this->children.end());

	Ptr result = std::move(*found);
	result->parent = nullptr;
	this->children.erase(found);
	return result;
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();

	drawCurrent(target, states);
	drawChildren(target, states);

	// drawBoundingRect(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget&, sf::RenderStates) const
{
		// Do nothing by default
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const {
	for (const Ptr& child : this->children) {
		child->draw(target, states);
	}
}

void SceneNode::drawBoundingRect(sf::RenderTarget& target, sf::RenderStates) const
{
	sf::FloatRect rect = getBoundingRect();

	sf::RectangleShape shape;
	shape.setPosition(sf::Vector2f(rect.left, rect.top));
	shape.setSize(sf::Vector2f(rect.width, rect.height));
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::Green);
	shape.setOutlineThickness(1.f);

	target.draw(shape);
}


void SceneNode::update(sf::Time dt) {
	updateCurrent(dt);
	updateChildren(dt);
}

void SceneNode::updateCurrent(sf::Time dt) {

}

void SceneNode::updateChildren(sf::Time dt) {
	for (Ptr& child : this->children) {
		child->update(dt);
	}
}

sf::Vector2f SceneNode::getWorldPosition() const {
	return getWorldTransform() * sf::Vector2f();
}

sf::Transform SceneNode::getWorldTransform() const {
	sf::Transform transform = sf::Transform::Identity;
	for (const SceneNode* node = this; node != nullptr; node = node->parent)
		transform = node->getTransform() * transform;

	return transform;
}

void SceneNode::onCommand(const Command& command, sf::Time dt) {
	if (command.category & getCategory()) command.action(*this, dt);

	for (Ptr& child : this->children) child->onCommand(command, dt);
}

unsigned int SceneNode::getCategory() const {
	return Category::Scene;
}

sf::FloatRect SceneNode::getBoundingRect() const
{
	return sf::FloatRect();
}
