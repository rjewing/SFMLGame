#include "StateStack.hpp"

#include <cassert>
#include <iostream>

StateStack::StateStack(State::Context context) :
stack(),
pendingList(),
context(context),
factories()
{
}

void StateStack::update(sf::Time dt) {
	for (auto itr = this->stack.rbegin(); itr != this->stack.rend(); ++itr) {
		if (!(*itr)->update(dt))
			break;
	}
	applyPendingChanges();
}

void StateStack::draw() {
	for (State::Ptr& state : this->stack) {
		state->draw();
	}
}

void StateStack::handleEvent(const sf::Event& event) {
	for (auto itr = this->stack.rbegin(); itr != this->stack.rend(); ++itr) {
		if (!(*itr)->handleEvent(event))
			break;
	}
	applyPendingChanges();
}

void StateStack::pushState(States::ID stateID) {
	this->pendingList.push_back(PendingChange(Push, stateID));
}

void StateStack::popState() {
	this->pendingList.push_back(PendingChange(Pop));
}

void StateStack::clearStates() {
	this->pendingList.push_back(PendingChange(Clear));
}

bool StateStack::isEmpty() const {
	return this->stack.empty();
}

State::Ptr StateStack::createState(States::ID stateID) {
	auto found = this->factories.find(stateID);
	assert(found != this->factories.end());
	return found->second();
}

void StateStack::applyPendingChanges() {
	for (PendingChange change : this->pendingList) {
		switch (change.action) {
			case Push:
				this->stack.push_back(createState(change.stateID));
				break;
			case Pop:
				this->stack.pop_back();
				break;
			case Clear:
				this->stack.clear();
				break;
		}
	}
	this->pendingList.clear();
}

StateStack::PendingChange::PendingChange(Action action, States::ID stateID) :
action(action),
stateID(stateID)
{
}
