#include "chooselevelscene.h"
#include<QMenuBar>
//引入画家
#include<QPainter>
#include"mypushbutton.h"
#include<QLabel>
#include<QTimer>
#include<QSoundEffect>


ChooseLevelScene::ChooseLevelScene(QWidget *parent)
    : QMainWindow{parent}
{
    //配置选择场景

    //设置固定大小
    this->setFixedSize(320,588);
    //设置应用图片
    this->setWindowIcon(QPixmap(":logo.icns"));

    //设置窗口标题
    this->setWindowTitle("翻金币");


    //菜单栏创建
    QMenuBar *ptr_bar = menuBar();
    setMenuBar(ptr_bar);

    //创建开始菜单
    QMenu *ptr_strarBar = ptr_bar->addMenu("开始");

    QAction *ptr_quitAct =  ptr_strarBar->addAction("退出");


    connect(ptr_quitAct,&QAction::triggered,this,[=](){
        this->close();
    });


    //返回按钮
    MyPushButton *ptr_backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    ptr_backBtn->setParent(this);

    ptr_backBtn->move(this->width()-ptr_backBtn->width(),this->height()-ptr_backBtn->height());

    //点击返回
    connect(ptr_backBtn,&QPushButton::clicked,this,[=](){

        //发送信号 返回
        emit this->chooseSceneBack();

    });

    //创建 选择关卡按钮
    //一个for循环写个矩阵
    for(int i = 0;i < 20;i++){

        MyPushButton *ptr_menuBtn = new MyPushButton(":/res/LevelIcon.png");




        ptr_menuBtn->setParent(this);

        ptr_menuBtn->move(25 + i % 4 * 70,130 + i / 4 * 70);

        //直接加文字 不行
        //ptr_menuBtn->setText(QString::number(i+1));

        //用label 这个label盖在了按钮上
        QLabel *ptr_label = new QLabel;
        ptr_label->setParent(this);
        ptr_label->setFixedSize(ptr_menuBtn->width(),ptr_menuBtn->height());
        ptr_label->move(25 + i % 4 * 70,130 + i / 4 * 70);
        ptr_label->setText(QString::number(i+1));
        //设置label上的文字对齐方式
        ptr_label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        //穿透 label
        ptr_label->setAttribute(Qt::WA_TransparentForMouseEvents);


        //监听每个按钮的事件
        connect(ptr_menuBtn,&QPushButton::clicked,this,[=](){


            QSoundEffect * chooseSound = new QSoundEffect(this);

            chooseSound->setSource(QUrl::fromLocalFile(":/res/TapButtonSound.wav"));//添加资源
            chooseSound->play();//软件启动自动播放



            this->hide();
            ptr_play = new PlayScene(i+1);

            ptr_play->setGeometry(this->geometry());

            ptr_play->show();


            //监听选择界面的 返回按钮信号
            connect(ptr_play,&PlayScene::chooseSceneBack,this,[=](){


                QSoundEffect * backSound = new QSoundEffect(this);

                backSound->setSource(QUrl::fromLocalFile(":/res/BackButtonSound.wav"));//添加资源
                backSound->play();//软件启动自动播放



                //延时返回
                QTimer::singleShot(300,this,[=](){
                    this->setGeometry(ptr_play->geometry());

                    ptr_play->hide();
                    delete ptr_play;
                    ptr_play = nullptr;

                    this->show();

                });


            });

        });




    }


}

//设置背景 用PaintEvent事件 画家方式
void ChooseLevelScene::paintEvent(QPaintEvent *){

    //画家
    QPainter painter(this);


    //加载背景
    QPixmap pix;

    pix.load(":/res/OtherSceneBg.png");


    //画上去 this->width 拉伸
    painter.drawPixmap(0,0,this->width(),this->height(),pix);


    //画背景上的图标
    pix.load(":/res/Title.png");
    //缩放

    //画上去
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);




}
