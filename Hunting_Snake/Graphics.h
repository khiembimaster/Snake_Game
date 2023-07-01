#pragma once

void DrawBoard(int x, int y, int width, int height, int curPosX = 0, int curPosY = 0) {
    WindowsManager::SetColor(1, 1);
    GotoXY(x, y); cout << ' ';
    for (int i = 1; i < width; i++)cout << ' ';
    cout << ' ';
    GotoXY(x, height + y); cout << ' ';
    for (int i = 1; i < width; i++)cout << ' ';
    cout << ' ';
    for (int i = y + 1; i < height + y; i++) {
        GotoXY(x, i); cout << ' ';
        GotoXY(x + width, i); cout << ' ';
    }
    WindowsManager::SetColor(15, 0);
    GotoXY(curPosX, curPosY);
}

//Function to process the dead of snake
void ProcessDead() {
    STATE = 0;
    GotoXY(0, HEIGH_CONSOLE + 2);
    printf("Dead, type y to continue or anykey to exit");
}

//Function to draw
void DrawSnakeAndFood(const char* str) {
    GotoXY(food[FOOD_INDEX].x, food[FOOD_INDEX].y);
    printf(str);
    for (int i = 0; i < SIZE_SNAKE; i++) {
        GotoXY(snake[i].x, snake[i].y);
        printf(str);
    }
}