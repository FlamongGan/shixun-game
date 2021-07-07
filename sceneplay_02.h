#ifndef SCENEPLAY_02_H
#define SCENEPLAY_02_H

#include <QMainWindow>
#include <enemy.h>
#include<QTimer>
#include<QPropertyAnimation>
#include<QLabel>
#include<scenegameover.h>
#include<pause.h>
#include<QSound>

#include <QMainWindow>

class scenePlay_02 : public QMainWindow
{
    Q_OBJECT
public:
    explicit scenePlay_02(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);

    int index_1;
    int index_2;
    int interval;
    int score;
    QSound *home;
    QVector<int> arrayInterval;
    QVector<bool> onTheRight;
    QVector<Enemy*> arrayEnemy;
    QTimer *timer = NULL;
    QPropertyAnimation *drop = NULL;
    QLabel *labelScore = NULL;
    QLabel *labelReminder = NULL;
    QLabel *labelJudge = NULL;
    QString strScore;
    SceneGameover *gameover = NULL;

    void enemyMove();

    void keyPressEvent(QKeyEvent *e);

    void judgement();

    void judgementLeft();
    void judgementRight();

    void isGameover();

    void showEvent(QShowEvent *);

signals:

};

#endif // SCENEPLAY_02_H
