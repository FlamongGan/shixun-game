#include "secondmainwindow.h"
#include "ui_secondmainwindow.h"
#include<QIcon>
#include<QPainter>
#include<QPixmap>

secondMainWindow::secondMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::secondMainWindow)
{
    ui->setupUi(this);

    setWindowTitle("消灭炸弹");
    setWindowIcon(QIcon(":/picture/black boom.png"));

    ui->back->setIcon(QIcon(":/picture/back.png"));
    ui->back->setIconSize(QSize(40,40));
    ui->back->setFlat(true);

    ui->set_2->setIcon(QIcon(":/picture/setting.png"));
    ui->set_2->setIconSize(QSize(40,40));
    ui->set_2->setFlat(true);

    ui->chap_1->setIcon(QIcon(":/picture/chapter_1.png"));
    ui->chap_1->setIconSize(QSize(ui->chap_1->width(),ui->chap_1->height()));

    ui->chap_2->setIcon(QIcon(":/picture/chapter_2.png"));
    ui->chap_2->setIconSize(QSize(ui->chap_2->width(),ui->chap_2->height()));

}

secondMainWindow::~secondMainWindow()
{
    delete ui;
}

void secondMainWindow::paintEvent(QPaintEvent *)
{
    QPixmap background;
    QPainter painter(this);
    background.load(":/picture/background.png");
    painter.drawPixmap(0,0,this->width(),this->height(),background);
}


void secondMainWindow::on_back_clicked()
{
    this->close();
    MainWindow *m =new MainWindow;
    m->show();
}


void secondMainWindow::on_set_2_clicked()
{
    Form *f = new Form;
    f->show();
}


void secondMainWindow::on_chap_1_clicked()
{
    this->close();
    scenePlay *s_1 = new scenePlay;
    s_1->show();
}


void secondMainWindow::on_chap_2_clicked()
{
    this->close();
    scenePlay_02 *s_2 =new scenePlay_02;
    s_2->show();
}

