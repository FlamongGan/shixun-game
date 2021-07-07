#include "enemy.h"
#include<QPixmap>
#include<QPropertyAnimation>

Enemy::Enemy(bool onTheRight,QWidget *parent) : QLabel(parent)
{

    this->setParent(parent);
    QPixmap pix;
    QString imgPath = ":/img/Bomb.png";
    pix.load(imgPath);
    pix = pix.scaled(50,50);
    resize(50,50);
    this->onTheRight = onTheRight;

    if(onTheRight == false)
        this->setGeometry(100,-50,50,50);
    else
        this->setGeometry(350,-50,50,50);


    this->setPixmap(pix);
}
