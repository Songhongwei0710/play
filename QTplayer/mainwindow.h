#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *mediaPlayer;
    void Init();

private slots:
    void play();//播放
    void mediaStateChanged(QMediaPlayer::State state);//播放状态
    void positionChanged(qint64 position);//改变播放位置
    void setPosition(int position);//获取播放位置
    void durationChanged(qint64 duration);//播放长度
    void handleError();//播放异常的抛出

    void on_toolButton_clicked();
    void on_horizontalSlider_sliderMoved(int position);
    void on_toolButton_2_clicked();
};

#endif // MAINWINDOW_H
