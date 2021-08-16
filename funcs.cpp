#include "header.h"

int draw_borders(sf::RenderWindow& win) {
	sf::Vertex line[2];
	
	for (int i = 1; i < width; i++) {
		line[0] = sf::Vertex(sf::Vector2f((float) size * i, 0.f));
		line[1] = sf::Vertex(sf::Vector2f((float) size * i, (float) (height * size)));
		win.draw(line, 2, sf::Lines);
	}

	for (int i = 1; i < height; i++) {
		line[0] = sf::Vertex(sf::Vector2f(0.f, (float) size * i));
		line[1] = sf::Vertex(sf::Vector2f((float) (width * size), (float) size * i));
		win.draw(line, 2, sf::Lines);
	}
	
	return 0;
}

int dealloc(bool** grid, char** grid_nbors, char** grid_nbors_buffer) {
	for (int i = 0; i < width; i++) {
		delete[] grid[i];
		delete[] grid_nbors[i];
		delete[] grid_nbors_buffer[i];
	}
	delete[] grid;
	delete[] grid_nbors;
	delete[] grid_nbors_buffer;
	
	return 0;
}

int neighbor_subtract(char** grid_nbors, int i, int j) {
	if (i - 1 >= 0) {
		grid_nbors[i - 1][j]--;
		if (j - 1 >= 0) {
			grid_nbors[i - 1][j - 1]--;
		}
		if (j + 1 < height) {
			grid_nbors[i - 1][j + 1]--;
		}
	}
	if (j - 1 >= 0) {
		grid_nbors[i][j - 1]--;
		if (i + 1 < width) {
			grid_nbors[i + 1][j - 1]--;
		}
	}
	if (i + 1 < width) {
		grid_nbors[i + 1][j]--;
		if (j + 1 < height) {
			grid_nbors[i + 1][j + 1]--;
		}
	}
	if (j + 1 < height) {
		grid_nbors[i][j + 1]--;
	}

	return 0;
}

int neighbor_add(char** grid_nbors, int i, int j) {
	if (i - 1 >= 0) {
		grid_nbors[i - 1][j]++;
		if (j - 1 >= 0) {
			grid_nbors[i - 1][j - 1]++;
		}
		if (j + 1 < height) {
			grid_nbors[i - 1][j + 1]++;
		}
	}
	if (j - 1 >= 0) {
		grid_nbors[i][j - 1]++;
		if (i + 1 < width) {
			grid_nbors[i + 1][j - 1]++;
		}
	}
	if (i + 1 < width) {
		grid_nbors[i + 1][j]++;
		if (j + 1 < height) {
			grid_nbors[i + 1][j + 1]++;
		}
	}
	if (j + 1 < height) {
		grid_nbors[i][j + 1]++;
	}

	return 0;
}

int display(sf::VertexArray shape, bool** grid, sf::RenderWindow& win) {
	sf::Color col;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (grid[i][j]) {
				col = sf::Color::White;
			} else {
				col = sf::Color::Black;
			}
			
			shape[0].position = sf::Vector2f((float) size * i, (float) size * j);
			shape[1].position = sf::Vector2f((float) size * i, (float) size * j + (float) size);
			shape[2].position = sf::Vector2f((float) size * i + (float) size, (float) size * j + (float) size);
			shape[3].position = sf::Vector2f((float) size * i + (float) size, (float) size * j);

			for (int p = 0; p < 4; p++) {
				shape[p].color = col;
			}
			win.draw(shape);
		}
    }
	
	return 0;
}

int life_update(bool** grid, char** grid_nbors, char** grid_nbors_buffer) {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (grid[i][j]) {
				if (grid_nbors[i][j] < 2 || grid_nbors[i][j] > 3) {
					grid[i][j] = false;
					neighbor_subtract(grid_nbors_buffer, i, j);
				}
			} else {
				if (grid_nbors[i][j] == 3) {
					grid[i][j] = true;
					neighbor_add(grid_nbors_buffer, i, j);
				}
			}
		}
	}
	
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			grid_nbors[i][j] = grid_nbors_buffer[i][j];
		}
	}
	
	return 0;
}