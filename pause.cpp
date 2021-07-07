#include "pause.h"
#include "ui_pause.h"
#include<QApplication>

pause::pause(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pause)
{
    ui->setupUi(this);
    setWindowTitle("消灭炸弹");
    setWindowIcon(QIcon(":/picture/black boom.png"));

}

pause::~pause()
{
    delete ui;
}

void pause::on_setting_3_clicked()
{
    Form *f = new Form;
    f->show();
}


void pause::on_quitBtn_clicked()
{
    QApplication::exit();
}


void pause::on_continueBtn_clicked()
{
    this->close();
}


void pause::on_restartBtn_clicked()
{
    this->close();

    scenePlay *s =new scenePlay;
    s->show();
}

