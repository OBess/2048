#include "tile.h"

//Main
Tile::Tile(){}
Tile::Tile(int x, int y, int w, int h, int value){
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->value = value;
    this->upgradet = false;
}
//~Main

//Setters
void Tile::setStartValue(){
    this->value = START_VALUE;
}
void Tile::clear(){
    this->value = 0;
}
void Tile::setUpgradet(bool value){
    this->upgradet = value;
}
//~Setters

//Getters
QRect Tile::getRect(){
    return QRect(this->x, this->y, this->w, this->h);
}
int Tile::getValue(){
    return this->value;
}
//~Getters

//Valids
bool Tile::isZero(){
    return this->value == 0;
}
bool Tile::isUpgradet(){
    return this->upgradet;
}
bool Tile::hasValue(){
    return !(this->isZero());
}
bool Tile::equelValue(int &other){
    return this->value == other;
}
void Tile::upgrade(int start_value){
    if(this->value == 0)
        this->value = start_value;
    else {
        this->value *= start_value;
        this->upgradet = true;
    }
}
//~Valids

//Moving
bool Tile::left(std::vector<std::vector<Tile>> *map){
    bool isChanged = false;
    for(int j = 1; j < SIZE; j++){
        for(int i = 0; i < SIZE; i++){
            for(int k = j - 1, o = j; k >= 0; k--, o--){
                if((*map)[i][o].isUpgradet()) break;
                if((*map)[i][o].isZero()) break;
                if((*map)[i][k].isZero()){
                    (*map)[i][k].upgrade((*map)[i][o].getValue());
                    (*map)[i][o].clear();
                    isChanged = true;
                } else if(!(*map)[i][k].isUpgradet() && (*map)[i][k] == (*map)[i][o]){
                    (*map)[i][k].upgrade();
                    (*map)[i][k].setUpgradet(true);
                    (*map)[i][o].clear();
                    isChanged = true;
                    break;
                } else
                    break;
            }
        }
    }
    return isChanged;
}
bool Tile::top(std::vector<std::vector<Tile>> *map){
    bool isChanged = false;
    for(int i = 1; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            for(int k = i - 1, o = i; k >= 0; k--, o--){
                if((*map)[o][j].isUpgradet()) break;
                if((*map)[o][j].isZero()) break;
                if((*map)[k][j].isZero()){
                    (*map)[k][j].upgrade((*map)[o][j].getValue());
                    (*map)[o][j].clear();
                    isChanged = true;
                } else if(!(*map)[i][k].isUpgradet() && (*map)[k][j] == (*map)[o][j]){
                    (*map)[k][j].upgrade();
                    (*map)[k][j].setUpgradet(true);
                    (*map)[o][j].clear();
                    isChanged = true;
                    break;
                } else
                    break;
            }
        }
    }
    return isChanged;
}
bool Tile::right(std::vector<std::vector<Tile>> *map){
    bool isChanged = false;
    for(int j = SIZE - 2; j >= 0; j--){
        for(int i = 0; i < SIZE; i++){
            for(int k = j + 1, o = j; k < SIZE; k++, o++){
                if((*map)[i][o].isUpgradet()) break;
                if((*map)[i][o].isZero()) break;
                if((*map)[i][k].isZero()){
                    (*map)[i][k].upgrade((*map)[i][o].getValue());
                    (*map)[i][o].clear();
                    isChanged = true;
                } else if(!(*map)[i][k].isUpgradet() && (*map)[i][k] == (*map)[i][o]){
                    (*map)[i][k].upgrade();
                    (*map)[i][k].setUpgradet(true);
                    (*map)[i][o].clear();
                    isChanged = true;
                    break;
                } else
                    break;
            }
        }
    }
    return isChanged;
}
bool Tile::down(std::vector<std::vector<Tile>> *map){
    bool isChanged = false;
    for(int i = SIZE - 2; i >= 0; i--){
        for(int j = 0; j < SIZE; j++){
            for(int k = i + 1, o = i; k < SIZE; k++, o++){
                if((*map)[o][j].isUpgradet()) break;
                if((*map)[o][j].isZero()) break;
                if((*map)[k][j].isZero()){
                    (*map)[k][j].upgrade((*map)[o][j].getValue());
                    (*map)[o][j].clear();
                    isChanged = true;
                } else if(!(*map)[i][k].isUpgradet() && (*map)[k][j] == (*map)[o][j]){
                    (*map)[k][j].upgrade();
                    (*map)[k][j].setUpgradet(true);
                    (*map)[o][j].clear();
                    isChanged = true;
                    break;
                } else
                    break;
            }
        }
    }
    return isChanged;
}
bool Tile::move(QKeyEvent *event, std::vector<std::vector<Tile>> *map){
    std::vector<std::vector<Tile>> pastMap = *map;
    switch (event->key()) {
    case Qt::Key_A:
    case Qt::Key_Left:
        return Tile::left(map);
    case Qt::Key_W:
    case Qt::Key_Up:
        return Tile::top(map);
    case Qt::Key_D:
    case Qt::Key_Right:
        return Tile::right(map);
    case Qt::Key_S:
    case Qt::Key_Down:
        return Tile::down(map);
    default:
        return false;
    }
}
//~Moving

//Operators
bool Tile::operator==(const Tile &other){
    return this->value == other.value;
}
bool Tile::operator!=(const Tile &other){
    return !(this->value == other.value);
}
void Tile::operator=(const Tile &other){
    this->x = other.x;
    this->y = other.y;
    this->h = other.h;
    this->w = other.w;
    this->value = other.value;
}
//~Operators
