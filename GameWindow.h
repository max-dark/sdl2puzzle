//
// Created by max on 20.05.16.
//

#ifndef SDL2PUZZLE_GAMEWINDOW_H
#define SDL2PUZZLE_GAMEWINDOW_H

#include <random>
#include "SimpleWindow.h"

class GameWindow: public SimpleWindow {
public:
    explicit GameWindow(const char* title);

    ~GameWindow() override;

    bool processEvent(const SDL_Event*) override;
private:
    static constexpr uint8_t kCellSize = 90; /// размер клетки в пикселях
    static constexpr uint8_t kNumCells    =  4; /// размер поля в клетках
    static constexpr uint8_t kEmptyCellId = 15;  /// номер квадрата с пустой клеткой

    std::random_device rnd;
    SDL_Surface*    img = nullptr;          /// картинка
    SDL_Texture*    tex = nullptr;          ///    с числами
    int             cells[kNumCells][kNumCells]; /// числовое представление игрового поля
    SDL_Rect        positions[kNumCells * kNumCells];   /// положение квадратов на картинке

    void draw();
    void initTexture();
    void initRects();  /// инициализирует массив положений и генератор чисел
    void randomize();  /// перемешивает числа на поле
    void move(int x, int y); /// перемещение числа на свободное место
    bool game(); /// проверка на окончание игры
    int Message(const char * title, const char * message, Uint32 flags);
};

#endif //SDL2PUZZLE_GAMEWINDOW_H
