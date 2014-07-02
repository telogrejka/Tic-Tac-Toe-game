#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QTextStream>
#include <stdlib.h>

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
    QString secondPlayerName;     // Имя второго игрока
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
    void on_rbComp_clicked();
    void on_rb2Players_clicked();
};

#endif // MAINWINDOW_H
