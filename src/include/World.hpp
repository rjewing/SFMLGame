#ifndef WORLD_HPP
#define WORLD_HPP

#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "SceneNode.hpp"
#include "SpriteNode.hpp"
#include "Worker.hpp"
#include "CommandQueue.hpp"
#include "Command.hpp"
#include "Player.hpp"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <array>
#include <vector>
#include <memory>

// Forward declaration
namespace sf {
	class RenderWindow;
}

class World : private sf::NonCopyable {
public:
	explicit World(sf::RenderWindow& window);
	void update(sf::Time dt);
	void draw();

	CommandQueue& getCommandQueue();
	void selectWorker();

private:
	void loadTextures();
	void buildScene();

private:
	enum Layer {
		Background,
		Ground,
		LayerCount
	};

private:
	sf::RenderWindow& window;
	sf::View worldView;
	TextureHolder textures;

	SceneNode sceneGraph;
	std::array<SceneNode*, LayerCount> sceneLayers;
	CommandQueue commandQueue;

	sf::FloatRect worldBounds;
	sf::Vector2f spawnPosition;
public:
	Worker* worker;
	Worker* worker2;
	std::vector<Worker*> workerlist;

};

#endif /* WORLD_HPP */
