#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!"); // Makes window with dimensions 200, 200, and name "SFML works"
	sf::CircleShape shape(100.f); // The circle that fills the whole screen lol
	shape.setFillColor(sf::Color::Green); // Make it green

	while (window.isOpen()) // The main loop that is run each frame
	{
		sf::Event event;
		while (window.pollEvent(event)) // Polls the window events so things like closing the window and resizing
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(); // Clears the current frame
		window.draw(shape); // Draws the shape to the buffer
		window.display(); // Displays the buffer
	}

	return 0; //  E N D
}