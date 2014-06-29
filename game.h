#ifndef GAME_H
#define GAME_H

#include <QList>
#include <QPixmap>
#include <QMessageBox>

class Game
{
public:
    Game();
    void LoadingImage(QPixmap x, QPixmap o);
    void Reset(QPixmap x, QPixmap o);
    int GameOver();
    // review notes: А почему вы используете QList? Чем он лучше std::list?
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
