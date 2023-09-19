#define _WIN32_WINNT 0x0501
#include <stdio.h>
#include <iostream>
#include <windows.h>

LONG_PTR setConsoleWindowStyle(INT, LONG_PTR);

int main()
{
    LONG_PTR new_style = WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL;
    setConsoleWindowStyle(GWL_STYLE, new_style);
    return 0;

    //TODO: Buffer pour l'affichage � mettre dans la boucle principale du jeu
    //HANDLE hOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);

    //COORD dwBufferSize = { SCREEN_WIDTH,SCREEN_HEIGHT };
    //COORD dwBufferCoord = { 0, 0 };
    //SMALL_RECT rcRegion = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };

    //CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH];

    //ReadConsoleOutput(hOutput, (CHAR_INFO*)buffer, dwBufferSize,
    //    dwBufferCoord, &rcRegion);

    //buffer[5][10].Char.AsciiChar = 'H';
    //buffer[5][10].Attributes = 0x0E;
    //buffer[5][11].Char.AsciiChar = 'i';
    //buffer[5][11].Attributes = 0x0B;
    //buffer[5][12].Char.AsciiChar = '!';
    //buffer[5][12].Attributes = 0x0A;

    //WriteConsoleOutput(hOutput, (CHAR_INFO*)buffer, dwBufferSize,
    //    dwBufferCoord, &rcRegion);

}

//Si le new style est � 0, la fenetre n'a absolument rien � part son contenu
LONG_PTR setConsoleWindowStyle(INT n_index, LONG_PTR new_style)
{
    /*The function does not clear the last error information. if last value was zero.*/
    SetLastError(NO_ERROR);

    HWND hwnd_console = GetConsoleWindow();
    LONG_PTR style_ptr = SetWindowLongPtr(hwnd_console, n_index, new_style);
    SetWindowPos(hwnd_console, 0, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_DRAWFRAME);

    //show window after updating
    ShowWindow(hwnd_console, SW_SHOW);

    return style_ptr;
}