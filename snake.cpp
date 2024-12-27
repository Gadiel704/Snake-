#include <iostream>
#include <vector>
#include <conio.h>
#include <ctime>

using namespace std;

const int WIDTH = 20;
const int HEIGHT = 20;

struct Point {
    int x, y;
};

vector<Point> snake = {{WIDTH / 2, HEIGHT / 2}};
Point food = {rand() % WIDTH, rand() % HEIGHT};
int dx = 0, dy = 1;
bool gameOver = false;

void draw() {
    system("cls");
    for (int y = 0; y <= HEIGHT; ++y) {
        for (int x = 0; x <= WIDTH; ++x) {
            if (y == 0 || y == HEIGHT || x == 0 || x == WIDTH) {
                cout << "#";
            } else {
                bool printed = false;
                for (const auto& s : snake) {
                    if (s.x == x && s.y == y) {
                        cout << "O";
                        printed = true;
                        break;
                    }
                }
                if (food.x == x && food.y == y) {
                    cout << "*";
                } else if (!printed) {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }
}

void update() {
    Point newHead = {snake[0].x + dx, snake[0].y + dy};

    // Check for collisions
    if (newHead.x == 0 || newHead.x == WIDTH || newHead.y == 0 || newHead.y == HEIGHT) {
        gameOver = true;
        return;
    }

    for (size_t i = 1; i < snake.size(); ++i) {
        if (snake[i].x == newHead.x && snake[i].y == newHead.y) {
            gameOver = true;
            return;
        }
    }

    // Check for food
    if (newHead.x == food.x && newHead.y == food.y) {
        snake.push_back({0, 0}); // Add new segment
        food = {rand() % (WIDTH - 1) + 1, rand() % (HEIGHT - 1) + 1};
    }

    // Move the snake
    for (size_t i = snake.size() - 1; i > 0; --i) {
        snake[i] = snake[i - 1];
    }
    snake[0] = newHead;
}

void input() {
    if (_kbhit()) {
        char key = _getch();
        if (key == 'w' && dy == 0) { dx = 0; dy = -1; }
        if (key == 's' && dy == 0) { dx = 0; dy = 1; }
        if (key == 'a' && dx == 0) { dx = -1; dy = 0; }
        if (key == 'd' && dx == 0) { dx = 1; dy = 0; }
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    while (!gameOver) {
        draw();
        input();
        update();
        _sleep(100);
    }

    cout << "Game Over!" << endl;
    return 0;
}
