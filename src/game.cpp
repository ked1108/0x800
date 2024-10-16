#ifndef GAME_HPP_IMPLEMENTATION
#define GAME_HPP_IMPLEMENTATION

#include "game.hpp"
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include <iterator>
#include <cassert>

Game::Game(){
	this->score = 0;
	this->state = true;

	for(int row = 0; row < this->grid_rows; row++)
		for(int col = 0; col < this->grid_cols; col++)
			this->grid[row][col] = 0;

	addRandomTile();
	addRandomTile();
}

bool Game::getGameState() {
	return this->state;
}

void Game::setGameState(bool state) {
	this->state = state;
}

int Game::getGridRows() {
	return this->grid_rows;
}

int Game::getGridCols() {
	return this->grid_cols;
}

std::array<std::array<int, 4>, 4> Game::getGrid() {
  return this->grid;
}

bool Game::isGameOver() {
	for(int row = 0; row < this->grid_rows; row++) {
		for(int col = 0; col < this->grid_cols; col++) {
			if(this->grid[row][col] == 0) return false;
			if(this->grid[row][col] == 11) return true;
		}
	}

	for(int row = 0; row < this->grid_rows-1; row++) {
		for(int col = 0; col < this->grid_cols-1; col++) {
			if(this->grid[row][col] == this->grid[row][col+1] ||
				this->grid[row][col] == this->grid[row+1][col])
				return false;
		}
	}

	return true;
}

void Game::moveUp() {
	for(int col = 0; col < this->grid_cols; col++) {
		std::array<int, 4> column;

		for(int i = 0; i < this->grid_rows; i++)
			column[i] = this->grid[i][col];

		std::array<int, 4> combined_col = combineArraysPost(column); 

		for(int i = 0; i < this->grid_rows; i++)
			this->grid[i][col] = combined_col[i];

	}
}

void Game::moveDown() {
	for(int col = 0; col < this->grid_cols; col++) {
		std::array<int, 4> column;

		for(int i = 0; i < this->grid_rows; i++)
			column[i] = this->grid[i][col];

		std::array<int, 4> combined_col = combineArraysPre(column); 

		for(int i = 0; i < this->grid_rows; i++)
			this->grid[i][col] = combined_col[i];

	}
}

void Game::moveLeft() {
	for(int row = 0; row < this->grid_rows; row++) {
		this->grid[row] = combineArraysPost(this->grid[row]);
		std::reverse(this->grid[row].begin(), this->grid[row].end());
	}
}

void Game::moveRight() {
	for(int row = 0; row < this->grid_rows; row++) {
		this->grid[row] = combineArraysPre(this->grid[row]);
	}
}

void Game::addRandomTile() {
	srand(time(NULL));

	typedef struct {
		int row, col;
	}Cell;

	std::vector<Cell> possible;
	for(int row = 0; row < this->grid_rows; row++) {
		for(int col = 0; col < this->grid_cols; col++) {
			if(this->grid[row][col] == 0) possible.push_back({row, col});
		}
	}

	assert(possible.size() > 0);
	Cell cell = possible[rand()%possible.size()];
	int rng = rand()%100;
	std::cout << rng << std::endl;
	int val = 1; 
	if(rng <= 15)
		val = 2;
	else if( rng >= 85)
		val = 3;

	this->grid[cell.row][cell.col] = val;
}


std::array<int, 4> Game::combineArraysPre(const std::array<int, 4>& array) {
	std::vector<int> non_zero;
	std::copy_if(array.begin(), array.end(), std::back_inserter(non_zero),
								[](const int& val)	{ 
									return val != 0;
								});


	if(non_zero.size() == 0)
		return {0, 0, 0, 0};

	for(size_t i = 0; i < non_zero.size() - 1; i++){
		if(non_zero[i] == non_zero[i+1]) {
			non_zero[i] *= 2;
			non_zero[i+1] = 0;
		}
	}
	std::vector<int> new_non_zero;
	std::copy_if(non_zero.begin(), non_zero.end(), std::back_inserter(new_non_zero), 
							[](const int& val){ 
								return val != 0;
							});

	std::array<int, 4> result = {0, 0, 0, 0};
	for(size_t i = 4 - new_non_zero.size(); i < 4; i++) {
			result[i] = new_non_zero[i - 4 - new_non_zero.size()];
	}

	return result;
}

std::array<int, 4> Game::combineArraysPost(const std::array<int, 4>& array) {
	std::vector<int> non_zero;
	std::copy_if(array.begin(), array.end(), std::back_inserter(non_zero),
								[](const int& val)	{ 
									return val != 0;
								});


	if(non_zero.size() == 0)
		return {0, 0, 0, 0};

	for(size_t i = 0; i < non_zero.size() - 1; i++){
		if(non_zero[i] == non_zero[i+1]) {
			non_zero[i] *= 2;
			non_zero[i+1] = 0;
		}
	}
	std::vector<int> new_non_zero;
	std::copy_if(non_zero.begin(), non_zero.end(), std::back_inserter(new_non_zero), 
							[](const int& val){ 
								return val != 0;
							});

	std::array<int, 4> result = {0, 0, 0, 0};
	for(size_t i = 0; i < 4 - new_non_zero.size(); i++) {
			result[i] = new_non_zero[i];
	}

	return result;
}

#endif
