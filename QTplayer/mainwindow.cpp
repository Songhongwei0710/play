#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPixmap>
#include<QFrame>
#include<QHBoxLayout>
#include<QFileDialog>
#include<QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Init();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::Init()
{
    //设置主界面背景

    QPixmap pixmap(":/image/background.jpg");//设定图片
    QPalette palette;//创建一个调色板对象
    palette.setBrush(backgroundRole(),QBrush(pixmap));//用调色板的画笔把映射到pixmap上的图片画到frame.backgroundRole()这个背景上
    setPalette(palette);//设置窗口调色板为palette，窗口和画笔相关联
    setAutoFillBackground(true);//设置窗体自动填充背景
    this->setWindowTitle(QString::fromLocal8Bit("视频播放器"));
    this->setWindowIcon(QIcon(":/image/icon.png"));//设置窗体图标

    //创建mediaPlayer
    mediaPlayer = new QMediaPlayer(this);
    //设置mediaPlayer的QVideoWidget播放窗口
    mediaPlayer->setVideoOutput(ui->widget);

    //设置播放属性
    //1 监听信号变化函数
    connect(mediaPlayer,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(mediaStateChanged(QMediaPlayer::State)));
    //2 播放进度信号变化函数
    connect(mediaPlayer,SIGNAL(positionChanged(qint64)),this,SLOT(positionChanged(qint64)));
    //3 播放长度信号变化
    connect(mediaPlayer,SIGNAL(durationChanged(qint64)),this,SLOT(durationChanged(qint64)));
    //4 设置播放错误关联
    connect(mediaPlayer,SIGNAL(error(QMediaPlayer::Error)),this,SLOT(handleError()));
    


    //设置播放按钮
    ui->toolButton->setToolTip(QString::fromLocal8Bit("播放"));//设置鼠标点上去提示
    //ui->toolButton->setAutoRaise(true);
    ui->toolButton->setIcon(QPixmap(":/image/play.png"));
    ui->toolButton->setIconSize(QSize(75,75));

    //设置打开文件按钮
    ui->toolButton_2->setToolTip(QString::fromLocal8Bit("打开文件"));
    ui->toolButton_2->setAutoRaise(true);//设置自动获取状态
    ui->toolButton_2->setIcon(QPixmap(":/image/openfile.png"));
    ui->toolButton_2->setIconSize(QSize(75,75));

    QHBoxLayout *hlayout = new QHBoxLayout(this);
    hlayout->addWidget(ui->toolButton);
    hlayout->addWidget(ui->horizontalSlider);
    hlayout->addWidget(ui->toolButton_2);



}

void MainWindow::play()
{
    switch (mediaPlayer->state()) {
    case QMediaPlayer::PlayingState:
        mediaPlayer->pause();
        break;
    default:
        mediaPlayer->play();
        break;
    }
}

void MainWindow::on_toolButton_clicked()
{
    play();
//    ui->widget->show();
    //设置播放按钮暂停样式 测试代码时候用
//    ui->toolButton->setToolTip(QString::fromLocal8Bit("暂停"));
//    ui->toolButton->setIcon(QPixmap(":/image/pause.jpg"));
}
void MainWindow::mediaStateChanged(QMediaPlayer::State state)
{
    //mediaPlayer播放过程中动态调整播放进度
    switch (state) {
    case QMediaPlayer::PlayingState:
        ui->toolButton->setToolTip(QString::fromLocal8Bit("暂停"));
        ui->toolButton->setIcon(QPixmap(":/image/pause.jpg"));
        break;
    default:
        ui->toolButton->setToolTip(QString::fromLocal8Bit("播放"));
        ui->toolButton->setIcon(QPixmap(":/image/play.png"));
        break;
    }

}
void MainWindow::positionChanged(qint64 position)
{
    //改变播放位置
    ui->horizontalSlider->setValue(position);

}
void MainWindow::setPosition(int position)
{
    //获取mediaPlayer进度条调整位置
    mediaPlayer->setPosition(position);

}
void MainWindow::durationChanged(qint64 duration)
{
    //获取进度条的范围
    ui->horizontalSlider->setRange(0,duration);

}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    setPosition(position);
}
void MainWindow::handleError()
{
    ui->toolButton->setEnabled(false);
}

void MainWindow::on_toolButton_2_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("打开视频"),"G:/",tr("*.wmv *.avi"));
    //设置播放内容
    mediaPlayer->setMedia(QUrl::fromLocalFile(filename));
    ui->toolButton->setAutoRaise(true);
}
