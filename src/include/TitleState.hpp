#ifndef TITLESTATE_HPP
#define TITLESTATE_HPP

#include "State.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class TitleState : public State {
public:
	TitleState(StateStack& stack, Context context);

	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);

private:
	sf::Sprite backgroundSprite;
	sf::Text text;

	bool showText;
	sf::Time textEffectTime;
};

#endif /* TITLESTATE_HPP */
