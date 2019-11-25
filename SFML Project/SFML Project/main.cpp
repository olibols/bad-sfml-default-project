#include <SFML/Graphics.hpp>
#include <array>


void drawSFML(sf::RenderWindow& window, sf::Drawable& drawable) {
	window.draw(drawable);
}

struct GridTile {

	GridTile() {
		shape.setFillColor(sf::Color(255, 0, 0));
		shape.setPosition(sf::Vector2f(1.0, 1.0));
	};

	sf::RectangleShape shape = sf::RectangleShape(sf::Vector2f(10.f, 10.f));
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");

	std::array<std::array<GridTile, 50>, 50>tiles;

	for (int x = 0; x < 50; x++) {
		for (int y = 0; y < 50; y++) {
			GridTile tile;
			tile.shape.setPosition(sf::Vector2f(x * 15, y * 15));

			tiles[x][y] = tile;
		}
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color(30, 30, 30));

		for (auto& arr : tiles) {
			for (auto& tile : arr) {
				drawSFML(window, tile.shape);
			}
		}

		window.display();
	}

	return 0;
}