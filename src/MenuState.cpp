#include "MenuState.hpp"
#include "Utility.hpp"
#include "ResourceHolder.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

MenuState::MenuState(StateStack& stack, Context context) : State(stack, context), options(), optionIndex(0) {
	sf::Texture& texture = context.textures->get(Textures::TitleScreen);
	sf::Font& font = context.fonts->get(Fonts::Main);

	this->backgroundSprite.setTexture(texture);

	sf::Text playOption;
	playOption.setFont(font);
	playOption.setString("Play");
	centerOrigin(playOption);
	playOption.setPosition(context.window->getView().getSize() / 2.f);
	this->options.push_back(playOption);

	sf::Text exitOption;
	exitOption.setFont(font);
	exitOption.setString("Exit");
	centerOrigin(exitOption);
	exitOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 30.f));
	this->options.push_back(exitOption);

	updateOptionText();
}

void MenuState::draw() {
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());
	window.draw(this->backgroundSprite);

	for (const sf::Text& text : this->options)
		window.draw(text);
}

bool MenuState::update(sf::Time) {
	return true;
}

bool MenuState::handleEvent(const sf::Event& event) {
	if (event.type != sf::Event::KeyPressed)
		return false;

	if (event.key.code == sf::Keyboard::Return) {
		if (this->optionIndex == Play) {
			requestStackPop();
			requestStackPush(States::Game);
		}
		else if (this->optionIndex == Exit) {
			requestStackClear();
		}
	}
	else if (event.key.code == sf::Keyboard::Up) {
		if (this->optionIndex > 0)
			this->optionIndex--;
		else
			this->optionIndex = this->options.size() - 1;

		updateOptionText();
	}
	else if (event.key.code == sf::Keyboard::Down) {
		if (this->optionIndex < this->options.size() - 1)
			this->optionIndex++;
		else
			this->optionIndex = 0;

		updateOptionText();
	}
	return true;
}

void MenuState::updateOptionText() {
	if (this->options.empty())
		return;

	for (sf::Text& text : this->options)
		text.setColor(sf::Color::White);

	this->options[this->optionIndex].setColor(sf::Color::Red);
}
