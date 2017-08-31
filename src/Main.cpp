#include "Application.hpp"

#include <stdexcept>
#include <iostream>

int main() {
	try {
		Application app;
		app.run();
	}
	catch (std::exception& e) {
		std::cout << "\nException: " << e.what() << std::endl;
	}
	return 0;
}
