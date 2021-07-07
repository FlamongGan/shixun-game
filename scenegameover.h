#ifndef SCENEGAMEOVER_H
#define SCENEGAMEOVER_H


#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class SceneGameover; }
QT_END_NAMESPACE

class SceneGameover : public QMainWindow
{
    Q_OBJECT

public:
    SceneGameover(QWidget *parent = nullptr);
    ~SceneGameover();

    int scoreCurrent;
    int scoreHighest;


    void paintEvent(QPaintEvent *);

signals:
    void gameoverRestart();



private:
    Ui::SceneGameover *ui;
};
#endif // SCENEGAMEOVER_H
