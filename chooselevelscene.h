#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>

#include"playscene.h"

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);

    //重写paint事件
    void paintEvent(QPaintEvent *);

    //声明一个游戏对象场景界面
    PlayScene *ptr_play = nullptr;
signals:
    //信号 告诉主场景返回
   void chooseSceneBack();

};

#endif // CHOOSELEVELSCENE_H
