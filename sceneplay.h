
#ifndef SCENEPLAY_H
#define SCENEPLAY_H
#include<pause.h>
#include <QMainWindow>
#include <enemy.h>
#include<QTimer>
#include<QPropertyAnimation>
#include<QLabel>
#include<scenegameover.h>
#include <QtMultimedia/QSound>

//#include<QSound>
//#include <QtMultimedia/QMediaPlayer>
#include<QSound>
#include <QtCore/QCoreApplication>

#include <QtMultimedia/QMediaPlayer>



QT_BEGIN_NAMESPACE
namespace Ui { class scenePlay; }
QT_END_NAMESPACE

class scenePlay : public QMainWindow
{
    Q_OBJECT

public:
    scenePlay(QWidget *parent = nullptr);
    ~scenePlay();

    void paintEvent(QPaintEvent *);

    int index_1;
    int index_2;
    int interval;
    int score;
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
    void fasheng(int j);

    void showEvent(QShowEvent *);

private slots:
    void on_btnPause_clicked();

private:
    Ui::scenePlay *ui;
};
#endif // SCENEPLAY_H
