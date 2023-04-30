#include "playscene.h"
#include<QPainter>
#include<QMenu>
#include<QMenuBar>
#include"mypushbutton.h"
#include<QLabel>
#include"dataconfig.h"
#include<QTimer>
#include<QPropertyAnimation>
#include<QSoundEffect>

#include"mycoin.h"

//PlayScene::PlayScene(QWidget *parent)
//    : QMainWindow{parent}
//{

//}


PlayScene::PlayScene(int level){

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




    this->levelIndex = level;


    //返回按钮
    //返回按钮
    MyPushButton *ptr_backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    ptr_backBtn->setParent(this);

    ptr_backBtn->move(this->width()-ptr_backBtn->width(),this->height()-ptr_backBtn->height());

    //点击返回
    connect(ptr_backBtn,&QPushButton::clicked,this,[=](){

        //发送信号 返回
        emit this->chooseSceneBack();

    });


    //显示当前关卡数
    QLabel *ptr_label = new QLabel(this);


    QFont font;
    font.setFamily("Baoli TC");
    font.setPointSize(30);
    ptr_label->setFont(font);
    QString str = QString("Leavel: %1").arg(this->levelIndex);
    ptr_label->setText(str);


    ptr_label->setGeometry(QRect(30, this->height() - 50,120, 50));

    //初始化二维数组
    dataConfig config;
    for(int i = 0 ; i < 4;i++)
    {
        for(int j = 0 ; j < 4; j++)
        {
            gameArray[i][j] = config.mData[this->levelIndex][i][j];
        }
    }


    //胜利图片的显示
    QLabel* winLabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move( (this->width() - tmpPix.width())*0.5 , -tmpPix.height());




    //创建金币的背景图片
    for(int i = 0 ; i < 4;i++)
    {
        for(int j = 0 ; j < 4; j++)
        {
            //绘制背景图片
            QLabel* label = new QLabel(this);
            label->setGeometry(0,0,50,50);
            label->setPixmap(QPixmap(":/res/BoardNode.png"));
            label->move(57 + i*50,200+j*50);


            QString str_coin;
            if(this->gameArray[i][j] == 1){

                str_coin = ":/res/Coin0001.png";

            } else {

                str_coin = ":/res/Coin0008.png";
            }

            MyCoin *ptr_coin = new MyCoin(str_coin);
            ptr_coin->setParent(this);
            ptr_coin->move(59 + i*50,204+j*50);
            ptr_coin->posX = i; //记录x坐标
            ptr_coin->posY = j; //记录y坐标
            ptr_coin->flag = gameArray[i][j]; //记录正反标志

            //将金币放入到金币 二维数组里 便于后期维护
            coinBtn[i][j] = ptr_coin;


            connect(ptr_coin,&MyCoin::clicked,this,[=](){
                QSoundEffect * flipSound = new QSoundEffect(this);

                flipSound->setSource(QUrl::fromLocalFile(":/res/ConFlipSound.wav"));//添加资源
                flipSound->play();//软件启动自动播放



                for(int i = 0 ; i < 4;i++)
                {
                    for(int j = 0 ; j < 4; j++)
                    {
                        coinBtn[i][j]->isWin = true;
                    }
                }



                ptr_coin->changeFlag();
                this->gameArray[i][j] = gameArray[i][j] == 0 ? 1 : 0;


                //延时翻转
                QTimer::singleShot(150,this,[=](){

                    //反转周围的金币
                    if(ptr_coin->posX + 1 <= 3){
                        //右侧金币翻转
                        coinBtn[ptr_coin->posX+1][ptr_coin->posY] ->changeFlag();
                        this->gameArray[ptr_coin->posX+1][ptr_coin->posY] = this->gameArray[ptr_coin->posX+1][ptr_coin->posY] == 0 ? 1 : 0;
                    }

                    if(ptr_coin->posX - 1 >= 0){
                        //左侧金币翻转
                        coinBtn[ptr_coin->posX - 1][ptr_coin->posY] ->changeFlag();
                        this->gameArray[ptr_coin->posX - 1][ptr_coin->posY] = this->gameArray[ptr_coin->posX - 1][ptr_coin->posY] == 0 ? 1 : 0;
                    }

                    if(ptr_coin->posY + 1 <= 3){
                        //上侧金币翻转
                        coinBtn[ptr_coin->posX][ptr_coin->posY+1] ->changeFlag();
                        this->gameArray[ptr_coin->posX][ptr_coin->posY+1] = this->gameArray[ptr_coin->posX][ptr_coin->posY+1] == 0 ? 1 : 0;
                    }


                    if(ptr_coin->posY - 1 >= 0){
                        //下侧金币翻转
                        coinBtn[ptr_coin->posX][ptr_coin->posY - 1] ->changeFlag();
                        this->gameArray[ptr_coin->posX][ptr_coin->posY - 1] = this->gameArray[ptr_coin->posX][ptr_coin->posY - 1] == 0 ? 1 : 0;
                    }

                    for(int i = 0 ; i < 4;i++)
                    {
                        for(int j = 0 ; j < 4; j++)
                        {
                            coinBtn[i][j]->isWin = false;
                        }
                    }


                    //判断是否胜利
                    this->isWin = true;
                    for(int i = 0 ; i < 4;i++)
                    {
                        for(int j = 0 ; j < 4; j++)
                        {
                            //qDebug() << coinBtn[i][j]->flag ;
                            if( coinBtn[i][j]->flag == false)
                            {
                                this->isWin = false;
                                break;
                            }
                        }
                    }
                    if(this->isWin)
                    {

                        //将所有胜利的标改为true
                        for(int i = 0 ; i < 4;i++)
                        {
                            for(int j = 0 ; j < 4; j++)
                            {
                                coinBtn[i][j]->isWin = true;
                            }
                        }

                        QPropertyAnimation * animation1 =  new QPropertyAnimation(winLabel,"geometry");
                        animation1->setDuration(1000);
                        animation1->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        animation1->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->height()));
                        animation1->setEasingCurve(QEasingCurve::OutBounce);
                        animation1->start();




                        QSoundEffect * successSound = new QSoundEffect(this);

                        successSound->setSource(QUrl::fromLocalFile(":/res/LevelWinSound.wav"));//添加资源
                        successSound->play();//软件启动自动播放




                    }





                });




            });

        }
    }







}




//设置背景 用PaintEvent事件 画家方式
void PlayScene::paintEvent(QPaintEvent *){

    //画家
    QPainter painter(this);


    //加载背景
    QPixmap pix;

    pix.load(":/res/PlayLevelSceneBg.png");


    //画上去 this->width 拉伸
    painter.drawPixmap(0,0,this->width(),this->height(),pix);


    //画背景上的图标
    pix.load(":/res/Title.png");

    //画上去
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);




}
