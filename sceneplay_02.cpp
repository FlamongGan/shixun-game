#include "sceneplay_02.h"
#include "enemy.h"
#include "scenegameover.h"
#include<QPainter>
#include<QTimer>
#include<QDebug>
#include<QPropertyAnimation>
#include<QKeyEvent>
#include<QLabel>
#include<QPushButton>
#include<QSound>


scenePlay_02::scenePlay_02(QWidget *parent) : QMainWindow(parent)
{
    setFixedSize(500,800);
    setWindowTitle("消灭炸弹");
    setWindowIcon(QIcon(":/picture/black boom.png"));

    home= new QSound(":/sound/02.wav",this);
    home -> play();

    QPushButton *btnPause_02 = new QPushButton(QIcon(":/picture/pause.png"),"",this);
    btnPause_02->setIconSize(QSize(40,40));
    btnPause_02->move(440,10);
    btnPause_02->setFixedSize(QSize(50,50));
    btnPause_02->setFlat(true);

    connect(btnPause_02,&QPushButton::clicked,[=](){
        pause *p = new pause;
        p->show();

    });
    btnPause_02->setFocusPolicy(Qt::NoFocus);

    QFont font("微软雅黑",20);
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);

    QFont judgeFont("Castellar",15);
    labelJudge = new QLabel(this);
    labelJudge->setPalette(pa);
    labelJudge->setFont(judgeFont);
    labelJudge->setVisible(false);
    labelJudge->setAlignment(Qt::AlignHCenter);
    labelJudge->setGeometry(200,550,100,100);


    labelScore = new QLabel(this);
    labelScore->setFont(font);
    labelScore->setGeometry(0,0,200,40);
    labelScore->setPalette(pa);
    strScore = QString("分数：%1").arg(score);
    labelScore->setText(strScore);

    gameover = new SceneGameover;

    connect(gameover,&SceneGameover::gameoverRestart,[=](){

        qDebug()<<"okkk";
        this->show();
        gameover->hide();
    });
}

void scenePlay_02::showEvent(QShowEvent *)
{
    score = 0;
    index_1 = 0;
    index_2 = 0;

    home= new QSound(":/sound/02.wav",this);
    home -> play();
    QFont font("微软雅黑",20);
    labelReminder = new QLabel("请按键盘任意键继续",this);
    labelReminder->setAlignment(Qt::AlignHCenter);
    labelReminder->setGeometry(50,400,400,40);
    labelReminder->setVisible(false);
    labelReminder->setFont(font);

    strScore = QString("分数：%1").arg(score);
    labelScore->setText(strScore);

    gameover = new SceneGameover;

    ///间隔数据,左右数据
    QVector<int>().swap(arrayInterval);
    QVector<bool>().swap(onTheRight);
    QVector<Enemy*>().swap(arrayEnemy);
    int k[40]={1400,516,1000,1032,1005,516,435,1032,978,1032,978,1005,500,500,1005,489,516,463,542,517,461,1522,516,978,516,543,1005,951,470,470,1042,996,978,1032,951,516,2000};
    int j [40]={1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,0,1,0,1,0,1,0,0,1,1,1,0,0,1,1,1,0,1,0,1,0,1,0,1};
    for(int i =1;i<40;i++)
    {
        arrayInterval.push_back(k[i-1]);
        onTheRight.push_back(j[i-1]);
    }

    interval = arrayInterval[index_1];

    for(int i =1;i<=arrayInterval.count();i++)
    {
        arrayEnemy.push_back(new Enemy(onTheRight[i-1],this));
        arrayEnemy[i-1]->setVisible(true);
    }

    timer = new QTimer(this);
    timer->start(interval);
    timer->setInterval(0);

    connect(timer,&QTimer::timeout,this,&scenePlay_02::enemyMove);

    QTimer *timerCheck = new QTimer(this);
    timerCheck->start(10);
    connect(timerCheck,&QTimer::timeout,[=](){
        if(index_2==arrayEnemy.count())
            timerCheck->stop();
        else if(arrayEnemy[index_2]->pos().y()>775)
            judgement();
    });
    connect(gameover,&SceneGameover::gameoverRestart,[=](){
        gameover->hide();
        this->show();
    });
}

