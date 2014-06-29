#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QTextStream>
#include <QPainter>
#include <QMouseEvent>
#include <QPixmap>
#include <QXmlStreamReader>
#include <stdlib.h>

#define TWO_PLAYERS 0   // Режим 2 игрока
#define ONE_PLAYER 1    // Режим игры одного игрока с компьютером

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QImage back;            // Задний фон
    QString playerName;     // Имя игрока
    int mode;               // Режим игры

    void resetScin();
    void setScinParam(int size, QString back);
    void GameOverHandle(int over);

protected:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void closeEvent(QCloseEvent *event);
    
private slots:
    void on_pushButton_clicked();
    void on_lineEdit_returnPressed();
    void on_newGameButton_clicked();
    void on_aboutButton_clicked();
};

#endif // MAINWINDOW_H
