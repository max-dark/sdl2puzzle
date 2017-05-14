//
// Created by max on 20.05.16.
//

#ifndef SDL2PUZZLE_WINDOW_H
#define SDL2PUZZLE_WINDOW_H

#include <random>
#include "SimpleWindow.h"

class Window:public SimpleWindow {
public:
    Window(const char* title);

    virtual ~Window();

    virtual bool processEvent(const SDL_Event*);
private:
    enum CONSTANTS {
        sQuadre = 90, /// размер клетки в пикселях
        size    =  4, /// размер поля в клетках
        empty   = 15  /// номер квадрата с пустой клеткой
    };
    std::random_device rnd;
    SDL_Surface*    img;          /// картинка
    SDL_Texture*    tex;          ///    с числами
    int             numbs[size][size]; /// числовое представление игрового поля
    SDL_Rect        rnum[size*size];   /// положение квадратов на картинке

    void draw();
    void initTexture();
    void initRects();  /// инициализирует массив положений и генератор чисел
    void randomize();  /// перемешивает числа на поле
    void move(int x, int y); /// перемещение числа на свободное место
    bool game(); /// проверка на окончание игры
    int Message(const char * title, const char * message, Uint32 flags);
};

#endif //SDL2PUZZLE_WINDOW_H