void scenePlay_02::enemyMove()
{
    drop = new QPropertyAnimation;
    drop->setTargetObject(arrayEnemy[index_1]);
    drop->setPropertyName("pos");
    drop->setStartValue(QPoint(arrayEnemy[index_1]->pos().x(),arrayEnemy[index_1]->pos().y()));
    drop->setEndValue(QPoint(arrayEnemy[index_1]->pos().x(),arrayEnemy[index_1]->pos().y()+850));
    drop->setDuration(3000);
    drop->start();
    index_1++;
    if(index_1==arrayInterval.count()) timer->stop();
    interval = arrayInterval[index_1-1];
    timer->setInterval(interval);
}

void scenePlay_02::isGameover()
{
    labelReminder->setVisible(false);
    this->hide();
    gameover->show();

}

void scenePlay_02::keyPressEvent(QKeyEvent *e)
{
    if(index_2==arrayEnemy.count())
    {
        isGameover();
        return;
    }
    else
        switch(e->key())
        {
        case Qt::Key_Left:
            judgementLeft();break;

        case Qt::Key_Right:
            judgementRight();break;

        default:
            break;
        }
}

void scenePlay_02::judgement()
{
    int dis = arrayEnemy[index_2]->pos().y() - 575;

    if(dis>=-100&&dis<=100)
    {
        arrayEnemy[index_2]->setVisible(false);
        if(dis<=20&&dis>=-20)
        {
            qDebug()<<dis;
            qDebug()<<"Perfect";
            labelJudge->setText("Great!");
            labelJudge->setVisible(true);
            QTimer::singleShot(300,labelJudge,[=](){
                labelJudge->setVisible(false);
            });
            score += 100;
            strScore =QString("得分:%1").arg(score);
            labelScore->setText(strScore);
            index_2++;
        }
        else if((dis<=50&&dis>20)||(dis>=-50&&dis<-20))
        {
            qDebug()<<dis;
            qDebug()<<"Good";
            labelJudge->setText("Good!");
            labelJudge->setVisible(true);
            QTimer::singleShot(300,labelJudge,[=](){
                labelJudge->setVisible(false);
            });
            score +=50;
            strScore =QString("得分:%1").arg(score);
            labelScore->setText(strScore);
            index_2++;
        }
        else if((dis<=100&&dis>50)||(dis>=-100&&dis<-50))
        {
            qDebug()<<dis;
            qDebug()<<"Poor";
            labelJudge->setText("OK!");
            labelJudge->setVisible(true);
            QTimer::singleShot(300,labelJudge,[=](){
                labelJudge->setVisible(false);
            });
            score +=20;
            strScore =QString("得分:%1").arg(score);
            labelScore->setText(strScore);
            index_2++;
        }
    }
    else if(dis>100)
    {
        qDebug()<<dis;
        qDebug()<<"Bad";
        labelJudge->setText("Miss!");
        labelJudge->setVisible(true);
        QTimer::singleShot(300,labelJudge,[=](){
            labelJudge->setVisible(false);
        });
        arrayEnemy[index_2]->setVisible(false);
        index_2++;
    }

    else
        return;
    if(index_2==arrayEnemy.count())
    {
        labelReminder->setVisible(true);
    }
}


void scenePlay_02::judgementLeft()
{
    if(arrayEnemy[index_2]->onTheRight == 1)
        return;
    else
        judgement();
}

void scenePlay_02::judgementRight()
{
    if(arrayEnemy[index_2]->onTheRight == 0)
        return;
    else
        judgement();
}


void scenePlay_02::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::white);

    QPixmap pixBackground;
    pixBackground.load(":/img/level_02");
    pixBackground = pixBackground.scaled(500,800);
    painter.drawPixmap(0,0,500,800,pixBackground);

    painter.setPen(pen);
    painter.drawEllipse(QPoint(125,600),20,20);
    painter.drawEllipse(QPoint(375,600),20,20);
}

