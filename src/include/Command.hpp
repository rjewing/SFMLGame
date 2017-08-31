#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <SFML/System/Time.hpp>

#include <functional>
#include <cassert>

#include "Category.hpp"

class SceneNode;

struct Command {
	Command();
	std::function<void(SceneNode&, sf::Time)> action;
	unsigned int category;
};

template <typename GameObject, typename Function> std::function<void(SceneNode& node, sf::Time dt)> derivedAction(Function fn) {
	return [=] (SceneNode& node, sf::Time dt) {
		assert(dynamic_cast<GameObject*>(&node) != nullptr);

		fn(static_cast<GameObject&>(node), dt);
	};
}

#endif /* COMMAND_HPP */
