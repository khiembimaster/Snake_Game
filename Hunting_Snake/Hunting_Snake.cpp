#include <iostream>
#include <fstream>
#include <Windows.h>
#include <thread>
#include <conio.h>
#include <iomanip>
#include <vector>
#include <sstream>
#include "WindowsManager.h"
using namespace std;
//Constants
#define MAX_SIZE_SNAKE 10
#define MAX_SIZE_FOOD 4
#define MAX_SPEED 3
//Global variables
const char GATE_PATTERN = '#';
const char FOOD_PATTERN = 'O';
char BODY_PATTERN[] = "2112731721127284";
POINT snake[10];// snake
POINT food[4];  // food
POINT gate;     // gate
POINT spawn;    // spwan location
int CHAR_LOCK;//used to determine the direction my snake cannot move (At a moment, there is one direction my snake cannot move to)
int MOVING;//used to determine the direction my snake moves (At a moment, there are three directions my snake can move)
int SPEED;// Standing for level, the higher the level, the quicker the speed
int HEIGH_CONSOLE, WIDTH_CONSOLE;// Width and height of console-screen
int FOOD_INDEX; // current food-index
int SIZE_SNAKE; // size of snake, initially maybe 6 units and maximum size maybe
int STATE; // State of snake: dead or alive
int EXIT_GAME = 0;

POINT CURSOR;

//Draw=======================================================================================//
void EraseSnakeAndFood() {
    WindowsManager::GoTo(food[FOOD_INDEX].x, food[FOOD_INDEX].y);
    cout << ' ';
    for (int i = 0; i < SIZE_SNAKE; i++) {
        WindowsManager::GoTo(snake[i].x, snake[i].y);
        cout << ' ';
    }
}

void DrawSnakeAndFood() {
    WindowsManager::GoTo(food[FOOD_INDEX].x, food[FOOD_INDEX].y);
    cout << FOOD_PATTERN;
    int LENGTH_OF_BODY_PATTERN = sizeof(BODY_PATTERN);
    for (int i = 0; i < SIZE_SNAKE; i++) {
        WindowsManager::GoTo(snake[i].x, snake[i].y);
        cout << BODY_PATTERN[i % LENGTH_OF_BODY_PATTERN];
    }
}

void DrawGate() {
    WindowsManager::GoTo(gate.x, gate.y);
    cout << GATE_PATTERN;
}

void EraseGate() {
    WindowsManager::GoTo(gate.x, gate.y);
    cout << ' ';
}

void DrawBoard(int x, int y, int width, int height, int curPosX = 0, int curPosY = 0) {
    WindowsManager::SetColor(1, 1);
    WindowsManager::GoTo(x, y); cout << ' ';
    for (int i = 1; i < width; i++)cout << ' ';
    cout << ' ';
    WindowsManager::GoTo(x, height + y); cout << ' ';
    for (int i = 1; i < width; i++)cout << ' ';
    cout << ' ';
    for (int i = y + 1; i < height + y; i++) {
        WindowsManager::GoTo(x, i); cout << ' ';
        WindowsManager::GoTo(x + width, i); cout << ' ';
    }
    WindowsManager::SetColor(15, 0);
    WindowsManager::GoTo(curPosX, curPosY);

}

void FixConsoleWindow() {
    SetConsoleOutputCP(65001);
    WindowsManager::SetWindowSize(100, 30);
    WindowsManager::SetScreenBufferSize(100, 30);
    WindowsManager::M_SetConsoleTitle(L"Hunting Snake");
    WindowsManager::DisableResizeWindow();
    WindowsManager::ShowCur(0);
    WindowsManager::DisableCtrButton(1, 1, 1);
    WindowsManager::DisableSelection();
}

bool IsValid(int x, int y) {
    for (int i = 0; i < SIZE_SNAKE; i++) {
        if (snake[i].x == x && snake[i].y == y)
            return false;
    }
    return true;
}

void GenerateFood() {
    int x, y;
    srand(time(NULL));
    for (int i = 0; i < MAX_SIZE_FOOD; i++) {
        do {
            x = rand() % (WIDTH_CONSOLE - 1) + 1;
            y = rand() % (HEIGH_CONSOLE - 1) + 1;
        } while (IsValid(x, y) == false);
            food[i] = { x,y };
    }
}

void GenerateGateAndSpawn(){
    int x, y;
    srand(time(NULL));
    do {
        x = rand() % (WIDTH_CONSOLE - 1) + 1;
        y = rand() % (HEIGH_CONSOLE - 1) + 1;
    } while (IsValid(x, y) == false);
    gate = { x,y };

    do {
        x = rand() % (WIDTH_CONSOLE - 1) + 1;
        y = rand() % (HEIGH_CONSOLE - 1) + 1;
    } while (IsValid(x, y) == false);
    spawn = { x,y };

}

