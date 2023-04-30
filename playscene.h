#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include"mycoin.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = nullptr);

    PlayScene(int level);

    //重写paint事件
    void paintEvent(QPaintEvent *);

     //二维数组数据
    int gameArray[4][4];

    int levelIndex;

    MyCoin * coinBtn[4][4]; //金币按钮数组


    bool isWin = true; //是否胜利
signals:

    //信号 告诉选择场景返回
    void chooseSceneBack();

};

#endif // PLAYSCENE_H
