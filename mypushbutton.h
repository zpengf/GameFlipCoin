#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit 防止隐式类型转换来构造初始化
    //explicit MyPushButton(QWidget *parent = nullptr);

    //正常显示图片的路径。按下按钮显示图片的路径
    MyPushButton(QString normalImage,QString pressImg = "");

    // 弹跳 向下
    void zoomDown();
    // 弹跳 向上
    void zoomUp();


    //重写 按钮按下和释放时间
    void mousePressEvent(QMouseEvent *);


    void mouseReleaseEvent(QMouseEvent *);

    //成员属性 保存用户传入的默认显示路径
    QString normalImagePath;

    //成员属性 保存按下显示路径
    QString pressImgPath;




signals:

};

#endif // MYPUSHBUTTON_H