void ResetData() {
    //Initialize the global values
    CHAR_LOCK = 'A', MOVING = 'D', SPEED = 2; FOOD_INDEX = 0, WIDTH_CONSOLE = 70, HEIGH_CONSOLE = 20, SIZE_SNAKE = 6;
    // Initialize default values for snake
    snake[0] = { 10, 5 }; snake[1] = { 11, 5 };
    snake[2] = { 12, 5 }; snake[3] = { 13, 5 };
    snake[4] = { 14, 5 }; snake[5] = { 15, 5 };
    GenerateFood();//Create food array
}

void StartGame() {
    system("cls");
    ResetData(); // Intialize original data
    DrawBoard(0, 0, WIDTH_CONSOLE, HEIGH_CONSOLE); // Draw game
    STATE = 1;//Start running Thread
}

//Function exit game
void ExitGame(HANDLE t) {
    system("cls");
    EXIT_GAME = 1;
}

//Function pause game
void PauseGame(HANDLE t) {
    SuspendThread(t);
}


//Function to update global data
void Eat() {
    snake[SIZE_SNAKE] = food[FOOD_INDEX];
    if (FOOD_INDEX == MAX_SIZE_FOOD - 1)
    {
        GenerateGateAndSpawn();
        DrawGate();
    }
    else {
        FOOD_INDEX++;
        SIZE_SNAKE++;
    }
}

//Function to process the dead of snake
void ProcessDead() {
    STATE = 0;
    WindowsManager::GoTo(0, HEIGH_CONSOLE + 2);
    cout << "Dead, type y to continue or anykey to exit";
}

// Movements==================================================================================//
void MoveRight() {
    if (snake[SIZE_SNAKE - 1].x + 1 == WIDTH_CONSOLE) {
        ProcessDead();
    }
    else {
        for (int i = 0; i < SIZE_SNAKE - 1; i++) {
            snake[i].x = snake[i + 1].x;
            snake[i].y = snake[i + 1].y;
        }
        snake[SIZE_SNAKE - 1].x++;
    }
}
void MoveLeft() {
    if (snake[SIZE_SNAKE - 1].x - 1 == 0) {
        ProcessDead();
    }
    else {

        for (int i = 0; i < SIZE_SNAKE - 1; i++) {
            snake[i].x = snake[i + 1].x;
            snake[i].y = snake[i + 1].y;
        }
        snake[SIZE_SNAKE - 1].x--;
    }
}
void MoveDown() {
    if (snake[SIZE_SNAKE - 1].y + 1 == HEIGH_CONSOLE) {
        ProcessDead();
    }
    else {
        for (int i = 0; i < SIZE_SNAKE - 1; i++) {
            snake[i].x = snake[i + 1].x;
            snake[i].y = snake[i + 1].y;
        }
        snake[SIZE_SNAKE - 1].y++;
    }
}

void MoveUp() {
    if (snake[SIZE_SNAKE - 1].y - 1 == 0) {
        ProcessDead();
    }
    else {
        for (int i = 0; i < SIZE_SNAKE - 1; i++) {
            snake[i].x = snake[i + 1].x;
            snake[i].y = snake[i + 1].y;
        }
        snake[SIZE_SNAKE - 1].y--;
    }
}

void Collisions() {
    if (snake[SIZE_SNAKE - 1].x == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y == food[FOOD_INDEX].y) {
        Eat();
        return;
    }
    if (snake[SIZE_SNAKE - 1].x == gate.x && snake[SIZE_SNAKE - 1].y == gate.y) {
        snake[SIZE_SNAKE - 1] = spawn;
        return;
    }

    if (snake[0].x == spawn.x && snake[0].y == spawn.y) {
        FOOD_INDEX = 0;
        if (SPEED == MAX_SPEED) {
            SPEED = 1;
            SIZE_SNAKE = 6;
        }
        else SPEED++;
        GenerateFood();
        EraseGate();
        return;
    }
    

    for (int i = 0; i < SIZE_SNAKE - 1; ++i) {
        if (snake[SIZE_SNAKE - 1].x == snake[i].x && snake[SIZE_SNAKE - 1].y == snake[i].y) {
            WindowsManager::GoTo(0, HEIGH_CONSOLE + 1);
            cout << "You have touched your self!";
            ProcessDead();
            return;
        }
    }

}

//Subfunction for thread
void ThreadFunc() {
    while (!EXIT_GAME) {
        if (STATE == 1) {//If my snake is alive
            EraseSnakeAndFood();
            switch (MOVING) {
            case 'A':
                MoveLeft();
                break;
            case 'D':
                MoveRight();
                break;
            case 'W':
                MoveUp();
                break;
            case 'S':
                MoveDown();
                break;
            }
            Collisions();
            DrawSnakeAndFood();
            Sleep(1000 / SPEED);//Sleep function with SPEEED variable
        }
    }
    return;
}

void Save() {
    //WindowsManager::GoTo(0, HEIGH_CONSOLE + 2);
    ofstream save_file("save.txt");

    for (int i = 0; i < SIZE_SNAKE; ++i)
    {
        save_file << snake[i].x << " " << snake[i].y << " ";
    }
    for (int i = 0; i < 4; ++i)
    {
        save_file << food[i].x << " " << food[i].y << " ";
    }
    save_file << CHAR_LOCK << " "
        << MOVING << " "
        << SPEED << " "
        << HEIGH_CONSOLE << " "
        << WIDTH_CONSOLE << " "
        << FOOD_INDEX << " "
        << SIZE_SNAKE << " "
        << STATE;
    save_file.close();
}

