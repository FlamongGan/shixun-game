#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPainter>
#include<QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("消灭炸弹");
    setWindowIcon(QIcon(":/picture/black boom.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap background;
    background.load(":/picture/background.png");
    painter.drawPixmap(0,0,this->width(),this->height(),background);
}

void MainWindow::on_start_clicked()
{
    this->close();
    secondMainWindow *s =new secondMainWindow;
    s->show();
}


void MainWindow::on_exit_clicked()
{
    this->close();
}


void MainWindow::on_set_clicked()
{

    Form *f = new Form;
    f->show();
}

