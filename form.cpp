#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    setWindowTitle("setting");
    setWindowIcon(QIcon(":/picture/setting.png"));
}

Form::~Form()
{
    delete ui;
}

void Form::on_back_2_clicked()
{
    this->close();

}

