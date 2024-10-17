#include <raylib.h>
#include <string>
#include <format>
#include "game.hpp"


std::array<Color, 12> colors = {
	RAYWHITE,
	GetColor(0xD4F1F9),  // Ice Blue
	GetColor(0x8ECDE6),  // Sky Blue
	GetColor(0x4EA6D8),  // Neon Blue
	GetColor(0x37B5D9),  // Electric Cyan
	GetColor(0x1B2C40),  // Deep Space Blue
	GetColor(0x0D5BA5),  // Cyber Blue
	GetColor(0x234D95),  // Ultramarine Blue
	GetColor(0x1A3B63),  // Dark Slate Blue
	GetColor(0x112C4E),  // Twilight Blue
	GetColor(0x0A1F3A),  // Midnight Blue
	GetColor(0x041526)   // Abyssal Blue
};

bool HandleInput(Game* g) {
	bool pressed = false;
	if(IsKeyReleased(KEY_W) || IsKeyReleased(KEY_UP)){
		g->moveUp();
		pressed = true;
	}

	else if(IsKeyReleased(KEY_A) || IsKeyReleased(KEY_LEFT)) {
		g->moveLeft();
		pressed = true;
	}

	else if(IsKeyReleased(KEY_S) || IsKeyReleased(KEY_DOWN)) {
		g->moveDown();
		pressed = true;
	}

	else if(IsKeyReleased(KEY_D) || IsKeyReleased(KEY_RIGHT)) {
		g->moveRight();
		pressed = true;
	}

	return pressed;
}

void Render(Game* g) {
	BeginDrawing();
	ClearBackground(DARKGRAY);

	float cell_size = 800.0f/(float)g->getGridRows();

	std::array<std::array<int, 4>, 4> grid = g->getGrid();

	for(int r = 0; r < g->getGridRows(); r++) {
		for(int c = 0; c < g->getGridCols(); c++) {
			Rectangle rec = {c*cell_size+10+5, r*cell_size+180+5, cell_size-5, cell_size-5};
			int val = grid[r][c];
			DrawRectangleRec(rec, colors[val]);

			int hex_val = (val > 0) ? 1<<val: 0;
			std::string curr_val = std::format("{:#x}", hex_val);
			int len = MeasureText(curr_val.c_str(), 50);
			DrawText(curr_val.c_str(), (int)(rec.x+cell_size/2 - len/2), (int)rec.y+cell_size/2-25, 50, LIGHTGRAY);
		}
	}
	
	EndDrawing();
}

int main(void) {
	Game g = Game();
	std::string debug = "Test"+std::to_string(g.getGridCols());

	TraceLog(LOG_INFO, debug.c_str());
	InitWindow(820, 1000, "0x800");
	SetTargetFPS(60);

	while(!WindowShouldClose()){
		Render(&g);
		if(HandleInput(&g) && !g.isGameOver()){
			g.addRandomTile();
		}
	}

  return 0;
}
