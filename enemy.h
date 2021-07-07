#ifndef ENEMY_H
#define ENEMY_H

#include <QLabel>

class Enemy : public QLabel
{
    Q_OBJECT
public:
    explicit Enemy(bool onTheRight,QWidget *parent = nullptr);
    bool onTheRight;

signals:

};

#endif // ENEMY_H
