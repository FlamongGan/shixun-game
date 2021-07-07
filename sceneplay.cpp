#include "sceneplay.h"
#include "ui_sceneplay.h"
#include "enemy.h"
#include "scenegameover.h"
#include<QPainter>
#include<QTimer>
#include<QDebug>
#include<QPropertyAnimation>
#include<QKeyEvent>
#include<QLabel>
int jishu=0;



scenePlay::scenePlay(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::scenePlay)
{
    ui->setupUi(this);

    setWindowTitle("消灭炸弹");
    setWindowIcon(QIcon(":/picture/black boom.png"));
    setFixedSize(500,800);

    ui->btnPause->setIcon(QIcon(":/picture/pause.png"));
    ui->btnPause->setIconSize(QSize(40,40));
    ui->btnPause->setFlat(true);

    jishu=0;

    QFont font("微软雅黑",20);
    QFont judgeFont("Castellar",15);
    labelJudge = new QLabel(this);
    labelJudge->setFont(judgeFont);
    labelJudge->setVisible(false);
    labelJudge->setAlignment(Qt::AlignHCenter);
    labelJudge->setGeometry(200,550,100,100);

    labelScore = new QLabel(this);
    labelScore->setFont(font);
    labelScore->setGeometry(0,0,200,40);
    strScore = QString("分数：%1").arg(score);
    labelScore->setText(strScore);

    gameover = new SceneGameover;

    connect(gameover,&SceneGameover::gameoverRestart,[=](){
        this->show();
        gameover->hide();
    });

}

void scenePlay::showEvent(QShowEvent *)
{
    score = 0;
    index_1 = 0;
    index_2 = 0;

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
    int k[43]={3000,700,700,700,700,400,600,900,600,600,600,600,600,600,900,600,600,600,600,600,600,900,600,600,600,600,600,600,1300,600,600,600,600,600,600,900,600,600,600,600,600,600,600};
    int j [43]={0,0,1,0,1,0,0,1,1,1,0,0,1,1,0,1,1,0,0,1,1,0,1,1,0,0,1,1,0,0,1,0,1,0,0,1,0,0,1,1,0,0,1};
    for(int i =1;i<=43;i++)
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

    connect(timer,&QTimer::timeout,this,&scenePlay::enemyMove);

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

void scenePlay::enemyMove()
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


void scenePlay::isGameover()
{
    labelReminder->setVisible(false);
    this->hide();
    gameover->show();
}

void scenePlay::keyPressEvent(QKeyEvent *e)
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
             //judgementRight();
            break;
        }
}

