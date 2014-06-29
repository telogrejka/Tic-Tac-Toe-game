#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "game.h"

using namespace std;

QFile txtRecords("c://records.txt");
Game game;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    game.Reset(QPixmap(DEFAULT_X_PIC), QPixmap(DEFAULT_O_PIC));
    ui->comboBox->addItem("Default");
    ui->comboBox->addItem("Red");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(ui->lineEdit->text().isEmpty() || ui->lineEdit->text() == " ")
    {
        QMessageBox::warning(this, "Ошибка", "Введите имя игрока", QMessageBox::Ok);
        ui->lineEdit->setFocus();
    }
    else
    {
        playerName.append(ui->lineEdit->text());
        ui->groupBox->hide();
        ui->welcomeLabel->hide();
        resetScin();
        game.start = true;
        ui->newGameButton->setEnabled(true);
        ui->turnLabel->setEnabled(true);
        if(ui->rb2Players->isChecked())
            mode = TWO_PLAYERS;
        if(ui->rbComp->isChecked())
        {
            mode = ONE_PLAYER;
            ui->turnLabel->setText(" ");
        }
    }
    repaint();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    //Отрисовка поля

    QPainter painter(this);
    painter.setPen( Qt::gray );
    painter.drawLine(QPoint(FIELD_SIZE,0), QPoint(FIELD_SIZE, FIELD_SIZE));
    painter.drawImage(QRect (0, 0, FIELD_SIZE, FIELD_SIZE), back);
    for (int i = 0; i < 9; i++)
    {
        painter.drawPixmap(game.coords.at(i), game.all.at(i));
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    // Если игра начата и кликнуто по полю
    if(game.start && event->x() <= FIELD_SIZE)
    {
        // Берем координаты нажатой клетки
        int x = event->pos().x() / CELL_SIZE;
        int y = event->pos().y() / CELL_SIZE;
        // Если мы нажали на пустую клетку
        if(game.grid[x][y] == EMPTY_CELL)
        {
            //TWO_PLAYERS - режим 2 игрока, ONE_PLAYER - игра с компьютером
            if(mode == TWO_PLAYERS)
            {
                // Устанавливаем крестик или нолик в клетку
                game.grid[x][y] = game.currplayer;
                //Передаем ход следующему игроку
                if(game.currplayer == X)
                {
                        game.currplayer = O;
                        ui->turnLabel->setText(QString("Сейчас ходит: O"));
                }
                else
                {
                        game.currplayer = X;
                        ui->turnLabel->setText(QString("Сейчас ходит: X"));
                }
            }
            if (mode == ONE_PLAYER)
            {
                // Устанавливаем крестик в клетку
                game.grid[x][y] = X;

                // Устанавливаем нолик в клетку
                bool check = true;

                // Проверка не заполнено ли поле
                int count = 0;
                for(int i = 0; i < 3; i++)
                    for(int j = 0; j < 3; j++)
                        if(game.grid[i][j] != 0)
                            count++;
                if(count == 9) check = false;

                // Случайно выбираем клетку
                while(check)
                {
                    int rx = qrand() % 3;
                    int ry = qrand() % 3;
                    // Если она пуста, ставим в нее нолик.
                    if (game.grid[rx][ry] == EMPTY_CELL)
                    {
                        game.grid[rx][ry] = O;
                        check = false;
                    }
                }
            }
            // Рисуем крестики и нолики
            int k = 0;
            for(int i = 0; i < 3; i++)
            {
                for(int j = 0; j < 3; j++)
                {
                    if(game.grid[i][j] != 0)
                    {
                        game.all[i+j+k] = game.player.at(game.grid[i][j]-1);
                        game.coords[i+j+k] = QRect(i * DISTANCE, j * DISTANCE, game.picSize, game.picSize);
                    }
                }
                k = 2;
                if (i == 1) k += 2;
            }
            //Перерисовываем поле
            repaint();
         }
        // Обрабатываем конец игры
        GameOverHandle(game.GameOver());
    }
}

