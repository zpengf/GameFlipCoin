#include "mainscene.h"
#include "ui_mainscene.h"
//引入画家
#include<QPainter>
#include"mypushbutton.h"
#include<QTimer>
#include<QSoundEffect>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);


    //设置固定大小
    this->setFixedSize(320,588);
    //设置应用图片
    this->setWindowIcon(QPixmap(":logo.icns"));

    //设置窗口标题
    this->setWindowTitle("翻金币");

    //点击退出 关闭游戏
    connect(ui->actionQuit,&QAction::triggered,this,[=](){

        this->close();

    });



    //开始按钮
    MyPushButton *ptr_startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");

    ptr_startBtn->setParent(this);

    ptr_startBtn->move(this->width()*0.5-ptr_startBtn->width()*0.5,this->height()*0.7);





    connect(ptr_startBtn,&MyPushButton::clicked,this,[=](){


        QSoundEffect * startSound = new QSoundEffect(this);

        startSound->setSource(QUrl::fromLocalFile(":/res/TapButtonSound.wav"));//添加资源
        startSound->play();//软件启动自动播放



        //点击做一个弹起的特效
        ptr_startBtn->zoomDown();
        ptr_startBtn->zoomUp();


        //开始进入到选中关卡

        //延时进入选择关卡
        //实例化选择关卡场景
        ptr_choose = new ChooseLevelScene;

        //延迟多长时间 触发什么函数
        QTimer::singleShot(300,this,[=](){
            //自身隐藏
            this->hide();

            //下一个窗口跟当前窗口位置一样
            ptr_choose->setGeometry(this->geometry());
            //选择关卡场景
            ptr_choose->show();

        });


        //监听选择界面的 返回按钮信号
        connect(ptr_choose,&ChooseLevelScene::chooseSceneBack,this,[=](){

            QSoundEffect * backSound = new QSoundEffect(this);

            backSound->setSource(QUrl::fromLocalFile(":/res/BackButtonSound.wav"));//添加资源
            backSound->play();//软件启动自动播放


            //延时返回
            QTimer::singleShot(300,this,[=](){
                this->setGeometry(ptr_choose->geometry());
                ptr_choose->hide();
                delete ptr_choose;
                ptr_choose = nullptr;
                this->show();

            });


        });

    });















}
//设置背景 用PaintEvent事件 画家方式
void MainScene::paintEvent(QPaintEvent *){

    //画家
    QPainter painter(this);


    //加载背景
    QPixmap pix;

    pix.load(":/res/PlayLevelSceneBg.png");


    //画上去 this->width 拉伸
    painter.drawPixmap(0,0,this->width(),this->height(),pix);


    //画背景上的图标
    pix.load(":/res/Title.png");
    //缩放
    pix = pix.scaled(pix.width() * 0.5,pix.height() * 0.5);

    //画上去
    painter.drawPixmap(10,10,pix);




}




MainScene::~MainScene()
{
    delete ui;
}

