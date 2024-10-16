#ifndef GAME_HPP
#define GAME_HPP

#include <array>
class Game {
private:
  const int grid_rows = 4;
  const int grid_cols = 4;
  std::array<std::array<int, 4>, 4> grid;
  int score;
  bool state;

public:
  Game();
  bool getGameState();
  void setGameState(bool);
	int getGridRows();
	int getGridCols();
  std::array<std::array<int, 4>, 4> getGrid();

  bool isGameOver();
  void moveUp();
  void moveDown();
  void moveLeft();
  void moveRight();

  void addRandomTile();

private:
  std::array<int, 4> combineArraysPre(const std::array<int, 4> &);
  std::array<int, 4> combineArraysPost(const std::array<int, 4> &);
};

#endif
