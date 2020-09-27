#ifndef TILE_H
#define TILE_H

//qt
#include <QKeyEvent>
#include <QRect>

//c++
#include <vector>

//consts
#include "Preprocessors.h"

class Tile
{
public:
    Tile();
    Tile(int, int, int, int, int = 0);

    QRect getRect();
    int getValue();

    bool isZero();
    bool isUpgradet();
    bool hasValue();
    bool equelValue(int &);

    void setStartValue();
    void setUpgradet(bool);

    void upgrade(int = START_VALUE);

    bool operator== (const Tile &);
    bool operator!= (const Tile &);
    void operator= (const Tile &);

    static bool move(QKeyEvent *, std::vector<std::vector<Tile>> *);
private:
    int x, y, w, h;
    int value;
    bool upgradet;

    void clear();

    static bool left(std::vector<std::vector<Tile>> *);
    static bool top(std::vector<std::vector<Tile>> *);
    static bool right(std::vector<std::vector<Tile>> *);
    static bool down(std::vector<std::vector<Tile>> *);
};

#endif // TILE_H
