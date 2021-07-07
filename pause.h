#ifndef PAUSE_H
#define PAUSE_H

#include<form.h>
#include<sceneplay.h>
#include<sceneplay_02.h>
#include <QWidget>

namespace Ui {
class pause;
}

class pause : public QWidget
{
    Q_OBJECT

public:
    explicit pause(QWidget *parent = nullptr);
    ~pause();

private slots:
    void on_setting_3_clicked();

    void on_quitBtn_clicked();

    void on_continueBtn_clicked();

    void on_restartBtn_clicked();

private:
    Ui::pause *ui;
};

#endif // PAUSE_H
