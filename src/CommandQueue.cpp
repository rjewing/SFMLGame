#include "CommandQueue.hpp"
#include "SceneNode.hpp"

void CommandQueue::push(const Command& command) {
	this->queue.push(command);
}

Command CommandQueue::pop() {
	Command command = this->queue.front();
	this->queue.pop();
	return command;
}

bool CommandQueue::isEmpty() const {
	return this->queue.empty();
}
