#include "State.hpp"
#include "StateStack.hpp"

State::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Player& player) : window(&window), textures(&textures), fonts(&fonts), player(&player) {}

State::State(StateStack& stack, Context context) : stack(&stack), context(context) {}

State::~State() {}

void State::requestStackPush(States::ID stateID) {
	this->stack->pushState(stateID);
}

void State::requestStackPop() {
	this->stack->popState();
}

void State::requestStackClear() {
	this->stack->clearStates();
}

State::Context State::getContext() const {
	return this->context;
}
