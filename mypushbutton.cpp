#include "mypushbutton.h"
#include<QDebug>
#include<QPropertyAnimation>
#include<QRect>
#include<QEasingCurve>
//MyPushButton::MyPushButton(QWidget *parent) : QPushButton{parent}
//{

//}


MyPushButton::MyPushButton(QString normalImage,QString pressImg)
{
    this->normalImagePath = normalImage;

    this->pressImgPath = pressImg;

    QPixmap pix;

    bool result = pix.load(normalImage);

    if(!result){

        qDebug()<< "图片加载失败";
        return;

    }

    //设置按钮大小 图片大小
    this->setFixedSize(pix.width(),pix.height());

    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px;}");

    //设置图标
    this->setIcon(pix);

    this->setIconSize(QSize(pix.width(),pix.height()));


}

void MyPushButton::zoomDown(){

    //创建动画对象 this给谁做动画 什么动画
    QPropertyAnimation *ptr_animation = new QPropertyAnimation(this,"geometry");

    //设置动画时间 间隔
    ptr_animation->setDuration(200);

    //起始位置
    ptr_animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    ptr_animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));


    //设置弹跳曲线
    ptr_animation->setEasingCurve(QEasingCurve::OutBounce);

    ptr_animation->start();

}

void MyPushButton::zoomUp(){
    //创建动画对象 this给谁做动画 什么动画
    QPropertyAnimation *ptr_animation = new QPropertyAnimation(this,"geometry");

    //设置动画时间 间隔
    ptr_animation->setDuration(200);

    //起始位置
    ptr_animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    ptr_animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));


    //设置弹跳曲线
    ptr_animation->setEasingCurve(QEasingCurve::OutBounce);

    ptr_animation->start();


}

void MyPushButton::mousePressEvent(QMouseEvent *ptr_me){

    //如果传入图片不为空 说明有按下状态
    if(this->pressImgPath != ""){

        QPixmap pix;

        bool result = pix.load(this->pressImgPath);

        if(!result){

            qDebug()<< "图片加载失败";
            return;

        }

        //设置按钮大小 图片大小
        this->setFixedSize(pix.width(),pix.height());

        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px;}");

        //设置图标
        this->setIcon(pix);

        this->setIconSize(QSize(pix.width(),pix.height()));


    }
    //让父类执行其他的操作
    return QPushButton::mousePressEvent(ptr_me);


}


void MyPushButton::mouseReleaseEvent(QMouseEvent *ptr_me){
    //如果传入图片不为空 说明有按下状态
    if(this->pressImgPath != ""){

        QPixmap pix;

        bool result = pix.load(this->normalImagePath);

        if(!result){

            qDebug()<< "图片加载失败";
            return;

        }

        //设置按钮大小 图片大小
        this->setFixedSize(pix.width(),pix.height());

        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px;}");

        //设置图标
        this->setIcon(pix);

        this->setIconSize(QSize(pix.width(),pix.height()));


    }
    //让父类执行其他的操作
    return QPushButton::mouseReleaseEvent(ptr_me);


}





