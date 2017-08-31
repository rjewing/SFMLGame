#ifndef WORKER_HPP
#define WORKER_HPP

#include <SFML/Graphics/Sprite.hpp>

#include "Entity.hpp"
#include "ResourceIdentifiers.hpp"

class Worker : public Entity {
public:
	enum Type {
		Caveman,
		Farmer,
		SelectedWorker,
	};

public:
	Worker(Type type, const TextureHolder& texture);

	virtual unsigned int getCategory() const;
	virtual unsigned int getDefaultCategory() const;

	virtual void select();
	virtual void deselect();

	void setWorkLocation(sf::Vector2f pos);
	void setWorkLocation(float x, float y);

	void setHomeLocation(sf::Vector2f pos);

	void setTargetLocation(sf::Vector2f pos);

	virtual sf::FloatRect getBoundingRect() const;

private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void updateCurrent(sf::Time dt);


private:
	Type type;
	Type defaultType;
	sf::Sprite sprite;
	sf::Vector2f targetLocation;
	sf::Vector2f homeLocation;
	sf::Vector2f workLocation;

	bool working;
};

#endif /* WORKER_HPP */
