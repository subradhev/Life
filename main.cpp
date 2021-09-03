#include "header.h"

int size;
int width;
int height;

int main() {
	char in;
	float delay_min = 0.05;
	
	sf::Color col;
	
	std::cout << "Input input method \n (r)andom (s)eed (m)anual" << std::endl;
	std::cout << ">> ";
	
	std::cin >> in;
	
	if (in == 'r') {
		std::cout << "TODO. Exiting..." << std::endl;
		return 0;
	} else if (in == 's') {
		std::cout << "TODO. Exiting..." << std::endl;
		return 0;
	} else if (in == 'm') {
		manual();
	} else {
		std::cout << "Invalid input. Exiting..." << std::endl;
		return 0;
	}
	
	// TODO: Create function for this along with other init methods
	// TODO: Implement a size limit
	//
	
	sf::RenderWindow window(sf::VideoMode(size * width, size * height), "Conway's Game of Life", sf::Style::Close | sf::Style::Titlebar);
	
	bool** grid = new bool*[width];
	char** grid_nbors = new char*[width];
	char** grid_nbors_buffer = new char*[width];
	for (int i = 0; i < width; i++) {
		grid[i] = new bool[height];
		grid_nbors[i] = new char[height];
		grid_nbors_buffer[i] = new char[height];
		
		for (int j = 0; j < height; j++) {
			grid[i][j] = false;
			grid_nbors[i][j] = 0;
			grid_nbors_buffer[i][j] = 0;
		}
	}
	
	sf::VertexArray cell_shape(sf::Quads, 4);
	
	window.clear();
	draw_borders(window);
	window.display();
	
	sf::Event event;
	
	bool wait = true;
	bool mouse_down = false;
	int block_x;
	int block_y;
	
	int old_x;
	int old_y;
	while (wait) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				dealloc(grid, grid_nbors, grid_nbors_buffer);
				
				return 0;
			} else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Space) {
					wait = false;
				}
			} else if (event.type == sf::Event::MouseButtonPressed) {
				mouse_down = true;
			} else if (event.type == sf::Event::MouseButtonReleased) {
				mouse_down = false;
			}
			
			if (mouse_down) {
				sf::Vector2i position = sf::Mouse::getPosition(window);
				
				block_x = position.x / size;
				block_y = position.y / size;
				
				//COORDINATE PRINT IF NEEDED
				
				if (not (block_x == old_x && block_y == old_y)) {
					old_x = block_x;
					old_y = block_y;
					if (block_x >= 0 && block_x < width && block_y >= 0 && block_y < height) {
						if (grid[block_x][block_y]) {
							grid[block_x][block_y] = false;
							neighbor_subtract(grid_nbors, block_x, block_y);
							neighbor_subtract(grid_nbors_buffer, block_x, block_y);
							col = sf::Color::Black;
						} else {
							grid[block_x][block_y] = true;
							neighbor_add(grid_nbors, block_x, block_y);
							neighbor_add(grid_nbors_buffer, block_x, block_y);
							col = sf::Color::White;
						}
						
						/*
						cell_shape[0].position = sf::Vector2f((float) size * block_x, (float) size * block_y);
						cell_shape[1].position = sf::Vector2f((float) size * block_x, (float) size * block_y + (float) size);
						cell_shape[2].position = sf::Vector2f((float) size * block_x + (float) size, (float) size * block_y + (float) size);
						cell_shape[3].position = sf::Vector2f((float) size * block_x + (float) size, (float) size * block_y);
						
						for (int i = 0; i < 4; i++) {
							cell_shape[i].color = col;
						}
						*/
						
						window.clear();
						display(cell_shape ,grid, window);
						draw_borders(window);
						
						//window.draw(cell_shape);
						window.display();
						
						
						//Consider using delta time?
					}
				}
			}
		}
	}
	
	sf::Clock clock;
	float time;
	bool run = true;
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Space) {
					if (run) {
						run = false;
					} else {
						run = true;
					}
				} else if (event.key.code == sf::Keyboard::Right) {
					if (delay_min > 0.06) {
						delay_min -= 0.05;
					}
					
					std::cout << delay_min << std::endl;
				} else if (event.key.code == sf::Keyboard::Left) {
					delay_min += 0.05; // ADD A MAX MAYBE?
					
					std::cout << delay_min << std::endl;
				}
			}
		}
		
		time = clock.getElapsedTime().asSeconds();
		if (time > delay_min && run) {
			life_update(grid, grid_nbors, grid_nbors_buffer);
		
			window.clear();
			display(cell_shape, grid, window);
			draw_borders(window);
			window.display();
			clock.restart();
		}
	}
	
	dealloc(grid, grid_nbors, grid_nbors_buffer);
	return 0;
}