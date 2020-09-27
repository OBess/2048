#include "mainwindow.h"
#include "ui_mainwindow.h"

//Main
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->init();
}

MainWindow::~MainWindow()
{
    this->clear();
    delete ui;
}
//~Main

//Start
void MainWindow::init(){
    this->painter = 0;
    this->gameOver = false;
    this->bacgroundColor = new QColor(15, 15, 10);
    this->fontColor = new QColor(31, 31, 20);
    this->tileColor = new QColor(46, 46, 31);
    this->tiles = new std::vector<std::vector<Tile>>;

    int x, y = BORDER_OFFSET;
    for(short i = 0; i < SIZE; i++){
        x = BORDER_OFFSET;

        std::vector<Tile> localTiles;
        for(short j = 0; j < SIZE; j++){
            localTiles.push_back(Tile(x, y, SIZE_TILE, SIZE_TILE));
            x += SIZE_TILE + BORDER_OFFSET;
        }
        this->tiles->push_back(localTiles);

        y += SIZE_TILE + BORDER_OFFSET;
    }

    this->randTiles(2);
}
void MainWindow::initPainter(){
    if(this->painter)
        delete this->painter;
    this->painter = new QPainter(this);
    this->painter->setPen(QPen(*this->fontColor, 1, Qt::SolidLine, Qt::SquareCap));

    this->font = this->painter->font();
    this->font.setPixelSize(FONT_SIZE);
    this->font.setBold(true);
    this->painter->setFont(this->font);
}
void MainWindow::clear(){
    delete this->painter;
    delete this->tiles;
    delete this->bacgroundColor;
    delete this->fontColor;
    delete this->tileColor;
}
void MainWindow::restart(){
    this->clear();
    this->init();
    this->update();
}
//~Start

//Randoming
void MainWindow::randTiles(int max){
    std::srand(std::time(0));
    int x = -1, y = -1, count = 0;
    while(count < max && this->hasStep()){
        x = std::rand() % (SIZE);
        y = std::rand() % (SIZE);
        if(!this->tiles->at(x)[y].hasValue()){
            this->tiles->at(x)[y].setStartValue();
            count++;
        }
    }
}
//~Randoming

//Setters
void MainWindow::clearUpgrades(){
    for(int i = 0; i < SIZE; i++)
        for(int j = 0; j < SIZE; j++)
            this->tiles->at(i)[j].setUpgradet(false);
}
//~Setters

//Valids
bool MainWindow::hasStep(){
    for(int i = 0; i < SIZE; i++)
        for(int j = 0; j < SIZE; j++)
            if(!this->tiles->at(i)[j].hasValue())
                return true;
    return false;
}
//~Valids

//Checkers
void MainWindow::checkGameOver(){
    if(this->hasStep()) return;
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if((j > 0 && this->tiles->at(i)[j - 1] == this->tiles->at(i)[j])
                    || (j < SIZE - 1 && this->tiles->at(i)[j + 1] == this->tiles->at(i)[j])
                    || (i > 0 && this->tiles->at(i - 1)[j] == this->tiles->at(i)[j])
                    || (i < SIZE - 1 && this->tiles->at(i + 1)[j] == this->tiles->at(i)[j]))
                return;
        }
    }
    this->gameOver = true;
}
//~Chekers

//Events
void MainWindow::keyPressEvent(QKeyEvent *event){
    if (!this->gameOver && Tile::move(event, tiles)){
        if(this->hasStep())
            this->randTiles(MAX_RANDOM_TILES);
        this->clearUpgrades();
        this->checkGameOver();
        this->update();
    }
    if(event->key() == Qt::Key_Space || event->key() == Qt::Key_R)
        this->restart();
}
void MainWindow::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    this->initPainter();

    this->drawArea();
    this->drawTile();
    this->drawGameOver();

    this->painter->end();
}
//~Events

//Drawing
void MainWindow::drawArea(){
    this->painter->setBrush(*this->bacgroundColor);
    this->painter->drawRect(-1, -1, this->width() + 1, this->height() + 1);
}
void MainWindow::drawTile(){
    QFontMetrics fm(this->font);
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++){
            if(this->tiles->at(i)[j].hasValue()) {
                QColor variableColor(*this->tileColor);
                float offset = 196 - (196 / this->tiles->at(i)[j].getValue()) - this->tiles->at(i)[j].getValue() / 2;
                variableColor.setRed(offset);
                variableColor.setGreen(offset);
                this->painter->setBrush(variableColor);

                this->painter->drawRect(this->tiles->at(i)[j].getRect());

                int pixWidth = fm.horizontalAdvance(QString(std::to_string(this->tiles->at(i)[j].getValue()).c_str()));
                int pixHeight = fm.height();

                this->painter->drawText(this->tiles->at(i)[j].getRect().x() + SIZE_TILE / 2 - pixWidth / 2,
                                        this->tiles->at(i)[j].getRect().y() + SIZE_TILE / 2 + pixHeight / 4,
                                        QString(std::to_string(this->tiles->at(i)[j].getValue()).c_str()));
            }
            else {
                this->painter->setBrush(*this->tileColor);
                this->painter->drawRect(this->tiles->at(i)[j].getRect());
            }
        }
    }
}
void MainWindow::drawGameOver(){
    if(!this->gameOver) return;

    this->painter->setBrush(QColor(115, 153, 102, 100));
    this->painter->drawRect(-1, -1, this->width() + 1, this->height() + 1);

    QFont font = this->painter->font();
    font.setBold(true);
    font.setPixelSize(this->width() / 7);

    this->painter->setFont(font);
    this->painter->setPen(QPen(QColor(153, 102, 102), 1, Qt::SolidLine, Qt::SquareCap));

    QFontMetrics fm(font);

    int pixWidth = fm.horizontalAdvance("Game Over!");
    int pixHeight = fm.height();

    this->painter->drawText(this->width() / 2 - pixWidth / 2, this->height() / 2 + pixHeight / 4, "Game Over!");

    font.setPointSize(this->width() / 19);
    this->painter->setFont(font);

    QFontMetrics fm1(font);
    pixWidth = fm1.horizontalAdvance("Press 'R' to restart");
    pixHeight = fm1.height();

    this->painter->drawText(this->width() / 2 - pixWidth / 2, this->height() / 2 + pixHeight + 10, "Press 'R' to restart");

    this->painter->setFont(this->font);
}
//~Drawing
