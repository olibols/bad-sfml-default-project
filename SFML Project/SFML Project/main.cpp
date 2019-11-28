#include <SFML/Graphics.hpp>
#include <array>


void drawSFML(sf::RenderWindow& window, sf::Drawable& drawable) {
	window.draw(drawable);
}

enum TileType {
	Filled,
	Empty,
	Visited
};

struct GridTile {

	GridTile() {
		shape.setFillColor(sf::Color(255, 0, 0));
		shape.setPosition(sf::Vector2f(1.0, 1.0));
	};

	TileType type = Empty;

	sf::RectangleShape shape = sf::RectangleShape(sf::Vector2f(10.f, 10.f));
};

GridTile getTile(std::array<std::array<GridTile, 50>, 50>& tiles, int x, int z) {
	return tiles[x][z];
}

bool traverse(std::array<std::array<GridTile, 50>, 50>& tiles, int x, int z) {
	if (!(x > 0 && x < 50 && z > 0 && z < 50)) return false;
	if (tiles[x][z].type == TileType::Filled) return false;

	if (x == 25 && z == 25) return true;
	else tiles[x][z].type = TileType::Visited;

	if (traverse(tiles, x - 1, z)) {
		tiles[x - 1][z].type = TileType::Visited;
		return true;
	}
	if (traverse(tiles, x + 1, z)) {
		tiles[x + 1][z].type = TileType::Visited;
		return true;
	}
	if (traverse(tiles, x, z + 1)) {
		tiles[x][z + 1].type = TileType::Visited;
		return true;
	}
	if (traverse(tiles, x, z - 1)) {
		tiles[x][z - 1].type = TileType::Visited;
		return true;
	}

	return false;
}

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

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sf::Vector2i pos = sf::Mouse::getPosition(window);
			pos /= 15;
			try {
				tiles.at(pos.x).at(pos.y).shape.setFillColor(sf::Color(0, 0, 0));
			}
			catch (std::exception e) {}
		}

		window.clear(sf::Color(30, 30, 30));

		for (auto& arr : tiles) {
			for (auto& tile : arr) {
				if (tile.type == TileType::Visited) tile.shape.setFillColor(sf::Color(0, 255, 0));
				drawSFML(window, tile.shape);
			}
		}

		window.display();
	}

	return 0;
}