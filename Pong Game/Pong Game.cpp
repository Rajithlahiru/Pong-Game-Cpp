#include <iostream>
#include <raylib.h>

using namespace std;


int player_score = 0;
int cpu_score = 0;
Color Green = Color{38, 185, 154, 255};
Color DarkGreen = Color{20, 160, 133, 255};
Color LightGreen = Color{129, 185, 154, 255};
Color Yellow = Color{243, 213, 91, 255};

class Ball {
public:
    float x, y;
    int speed_x, speed_y;
    int radius;

    void Draw() {
        DrawCircle(x, y, radius, Yellow);

    };

    void Update() {
        x += speed_x;
        y += speed_y;

        if(y + radius >= GetScreenHeight() || y - radius <= 0) {
			speed_y *= -1;
		}
        if (x + radius >= GetScreenWidth()) // cpu wins
        {
            player_score++;
            ResetBall();
        }
        if(x - radius <= 0) {
            cpu_score++;
            ResetBall();
		}
    }
    void ResetBall() {
		x = GetScreenWidth() / 2;
		y = GetScreenHeight() / 2;
		
        int speed_choice[2] = {1, -1};
        speed_x *= speed_choice[GetRandomValue(0,1)];
        speed_y *= speed_choice[GetRandomValue(0,1)];
	}

};

class Paddle {
protected:
    void LimitMovement() {
        if (y <= 0) {
            y = 0;
        }
        if (y + height >= GetScreenHeight()) {
            y = GetScreenHeight() - height;
        }
	}
public:
	float x, y;
	int speed;
	float width, height;

	void Draw() {
        DrawRectangleRounded(Rectangle{x,y,width,height}, 0.8, 0, WHITE);
	}
    void Update() {
		if (IsKeyDown(KEY_UP)) {
			y -= speed;
		}
		if (IsKeyDown(KEY_DOWN)) {
			y += speed;
		}
		LimitMovement();
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
        LimitMovement();
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

        // Collision
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height})) {
			ball.speed_x *= -1;
		}
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height})) {
            ball.speed_x *= -1;
        }


        // Drawaing
        ClearBackground(DarkGreen);
        DrawRectangle(screenWidth / 2 , 0 , screenHeight / 2, screenHeight, Green); // middle line
        DrawCircle(screenWidth / 2, screenHeight / 2, 150, LightGreen); // middle circle
        DrawLine(screenWidth/2,0,screenWidth/2,screenHeight,WHITE);
        ball.Draw();
        cpu.Draw();
        player.Draw();
        DrawText(TextFormat("%i", player_score), screenWidth / 2 - 100, 50, 50, WHITE);
        DrawText(TextFormat("%i", cpu_score), screenWidth / 2 + 50, 50, 50, WHITE);

        EndDrawing();
	}
    CloseWindow();
    return 0;
}

