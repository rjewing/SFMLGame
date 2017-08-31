#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include "State.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class MenuState : public State {
public:
	MenuState(StateStack& stack, Context context);

	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);

	void updateOptionText();

private:
	enum OptionNames {
		Play,
		Exit,
	};

private:
	sf::Sprite backgroundSprite;

	std::vector<sf::Text> options;
	std::size_t optionIndex;
};

#endif /* MENUSTATE_HPP */
