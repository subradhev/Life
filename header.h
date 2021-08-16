#ifndef HEADER_H
#define HEADER_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <stdlib.h>
#include <time.h>
#include <iostream>

extern int size;
extern int width;
extern int height;

int neighbor_subtract(char** grid_nbors, int i, int j);
int neighbor_add(char** grid_nbors, int i, int j);
int display(sf::VertexArray shape, bool** grid, sf::RenderWindow& win);
int life_update(bool** grid, char** grid_nbors, char** grid_nbors_buffer);
int dealloc(bool** grid, char** grid_nbors, char** grid_nbors_buffer);
int draw_borders(sf::RenderWindow& win);

#endif