#include "scenegameover.h"
#include "ui_scenegameover.h"
#include <QPushButton>
#include <QLabel>
#include<QPainter>
#include<QPropertyAnimation>
#include "sceneplay.h"
#include<mainwindow.h>

SceneGameover::SceneGameover(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SceneGameover)
{
    ui->setupUi(this);
    setFixedSize(500,800);
    setWindowTitle("消灭炸弹");
    setWindowIcon(QIcon(":/picture/black boom.png"));
    QSize lblSize(500,50);
    QFont font("微软雅黑",20);
    QSize btnSize(320,50);

    QPushButton * btnRestart = new QPushButton("重新开始",this);
    QPushButton * btnBack = new QPushButton("返回主页",this);
    QPushButton * btnQuit = new QPushButton("退出",this);

    btnRestart->move(90,480);
    btnBack->move(90,580);
    btnQuit->move(90,680);

    btnRestart->resize(btnSize);
    btnBack->resize(btnSize);
    btnQuit->resize(btnSize);

    btnRestart->setFont(font);
    btnBack->setFont(font);
    btnQuit->setFont(font);
    //测试用//
    scoreCurrent = 9999;
    scoreHighest=10000;


    QString strCurrent = QString("本次得分：%1").arg(scoreCurrent);
    QString strHighest = QString("历史最高：%1").arg(scoreHighest);

    QLabel *labelCurrent = new QLabel(strCurrent,this);
    QLabel *labelHightest = new QLabel(strHighest,this);

    labelCurrent->move(0,230);
    labelHightest->move(0,330);

    labelCurrent->resize(lblSize);
    labelHightest->resize(lblSize);

    labelCurrent->setFont(font);
    labelHightest->setFont(font);

    labelCurrent->setAlignment(Qt::AlignHCenter);
    labelHightest->setAlignment(Qt::AlignHCenter);

    if(scoreCurrent > scoreHighest)
        {
            QLabel *lblNewRecord = new QLabel("新纪录！",this);
            QPalette pe;
            QFont font("微软雅黑",13);
            font.setBold(true);
            pe.setColor(QPalette::WindowText,Qt::red);
            lblNewRecord->setPalette(pe);
            lblNewRecord->move(240,270);
            lblNewRecord->setFont(font);

            QPropertyAnimation *animation = new QPropertyAnimation(lblNewRecord,"pos");
            QPropertyAnimation *animation2 = new QPropertyAnimation(lblNewRecord,"pos");

            animation->setStartValue(QPoint(240,270));
            animation->setEndValue(QPoint(335,270));
            animation->setDuration(1000);
            animation->start();

            animation2->setStartValue(QPoint(335,270));
            animation2->setEndValue(QPoint(240,270));
            animation2->setDuration(1000);

            connect(animation,&QAbstractAnimation::finished,[=](){
                animation2->start();
            });
            connect(animation2,&QAbstractAnimation::finished,[=](){
                animation->start();
            });
    }

    connect(btnRestart,&QPushButton::clicked,[=](){
        emit gameoverRestart();
    });

    connect(btnQuit,&QPushButton::clicked,[=](){
       this->close();
    });

    connect(btnBack,&QPushButton::clicked,[=](){
        this->close();
        MainWindow *m = new MainWindow;
        m->show();
    });
}

void SceneGameover::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pixBackground;
    pixBackground.load(":/img/background.png");
    painter.drawPixmap(0,0,500,800,pixBackground);
    QPixmap pixGameover;
    pixGameover.load(":/img/game_over.png");
    painter.drawPixmap(148,50,245,138,pixGameover);
}

SceneGameover::~SceneGameover()
{
    delete ui;
}