void Load() {
    //WindowsManager::GoTo(0, HEIGH_CONSOLE + 2);

    EraseSnakeAndFood();
    ifstream load_file("save.txt");
    for (int i = 0; i < SIZE_SNAKE; ++i)
    {
        load_file >> snake[i].x;
        load_file >> snake[i].y;
    }
    for (int i = 0; i < 4; ++i)
    {
        load_file >> food[i].x;
        load_file >> food[i].y;
    }
    load_file >> CHAR_LOCK;
    load_file >> MOVING;
    load_file >> SPEED;
    load_file >> HEIGH_CONSOLE;
    load_file >> WIDTH_CONSOLE;
    load_file >> FOOD_INDEX;
    load_file >> SIZE_SNAKE;
    load_file >> STATE;
    load_file.close();
    system("cls");
    DrawBoard(0, 0, WIDTH_CONSOLE, HEIGH_CONSOLE); // Draw game
    STATE = 1;//Start running Thread
}

void RunGame() {
    int temp;
    EXIT_GAME = 0;
    thread t1(ThreadFunc); //Create thread for snake
    HANDLE handle_t1 = t1.native_handle(); //Take handle of thread
    while (1) {
        temp = toupper(_getch());
        if (STATE == 1) {
            if (temp == 'P') {
                PauseGame(handle_t1);
            }
            else if (temp == 'L') {
                PauseGame(handle_t1);
                Save();
            }
            else if (temp == 'T') {
                PauseGame(handle_t1);
                Load();
            }
            else if (temp == 27) {
                //ExitGame(handle_t1);
                EXIT_GAME = true;
                t1.join();
                return;
            }
            else {
                ResumeThread(handle_t1);
                if ((temp != CHAR_LOCK) && (temp == 'D' || temp == 'A' || temp == 'W' || temp == 'S'))
                {
                    if (temp == 'D') CHAR_LOCK = 'A';
                    else if (temp == 'W') CHAR_LOCK = 'S';
                    else if (temp == 'S') CHAR_LOCK = 'W';
                    else CHAR_LOCK = 'D';
                    MOVING = temp;
                }
            }
        }
        else {
            if (temp == 'Y') StartGame();
            else {
                //ExitGame(handle_t1);
                EXIT_GAME = true;
                t1.join();
                return;
            }
        }
    }
}

void DisplayOptions(vector<string>options, int x, int y, int new_opt, int bg_color, int text_color) {
    
    for (int i = 0; i < options.size(); ++i) {
        WindowsManager::GoTo(x, y + i);
        if (new_opt == i) {
            WindowsManager::SetColor(bg_color, text_color);
            cout << ">>" << options[i] << "<<";
            WindowsManager::SetColor(15, 0);
            continue;
        }

        WindowsManager::SetColor(15, 0);
        cout << setw(20) << left << options[i];
    }
}

void MainMenu() {
    bool exit = false;

    ifstream MainMenu("Font_MainMenu.txt");;
    stringstream menu_buff;
    menu_buff << MainMenu.rdbuf();
    MainMenu.close();
    

    int choice = 0;
    vector<string> choices = { "New Game", "Load Game", "Tutorial", "High Score" };
    


    WindowsManager::SetColor(15, 0);
    WindowsManager::GoTo(0, 0);
    cout << menu_buff.str();

    while (!exit)
    {
        DisplayOptions(choices, 40, 15, choice, 9, 10);
        char option = _getch();
        switch (option)
        {
        case 'W':
        case 'w':
            choice--;
            choice %= choices.size();
            break;
        case 'S':
        case 's':
            choice++;
            choice %= choices.size();
            break;
        case 13:
            switch(choice)
            {
            case 0:
                StartGame();
                RunGame();
                break;
            case 1:
                Load();
                RunGame();
                break;
            }
            system("cls");
            WindowsManager::SetColor(15, 0);
            WindowsManager::GoTo(0, 0);
            cout << menu_buff.str();
            break;
        case 27:
            exit = true;
            break;
        default:
            break;
        }
    }
}

void Intro() {
    ifstream Title("Title.txt");
    stringstream title_buff;
    title_buff << Title.rdbuf();
    Title.close();

    ifstream BackGround("Back_ground.txt");
    stringstream bg_buff;
    bg_buff << BackGround.rdbuf();
    BackGround.close();

    WindowsManager::GoTo(0, 0);
    WindowsManager::SetColor(15, 15);
    cout << bg_buff.str();

    WindowsManager::GoTo(0, 0);
    WindowsManager::SetColor(15, 0);
    cout << title_buff.str();

    _getch();

    system("cls");
}

// main function
int main() {
    
    FixConsoleWindow();
    Intro();
    MainMenu();
    return (0);
}
