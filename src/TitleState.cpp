#include "TitleState.hpp"
#include "Utility.hpp"
#include "ResourceHolder.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <iostream>

TitleState::TitleState(StateStack& stack, Context context) :
State(stack, context),
text(),
showText(true),
textEffectTime(sf::Time::Zero) {
	this->backgroundSprite.setTexture(context.textures->get(Textures::TitleScreen));

	this->text.setFont(context.fonts->get(Fonts::Main));
	this->text.setString("Press any key to start");

	centerOrigin(this->text);

	this->text.setPosition(context.window->getView().getSize() / 2.f);
}

void TitleState::draw() {
	sf::RenderWindow& window = *getContext().window;
	window.draw(this->backgroundSprite);

	if (this->showText)
		window.draw(this->text);
}

bool TitleState::update(sf::Time dt) {
	this->textEffectTime += dt;

	if (this->textEffectTime >= sf::seconds(0.5f)) {
		this->showText = !this->showText;
		this->textEffectTime = sf::Time::Zero;
	}

	return true;
}

bool TitleState::handleEvent(const sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) {
		requestStackPop();
		requestStackPush(States::Menu);
	}
	return true;
}
