#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "World.hpp"

class Game : private sf::NonCopyable {
public:
    Game();
    void run();

private:
    void processInput();
    void update(sf::Time elapsedTime);
    void render();

    void updateStatistics(sf::Time elapsedTime);

private:
    static const sf::Time   TimePerFrame;

    sf::RenderWindow 	window;
	World 				world;
	Player 				player;

    sf::Font 			font;
    sf::Text			statisticsText;
    sf::Time 			statisticsUpdateTime;
    std::size_t 		statisticsNumFrames;


};



#endif /* GAME_HPP */
