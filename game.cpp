#include "game.h"

Game::Game()
{
    picSize = DEFAULT_SKIN_SIZE;
    Xwins = 0, Owins = 0;
    start = false;
    from = QPoint(0, 0), to = QPoint(0, 0);
    Reset(QImage(DEFAULT_X_PIC), QImage(DEFAULT_O_PIC));
}

void Game::LoadingImage(QImage x, QImage o)
{
    // Загрузка изображений

    player[0] = x, player[1] = o;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            all[i][j] = QImage();
            coords[i][j] = (QRect(i * DISTANCE, j * DISTANCE, picSize, picSize));
        }

}

void Game::Reset(QImage x, QImage o)
{
    // Очистка поля

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            grid[i][j] = 0;
            all[i][j] = QImage();
            coords[i][j] = QRect();
        }
    }
    player[0] = QImage();
    player[1] = QImage();

    currplayer = X;
    from = QPoint(0, 0), to = QPoint(0, 0);
    LoadingImage(x, o);
}

int Game::GameOver()
{
    // -1 - игра не окончена; 0 - ничья; 1 - победили крестики; 2 - победили нолики

    // Проверка на чью-нибудь победу
    for(int i = 1; i < 3; i++)
    {
        // По горизонтали
        if(grid[0][0] == i && grid[1][0] == i && grid[2][0] == i){
            from = QPoint(0, finDist), to = QPoint(FIELD_SIZE, finDist);
            return i;
        }
        if(grid[0][1] == i && grid[1][1] == i && grid[2][1] == i){
            from = QPoint(0, finDist * 3), to = QPoint(FIELD_SIZE, finDist * 3);
            return i;
        }
        if(grid[0][2] == i && grid[1][2] == i && grid[2][2] == i){
            from = QPoint(0, finDist * 5), to = QPoint(FIELD_SIZE, finDist * 5);
            return i;
        }

        // По вертикали
        if(grid[0][0] == i && grid[0][1] == i && grid[0][2] == i){
            from = QPoint(finDist, 0), to = QPoint(finDist, FIELD_SIZE);
            return i;
        }
        if(grid[1][0] == i && grid[1][1] == i && grid[1][2] == i){
            from = QPoint(finDist * 3, 0), to = QPoint(finDist * 3, FIELD_SIZE);
            return i;
        }
        if(grid[2][0] == i && grid[2][1] == i && grid[2][2] == i){
            from = QPoint(finDist * 5, 0), to = QPoint(finDist * 5, FIELD_SIZE);
            return i;
        }

        // По диагонали
        if(grid[0][0] == i && grid[1][1] == i && grid[2][2] == i){
            from = QPoint(0, 0), to = QPoint(FIELD_SIZE, FIELD_SIZE);
            return i;
        }
        if(grid[2][0] == i && grid[1][1] == i && grid[0][2] == i){
            from = QPoint(FIELD_SIZE, 0), to = QPoint(0, FIELD_SIZE);
            return i;
        }
    }

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
