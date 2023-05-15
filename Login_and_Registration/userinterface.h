#include<iostream>
#include<windows.h>
using namespace std;

class UserInterface {
public:
    void borderBox(string text, int paddingRL = 0, int paddingTB = 0, int coolBorder = false) {
        int strlen = text.size();
        paddingRL += 1;
        int border = coolBorder == true ? 186 : 179;
        int row = (strlen + 2 * paddingRL);
        cout << endl;

        // Top Border
        cout << char(218);
        for (int i = 0; i < row; i++) { cout << char(196); }
        cout << char(191) << endl;

        // Middle Sections
        for (int i = 0; i < paddingTB; i++) {
            cout << char(border);
            for (int j = 0; j < row; j++) {
                cout << " ";
            }
            cout << char(border) << endl;
        }

        // Text Parts
        cout << char(border);
        for (int i = 0; i <= row; i++) {
            cout << " ";
            if (i == paddingRL - 1) {
                cout << text;
                i = row - paddingRL;
            }
        }cout << char(border) << endl;

        // Middle Sections
        for (int i = 0; i < paddingTB; i++) {
            cout << char(border);
            for (int j = 0; j < row; j++) {
                cout << " ";
            }
            cout << char(border) << endl;
        }

        // Bottom Border
        cout << char(192);
        for (int i = 0; i < row; i++) { cout << char(196); }
        cout << char(217) << endl;
    }

    // Animations
    void color(int color)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }

    void gotoxy(int x, int y)
    {
        COORD c;
        c.X = x;
        c.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    }

    void animate(string text) {
        system("CLS");
        int i, j = 0;
        while (j != 2) {
            for (i = 1;i <= 5;i++) {
                color(i);
                gotoxy(10 + j, 10 + i);
                cout << text;
                Sleep(100);
                system("CLS");
            }
            i = 0;
            j++;
        }
    }
};