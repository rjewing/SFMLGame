/* Includes - STL */
#include <string>

/* Includes - SFML */
#include <SFML/System/Vector2.hpp>

/* Defines */
#define PI 3.14159265358979323846F

/*
 * The dot product of this and another vector
 * @VECTOR2		Vector for comparing against
 * ->float		The dot product
 */
float dot(const sf::Vector2f, const sf::Vector2f);

/*
 * The normalization of this vector
 * ->VECTOR2	A new vector that equals this vector normalized
 */
sf::Vector2f norm(sf::Vector2f);

/*
 * The angle of this vector
 * ->float		This vector's angle in radians
 */
float ang(sf::Vector2f);

/*
 * The magnitude of this vector
 * ->float		This vector's magnitude
 */
float mag(sf::Vector2f);

/*
 * Reassigns this vector's values to the specified values
 * @float		The new x value
 * @float		The new y value
 */
void reassign(sf::Vector2f&, float, float);

/*
 * Reassigns this vector's values to the vector
 * @VECTOR2		The new vector
 */
void reassign(sf::Vector2f&, sf::Vector2f);


/*
 * A string representation of this vector
 * ->std::string	This vector to a string
 */
const std::string to_str(sf::Vector2f);