void scenePlay::judgement()
{
    jishu=jishu+1;
    int dis = arrayEnemy[index_2]->pos().y() - 575;

    if(dis>=-100&&dis<=100)
    {
        fasheng(jishu);
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

void scenePlay::judgementLeft()
{
    if(arrayEnemy[index_2]->onTheRight == 1)
        return;
    else
        judgement();
}

void scenePlay::judgementRight()
{
    if(arrayEnemy[index_2]->onTheRight == 0)
        return;
    else
        judgement();
}

void scenePlay::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QPixmap pixBackground;
    pixBackground.load(":/picture/chapter_1.png");
    pixBackground = pixBackground.scaled(500,800);
    painter.drawPixmap(0,0,500,800,pixBackground);

    painter.drawEllipse(QPoint(125,600),20,20);
    painter.drawEllipse(QPoint(375,600),20,20);
}

void scenePlay::fasheng(int j)
{
    j=j-1;
    if(j==0)
   {
        QSound *s = new QSound(":/sound/C4.wav",this);
               s->play();
    }
    if(j==1)
   {
        //QMediaPlayer * player = new QMediaPlayer;

            //player->setMedia(QUrl::fromLocalFile(":/img/sound/D.mp3"));
            //player->setVolume(50);
       // QSound::play(":/img/sound/D4.wav");
        QSound *s = new QSound(":/sound/C4.wav",this);
               s->play();
        //qDebug("已经过");

    }
    if(j==2)
   {
        QSound *s = new QSound(":/sound/C4.wav",this);
               s->play();
    }
    if(j==3)
   {
        QSound *s = new QSound(":/sound/G4.wav",this);
               s->play();
    }
    if(j==4)
   {
        QSound *s = new QSound(":/sound/G4.wav",this);
               s->play();
    }
    if(j==5)
   {
        QSound *s = new QSound(":/sound/A4.wav",this);
               s->play();
    }
    if(j==6)
   {
        QSound *s = new QSound(":/sound/A4.wav",this);
               s->play();
    }
    if(j==7)
   {
        QSound *s = new QSound(":/sound/G4.wav",this);
               s->play();
    }
    if(j==8)
   {
        QSound *s = new QSound(":/sound/F4.wav",this);
               s->play();
    }
    if(j==9)
   {
        QSound *s = new QSound(":/sound/F4.wav",this);
               s->play();
    }
    if(j==10)
   {
        QSound *s = new QSound(":/sound/E4.wav",this);
               s->play();
    }
    if(j==11)
   {
        QSound *s = new QSound(":/sound/E4.wav",this);
               s->play();
    }
    if(j==12)
   {
        QSound *s = new QSound(":/sound/D4.wav",this);
               s->play();
    }
    if(j==13)
   {
        QSound *s = new QSound(":/sound/D4.wav",this);
               s->play();
    }
    if(j==14)
   {
        QSound *s = new QSound(":/sound/C4.wav",this);
               s->play();
    }
    if(j==15)
   {
        QSound *s = new QSound(":/sound/G4.wav",this);
               s->play();
    }
    if(j==16)
   {
        QSound *s = new QSound(":/sound/G4.wav",this);
               s->play();
    }
    if(j==17)
   {
        QSound *s = new QSound(":/sound/F4.wav",this);
               s->play();
    }
    if(j==18)
   {
        QSound *s = new QSound(":/sound/F4.wav",this);
               s->play();
    }
    if(j==19)
   {
        QSound *s = new QSound(":/sound/E4.wav",this);
               s->play();
    }
    if(j==20)
   {
        QSound *s = new QSound(":/sound/E4.wav",this);
               s->play();
    }
    if(j==21)
   {
        QSound *s = new QSound(":/sound/D4.wav",this);
               s->play();
    }
    if(j==22)
   {
        QSound *s = new QSound(":/sound/G4.wav",this);
               s->play();
    }
    if(j==23)
   {
        QSound *s = new QSound(":/sound/G4.wav",this);
               s->play();
    }
    if(j==24)
   {
        QSound *s = new QSound(":/sound/F4.wav",this);
               s->play();
    }
    if(j==25)
   {
        QSound *s = new QSound(":/sound/F4.wav",this);
               s->play();
    }
    if(j==26)
   {
        QSound *s = new QSound(":/sound/E4.wav",this);
               s->play();
    }
    if(j==27)
   {
        QSound *s = new QSound(":/sound/E4.wav",this);
               s->play();
    }
    if(j==28)
   {
        QSound *s = new QSound(":/sound/D4.wav",this);
               s->play();
    }
    if(j==29)
   {
        //QMediaPlayer * player = new QMediaPlayer;

            //player->setMedia(QUrl::fromLocalFile(":/img/sound/D.mp3"));
            //player->setVolume(50);
       // QSound::play(":/img/sound/D4.wav");
        QSound *s = new QSound(":/sound/C4.wav",this);
               s->play();
        //qDebug("已经过");

    }
    if(j==30)
   {
        QSound *s = new QSound(":/sound/C4.wav",this);
               s->play();
    }
    if(j==31)
   {
        QSound *s = new QSound(":/sound/G4.wav",this);
               s->play();
    }
    if(j==32)
   {
        QSound *s = new QSound(":/sound/G4.wav",this);
               s->play();
    }
    if(j==33)
   {
        QSound *s = new QSound(":/sound/A4.wav",this);
               s->play();
    }
    if(j==34)
   {
        QSound *s = new QSound(":/sound/A4.wav",this);
               s->play();
    }
    if(j==35)
   {
        QSound *s = new QSound(":/sound/G4.wav",this);
               s->play();
    }
    if(j==36)
   {
        QSound *s = new QSound(":/sound/F4.wav",this);
               s->play();
    }
    if(j==37)
   {
        QSound *s = new QSound(":/sound/F4.wav",this);
               s->play();
    }
    if(j==38)
   {
        QSound *s = new QSound(":/sound/E4.wav",this);
               s->play();
    }
    if(j==39)
   {
        QSound *s = new QSound(":/sound/E4.wav",this);
               s->play();
    }
    if(j==40)
   {
        QSound *s = new QSound(":/sound/D4.wav",this);
               s->play();
    }
    if(j==41)
   {
        QSound *s = new QSound(":/sound/D4.wav",this);
               s->play();
    }
    if(j==42)
   {
        QSound *s = new QSound(":/sound/C4.wav",this);
               s->play();
    }


}

scenePlay::~scenePlay()
{
    delete ui;
}


void scenePlay::on_btnPause_clicked()
{
    pause *p = new pause;
    p->show();
}

