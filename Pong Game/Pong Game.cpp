#include <iostream>
#include <raylib.h>

using namespace std;

class Ball {
public:
    float x, y;
    int speed_x, speed_y;
    int radius;

    void Draw() {
        DrawCircle(x, y, radius, WHITE);

    };

    void Update() {
        x += speed_x;
        y += speed_y;

        if(y + radius >= GetScreenHeight() || y - radius <= 0) {
			speed_y *= -1;
		}
        if (x + radius >= GetScreenWidth() || x - radius <= 0) {
            speed_x *= -1;
		}
    }

};

class Paddle {
public:
	float x, y;
	int speed;
	float width, height;

	void Draw() {
		DrawRectangle(x, y, width, height, WHITE);
	}
    void Update() {
		if (IsKeyDown(KEY_UP)) {
			y -= speed;
		}
		if (IsKeyDown(KEY_DOWN)) {
			y += speed;
		}
        if (y <= 0) {
			y = 0;
		}
        if (y + height >= GetScreenHeight()) {
			y = GetScreenHeight() - height;
		}
	}
};

class CpuPaddle: public Paddle
{
public:
    void update(int ball_y) {
        if (y + height / 2 > ball_y) {
			y -= speed;
		}
        if (y + height / 2 <= ball_y) {
            y += speed;
    }
};

Ball ball;
Paddle player;
CpuPaddle cpu;

int main()
{
    cout << "starting game" << endl;
    int screenWidth = 1280;
    int screenHeight = 800;
    InitWindow(screenWidth,screenHeight,"Pong Game");
    SetTargetFPS(60);

    ball.radius = 20;
    ball.speed_x = 7;
    ball.speed_y = 7;
    ball.x = screenWidth / 2;
    ball.y = screenHeight / 2;

    player.width = 25;
    player.height = 120;
    player.x = screenWidth - player.width - 10;
    player.y = screenHeight / 2 - player.height / 2;
    player.speed = 6;

    cpu.width = 25;
    cpu.height = 120;
    cpu.x = 10;
    cpu.y = screenHeight / 2 - cpu.height / 2;
    cpu.speed = 6;


    while(WindowShouldClose() == false)
	{
        BeginDrawing();
        // Update
        ball.Update();
        player.Update();
        cpu.update(ball.y);

        // Drawaing
        ClearBackground(BLACK);
        DrawLine(screenWidth/2,0,screenWidth/2,screenHeight,WHITE);
        ball.Draw();
        cpu.Draw();
        player.Draw();

        EndDrawing();
	}
    CloseWindow();
    return 0;
}

