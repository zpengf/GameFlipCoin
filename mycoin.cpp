#include "mycoin.h"

//MyCoin::MyCoin(QWidget *parent)
//    : QPushButton{parent}
//{

//}


MyCoin::MyCoin(QString btnImg){

    QPixmap pix;

    bool result = pix.load(btnImg);

    if(!result){

        QString str = QString("图片 %1 加载失败").arg(btnImg);

        qDebug()<< str;

        return;

    }

    this->setFixedSize(pix.width(),pix.height());
    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px;}");

    //设置图标
    this->setIcon(pix);

    this->setIconSize(QSize(pix.width(),pix.height()));

    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    //监听正面翻转的信号槽
    connect(timer1,&QTimer::timeout,this,[=](){
        QPixmap pixmap;
        QString str = QString(":/res/Coin000%1.png").arg(this->min++);
        pixmap.load(str);
        this->setFixedSize(pixmap.width(),pixmap.height() );
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));
        if(this->min > this->max) //如果大于最大值，重置最小值，并停止定时器
        {
            this->min = 1;
            timer1->stop();

            this->isAnimation  = false;//完成
        }
    });

    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pixmap;
        QString str = QString(":/res/Coin000%1.png").arg((this->max)-- );
        pixmap.load(str);
        this->setFixedSize(pixmap.width(),pixmap.height() );
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));
        if(this->max < this->min) //如果小于最小值，重置最大值，并停止定时器
        {
            this->max = 8;
            timer2->stop();
            this->isAnimation  = false;//完成
        }
    });





}

void MyCoin::mousePressEvent(QMouseEvent *e){
    if(this->isAnimation || this->isWin)
    {
        return;
    }
    else
    {
       QPushButton::mousePressEvent(e);
    }
}



void MyCoin::changeFlag()
{
    if(this->flag){ //如果是正面，执行下列代码
        timer1->start(30);
        this->isAnimation  = true;//开始做动画
        this->flag = false;
    } else { //反面执行下列代码
        timer2->start(30);
        this->isAnimation  = true;
        this->flag = true;
    }
}



