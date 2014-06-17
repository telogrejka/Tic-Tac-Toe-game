#include "game.h"

Game::Game() {
    picSize = 122;
}

void Game::LoadingImage(QPixmap x, QPixmap o)
{
    // Загрузка изображений

    player.append(QPixmap());
    player.append(QPixmap());

    player[0] = x;
    player[1] = o;

    for (int i = 0; i < 9; i++)
        all.append(QPixmap());

    coords.append(QRect(0 * 132, 0 * 132, picSize, picSize));
    coords.append(QRect(1 * 132, 0 * 132, picSize, picSize));
    coords.append(QRect(2 * 132, 0 * 132, picSize, picSize));
    coords.append(QRect(0 * 132, 1 * 132, picSize, picSize));
    coords.append(QRect(1 * 132, 1 * 132, picSize, picSize));
    coords.append(QRect(2 * 132, 1 * 132, picSize, picSize));
    coords.append(QRect(0 * 132, 2 * 132, picSize, picSize));
    coords.append(QRect(1 * 132, 2 * 132, picSize, picSize));
    coords.append(QRect(2 * 132, 2 * 132, picSize, picSize));
}

void Game::Reset(QPixmap x, QPixmap o)
{
    // Очистка поля

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            grid[i][j] = 0;

    all.clear();
    coords.clear();
    player.clear();
    currplayer = 1;
    LoadingImage(x, o);
}

int Game::GameOver()
{
    // -1 - игра не окончена; 0 - ничья; 1 - победили крестики; 2 - победили нолики

    // Проверка на чью-нибудь победу
    for(int i = 1; i < 3; i++)
            // По горизонтали
        if( (grid[0][0] == i && grid[1][0] == i && grid[2][0] == i) ||
            (grid[0][1] == i && grid[1][1] == i && grid[2][1] == i) ||
            (grid[0][2] == i && grid[1][2] == i && grid[2][2] == i) ||

            // По вертикали
            (grid[0][0] == i && grid[0][1] == i && grid[0][2] == i) ||
            (grid[1][0] == i && grid[1][1] == i && grid[1][2] == i) ||
            (grid[2][0] == i && grid[2][1] == i && grid[2][2] == i) ||

            // По диагонали
            (grid[0][0] == i && grid[1][1] == i && grid[2][2] == i) ||
            (grid[2][0] == i && grid[1][1] == i && grid[0][2] == i) )
            return i;

    // Проверка на ничью
    int count = 0;
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(grid[i][j] != 0)
                count++;
    // Заполнено все поле
    if(count == 9)
        return 0;

    return -1;
}
