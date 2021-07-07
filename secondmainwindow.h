#ifndef SECONDMAINWINDOW_H
#define SECONDMAINWINDOW_H

#include<mainwindow.h>
#include<form.h>
#include<sceneplay.h>
#include<sceneplay_02.h>
#include <QMainWindow>

namespace Ui {
class secondMainWindow;
}

class secondMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit secondMainWindow(QWidget *parent = nullptr);
    ~secondMainWindow();

    void paintEvent(QPaintEvent *);


private slots:
    void on_back_clicked();

    void on_set_2_clicked();

    void on_chap_1_clicked();

    void on_chap_2_clicked();

private:
    Ui::secondMainWindow *ui;
};

#endif // SECONDMAINWINDOW_H
