#include "World.hpp"

#include "SFML/Graphics/RenderWindow.hpp"

World::World(sf::RenderWindow& window) : window(window) {
	this->worldView = window.getDefaultView();

	this->worldBounds = sf::FloatRect(0.f, 0.f, this->worldView.getSize().x, this->worldView.getSize().y);
	this->spawnPosition = sf::Vector2f(this->worldView.getSize().x / 2.f, this->worldView.getSize().y / 2.f);

	loadTextures();
	buildScene();

	this->worldView.setCenter(this->spawnPosition);
}

void World::update(sf::Time dt) {
	while (!this->commandQueue.isEmpty()) this->sceneGraph.onCommand(this->commandQueue.pop(), dt);

	this->sceneGraph.update(dt);
}

void World::draw() {
	this->window.setView(this->worldView);
	this->window.draw(this->sceneGraph);
}

void World::loadTextures() {
	this->textures.load(Textures::Caveman, "media/textures/Caveman.png");
	this->textures.load(Textures::Farmer, "media/textures/Farmer.png");
	this->textures.load(Textures::Background, "media/textures/Desert.png");
}

void World::buildScene() {
	// Initialize layers
	for (size_t i = 0; i < LayerCount; i++) {
		SceneNode::Ptr layer(new SceneNode());
		this->sceneLayers[i] = layer.get();
		this->sceneGraph.attachChild(std::move(layer));
	}

	sf::Texture& texture = this->textures.get(Textures::Background);
	sf::IntRect textureRect(this->worldBounds);
	texture.setRepeated(true);

	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(this->worldBounds.left, this->worldBounds.top);
	this->sceneLayers[Background]->attachChild(std::move(backgroundSprite));

	std::unique_ptr<Worker> caveman(new Worker(Worker::Caveman, this->textures));
	this->worker = caveman.get();
	this->worker->setPosition(this->spawnPosition);
	this->worker->setHomeLocation(this->spawnPosition);
	this->worker->setVelocity(0.f, 0.f);
	this->sceneLayers[Ground]->attachChild(std::move(caveman));

	// std::unique_ptr<Worker> caveman2(new Worker(Worker::Caveman, this->textures));
	// this->worker2 = caveman2.get();
	// this->worker2->setPosition(this->spawnPosition);
	// this->worker2->setVelocity(0.f, 0.f);
	// this->sceneLayers[Ground]->attachChild(std::move(caveman2));

	this->workerlist.push_back(worker);
	// this->workerlist.push_back(worker2);

}

CommandQueue& World::getCommandQueue() {
	return this->commandQueue;
}

void World::selectWorker() {
	for (auto& worker : this->workerlist) {
		worker->deselect();
	}
	for (auto& worker : this->workerlist) {
		if(worker->getBoundingRect().contains(sf::Vector2f(sf::Mouse::getPosition(this->window)))) {
			worker->select();
			return;
		}
	}
}