void MainWindow::GameOverHandle(int over)
{
    // Обработка конца игры

    QString message;

    switch(over)
    {
        case 0:
            message = "Ничья! Желаете сыграть еще раз?";
            break;
        case 1:
            message = "Крестики победили! Желаете сыграть еще раз?";
            game.Xwins++;
            break;
        case 2:
            message = "Нолики победили! Желаете сыграть еще раз?";
            game.Owins++;
            break;
        // Если игра не окончена, возвращаемся из функции
        default:
            return;
    }

    // Выводим счет
    ui->countLabel->setText(QString("Игрок 1: %1\n\nИгрок 2: %2")
                            .arg(QString::number(game.Xwins)).arg(QString::number(game.Owins)));
    // Спрашиваем пользователя, хочет ли он сыграть еще раз
    int replay = QMessageBox::warning(NULL, "Игра окончена", message,
           QMessageBox::Yes | QMessageBox::No);

    switch(replay)
    {
        case QMessageBox::Yes:
            resetScin();
            ui->turnLabel->setText(QString("Сейчас ходит: X"));
            break;
        case QMessageBox::No:
            game.start = false;
            break;
        default:
            break;
    }
    repaint();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    // Считаем количество очков которые набрал игрок
    if (game.Owins != 0)
        game.points = double(game.Xwins / game.Owins);
    else
        game.points = double(game.Xwins);

    // Если рекорд побит, обновляем его в файле
    if(txtRecords.open(QFile::ReadWrite | QFile::Text))
    {
        QByteArray fileData;
        fileData = txtRecords.readAll();
        QString text(fileData);
        QString points = QString::number(game.points);
        int oldRecord = 0;
        bool finded = false;
        txtRecords.seek(0);
        int count = 0;
        while(!txtRecords.atEnd() && !finded)
        {
            count++;
            // Ищем есть ли уже запись текущего игрока
            QString temp = txtRecords.readLine();
            if(QString::compare(QString(playerName + "\n"), temp) == 0)
            {
                finded = true;
                QString oldRec = txtRecords.readLine();
                oldRecord = oldRec.toInt();
                qDebug() << "oldRecord: " << oldRecord << "currentPoints: " << game.points;
                // Если установлен новый рекорд, заменяем им старый
                if(oldRecord < game.points)
                {                
                    int i = txtRecords.pos() - oldRec.length() - count - 1;
                    text.replace(i, points.length(), points);
                    txtRecords.seek(0);
                    txtRecords.write(text.toUtf8());
                }
            }
        }
        // Если игрок еще не существует в файле, то добавляем его
        if(finded == false)
        {
            text.append(playerName);
            text.append("\n" + points + "\n");
            txtRecords.seek(0);
            txtRecords.write(text.toUtf8());
        }
        txtRecords.close();
    }
}

void MainWindow::on_lineEdit_returnPressed()
{
    ui->pushButton->click();
}

void MainWindow::on_newGameButton_clicked()
{
    resetScin();
    if(mode == ONE_PLAYER)
        ui->turnLabel->setText(" ");
    else
        ui->turnLabel->setText(QString("Сейчас ходит: X"));
    game.start = true;
    repaint();
}

void MainWindow::on_aboutButton_clicked()
{
    QMessageBox::about(this, "О программе", "Игра крестики-нолики\nРазработчик Мельников Роман");
}
void MainWindow::resetScin()
{
    switch(ui->comboBox->currentIndex())
    {
        case(DEFAULT_SKIN):
            setScinParam(DEFAULT_SKIN_SIZE, DEFAULT_BACK);
            game.Reset(QPixmap(DEFAULT_X_PIC), QPixmap(DEFAULT_O_PIC));
            break;
        case(RED_SKIN):
            setScinParam(RED_SKIN_SIZE, RED_BACK);
            game.Reset(QPixmap(RED_X_PIC), QPixmap(RED_O_PIC));
            break;
        default:
            break;
    }
    repaint();
}

void MainWindow::setScinParam(int size, QString background)
{
    back.load(background);
    game.picSize = size;
    game.player.clear();
}

