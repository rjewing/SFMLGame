#include "PauseState.hpp"
#include "ResourceHolder.hpp"
#include "Utility.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

PauseState::PauseState(StateStack& stack, Context context) :
State(stack, context),
backgroundSprite(),
pausedText(),
instructionText() {
    sf::Font& font = context.fonts->get(Fonts::Main);
    sf::Vector2f viewSize = context.window->getView().getSize();

    this->pausedText.setFont(font);
    this->pausedText.setString("Game Paused");
    this->pausedText.setCharacterSize(70);
    centerOrigin(this->pausedText);
    this->pausedText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);

    this->instructionText.setFont(font);
    this->instructionText.setString("(Press Backspace to return to the main menu)");
    centerOrigin(this->instructionText);
    this->instructionText.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);
}

void PauseState::draw() {
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundShape.setSize(window.getView().getSize());

    window.draw(backgroundShape);
    window.draw(this->pausedText);
    window.draw(this->instructionText);
}

bool PauseState::update(sf::Time dt) {
    return false;
}

bool PauseState::handleEvent(const sf::Event& event) {
    if (event.type != sf::Event::KeyPressed)
        return false;
    if (event.key.code == sf::Keyboard::Escape){
        requestStackPop();
    }
    if (event.key.code == sf::Keyboard::BackSpace) {
        requestStackClear();
        requestStackPush(States::Menu);
    }

    return false;
}
