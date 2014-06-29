#ifndef GAME_H
#define GAME_H

#include <QList>
#include <QPixmap>
#include <QMessageBox>

#define FIELD_SIZE 384          // Размер игрового поля
#define CELL_SIZE 128           // Размер клетки на игровом поле
#define DEFAULT_SKIN 0          // Скин по умолчанию
#define RED_SKIN 1              // Скин "Red"
#define DEFAULT_SKIN_SIZE 120   // Размер клетки в скине по умолчанию
#define RED_SKIN_SIZE 100       // Размер клетки в скине "Red"
#define DISTANCE 132            // Расстояние между клетками
#define EMPTY_CELL 0            // Пустая клетка
#define X 1                     // Крестик
#define O 2                     // Нолик
// Изображения
#define DEFAULT_BACK ":/images/images/back.bmp"
#define DEFAULT_X_PIC ":/images/images/X.bmp"
#define DEFAULT_O_PIC ":/images/images/O.bmp"
#define RED_BACK ":/images/images/red/pole.png"
#define RED_X_PIC ":/images/images/red/Kre.png"
#define RED_O_PIC ":/images/images/red/No.png"

class Game
{
public:
    Game();
    void LoadingImage(QPixmap x, QPixmap o);
    void Reset(QPixmap x, QPixmap o);
    int GameOver();
    QList<QPixmap> all;
    QList<QPixmap> player;
    QList<QRect> coords;
    bool start;         // true - игра начата; false - игра еще не начата
    int grid[3][3];     // Массив обозначающий поле
    int currplayer;     // 1 - ходит крестик; 2 - ходит нолик
    int Xwins, Owins;   // Количество побед игроков
    double points;      // Очки игроков
    int picSize;        // Размер изображения крестика и нолика
};

#endif // GAME_H
