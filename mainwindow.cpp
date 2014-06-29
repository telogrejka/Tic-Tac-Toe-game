#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "xml.h"
#include "game.h"

using namespace std;

QFile txtRecords("c://records.txt");
QFile file("c://records.xml");
QDomDocument doc("records");
QDomElement  domElement = doc.createElement("records");
Game game;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // review notes: Зачем нужна данная строка? Какова ее цель? Можно-ли ее убрать?
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(repaint()));
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setScin(int)));

    // review notes: А где лучше всего выполнит эти 3 строки инициализауии объекта класса game?
    game.Xwins = 0, game.Owins = 0;
    game.start = false;
    game.Reset(QPixmap(":/images/images/X.bmp"), QPixmap(":/images/images/O.bmp"));

    // review notes: А где лучше всего выполнит эти строки инициализауии объекта класса Ui::MainWindow?
    ui->comboBox->addItem("Default");
    ui->comboBox->addItem("Red");
}

MainWindow::~MainWindow()
{
    // review notes: А как лучше владеть и удалять объект ui?
    delete ui;
}

void MainWindow::readRecord()
{
    // review notes: Роман, представте, что вы закачик или руководитель проекта.
    // review notes: Вы бы в такой ситуации были рады получить программу с неработующим функционалом и кучей задукоментированного кода?

    //  Чтение рекодров из XML-файла

//    QXmlStreamReader xmlReader;
//    if(file.open(QIODevice::ReadOnly))
//    {
//        QString s(file.readAll());
//        xmlReader.addData(s);
//        while(!xmlReader.atEnd())
//        {
//            if(xmlReader.isStartElement())
//            {
//                QStringList sl;
//                sl << xmlReader.name().toString();
//                QTreeWidgetItem* item =  QTreeWidgetItem(sl);

//            }
//            xmlReader.readNext();

//        }
//        file.close();
//    }

//    XML xml;
//    if(file.open(QIODevice::ReadOnly))
//    {
//            qDebug() << "XML file is open";
//            if(doc.setContent(&file))
//            {
//                QDomElement domElement = doc.documentElement();
//                xml.traverseNode(domElement);
//            }
//            file.close();
//     }
//    else
//        qDebug() << "Can't open XML file";
}


void MainWindow::writeRecord()
{
    // Запись рекордов в XML-файл

//    XML xml;
//    doc.appendChild(domElement);

//    QDomElement record1 = xml.record(doc, playerName, QString::number(game.points), QDate::currentDate().toString());

//    domElement.appendChild(record1);
//    if(file.open(QIODevice::WriteOnly))
//    {
//           QTextStream(&file) << doc.toString();
//           file.close();
//    }
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

        // review notes: Где лучше всего провести инициализацию объекта ui?
        ui->newGameButton->setEnabled(true);
        ui->turnLabel->setEnabled(true);
        //readRecord();
        if(ui->rb2Players->isChecked())
            mode = 0;   // review notes: Что означает 0? Какой он смысл несет? Вам знакомо, что такое именнованная константа?
        if(ui->rbComp->isChecked())
        {
            mode = 1;   // review notes: Что означает 1? Какой он смысл несет? Вам знакомо, что такое именнованная константа?
            ui->turnLabel->setText(" ");
        }
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    //Отрисовка поля

    QPainter painter(this);
    painter.setPen( Qt::gray );
    painter.drawLine(QPoint(382,0), QPoint(382, 384));
    painter.drawImage(QRect (0, 0, 384, 384), back);
    for (int i = 0; i < 9; i++)
    {
        painter.drawPixmap(game.coords.at(i), game.all.at(i));
    }

    // review notes: Что означают магические числа 382, 384, 0, 9? Вам знакомо, что такое именнованная константа?
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    // Если игра начата и кликнуто по полю
    if(game.start && event->x() <= 384)
    {
        // Берем координаты нажатой клетки
        int x = event->pos().x() / 128;
        int y = event->pos().y() / 128;
        // Если мы нажали на пустую клетку
        if(game.grid[x][y] == 0)
        {
            // Если 0 - режим 2 игрока, если 1 - игра с компьютером
            if(mode == 0)
            {
                // Устанавливаем крестик или нолик в клетку
                game.grid[x][y] = game.currplayer;
                //Передаем ход следующему игроку
                if(game.currplayer == 1)
                {
                        game.currplayer = 2;
                        ui->turnLabel->setText(QString("Сейчас ходит: O"));
                }
                else
                {
                        game.currplayer = 1;
                        ui->turnLabel->setText(QString("Сейчас ходит: X"));
                }
            }
            if (mode == 1)
            {
                // Устанавливаем крестик в клетку
                game.grid[x][y] = 1;
                // Устанавливаем нолик в клетку
                bool check = true;

                int count = 0;
                for(int i = 0; i < 3; i++)
                    for(int j = 0; j < 3; j++)
                        if(game.grid[i][j] != 0)
                            count++;
                if(count == 9) check = false;

                while(check)
                {
                    // review note: а как бы сделать не случайный процесс игры компьютера?
                    int rx = qrand() % 3;
                    int ry = qrand() % 3;
                    if (game.grid[rx][ry] == 0)
                    {
                        game.grid[rx][ry] = 2;
                        check = false;
                    }
                }
            }
            // Рисуем крестики и нолики
            // review notes: Не могли бы вы проще переписать проще данный цикл?
            int k = 0;
            for(int i = 0; i < 3; i++)
            {
                for(int j = 0; j < 3; j++)
                {
                    if(game.grid[i][j] != 0)
                    {
                        game.all[i+j+k] = game.player.at(game.grid[i][j]-1);
                        game.coords[i+j+k] = QRect(i * 132, j * 132, game.picSize, game.picSize);
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
            // review notes: Как правильно работать состроками? Корректно ли их так просто упоминать в тексте программы?
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
    if(mode == 1)
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
    // alex.ter: Вам не кажется, что у этого метод и метода MainWindow::setScin(int index) много общего?
    switch(ui->comboBox->currentIndex())
    {
        case(0):
            setScinParam(122, ":/images/images/back.bmp");
            game.Reset(QPixmap(":/images/images/X.bmp"), QPixmap(":/images/images/O.bmp"));
            break;
        case(1):
            setScinParam(100, ":/images/images/red/pole.png");
            game.Reset(QPixmap(":/images/images/red/Kre.png"), QPixmap(":/images/images/red/No.png"));
            break;
        default:
            break;
    }
    repaint();
}

void MainWindow::setScinParam(int size, QString pole)
{
    back.load(pole);
    game.picSize = size;
    game.player.clear();
}

void MainWindow::setScin(int index)
{
    if (game.start)
    {
        switch(index)
        {
            // review notes: Что означает 0? Какой он смысл несет? Вам знакомо, что такое именнованная константа?
            case(0):
                // review notes: Что означает 122? Какой смысл несет это число?
                setScinParam(122, ":/images/images/back.bmp");
                // review notes: Хорошо ли так просто укаывать имена путей?
                game.LoadingImage(QPixmap(":/images/images/X.bmp"), QPixmap(":/images/images/O.bmp"));
                break;
            // review notes: Что означает 1? Какой смысл несет это число?
            case(1):
                // review notes: Что означает 100? Какой смысл несет это число?
                setScinParam(100, ":/images/images/red/pole.png");
                game.LoadingImage(QPixmap(":/images/images/red/Kre.png"), QPixmap(":/images/images/red/No.png"));
                break;
            default:
                break;
        }
    }
    repaint();
}
