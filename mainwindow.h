#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//qt
#include <QMainWindow>
#include <QPainter>
#include <QDebug>

//c++
#include <vector>
#include <ctime>
#include <iostream>

//custom
#include "tile.h"

//consts
#include "Preprocessors.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget * = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *) override;
    void paintEvent(QPaintEvent *) override;

private:
    void init();
    void initPainter();
    void clear();
    void restart();

    void drawArea();
    void drawTile();
    void drawGameOver();

    void randTiles(int);
    void clearUpgrades();
    void checkGameOver();

    bool hasStep();

    Ui::MainWindow *ui;
    QPainter *painter;
    std::vector<std::vector<Tile>> *tiles;

    QColor *bacgroundColor;
    QColor *fontColor;
    QColor *tileColor;
    QFont font;

    bool gameOver;
};
#endif // MAINWINDOW_H
