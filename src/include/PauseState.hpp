#ifndef PAUSESTATE_HPP
#define PAUSESTATE_HPP

#include "State.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class PauseState : public State {
public:
    PauseState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

private:
    sf::Sprite backgroundSprite;
    sf::Text pausedText;
    sf::Text instructionText;
};

#endif /* PAUSESTATE_HPP */
