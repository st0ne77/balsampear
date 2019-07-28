#include "playwidget.h"
#include <QPainter>
#include "progresswidget.h"

PlayWidget::PlayWidget(QWidget *parent) : QWidget(parent)
{
    mVLayout = new QVBoxLayout(this);
    mVLayout->setContentsMargins(0, 0, 0, 0);
    mEmptyWidget = new QWidget();
    mProgressWidget = new ProgressWidget();

    QPalette pal(mProgressWidget->palette());
    pal.setColor(QPalette::Background , QColor(255,255,255 , 30));
    mProgressWidget->setAutoFillBackground(true);
    mProgressWidget->setPalette(pal);

    mVLayout->addWidget(mEmptyWidget , 15);//播放区
    mVLayout->addWidget(mProgressWidget , 3);//进度条
    mVLayout->addWidget(new QWidget, 2);//占位
}

PlayWidget::~PlayWidget()
{

}


void PlayWidget::paintEvent(QPaintEvent *event)
{
    //return;
    QPainter painter(this);
    painter.setBrush(Qt::black);
    painter.drawRect(0, 0, this->width(), this->height()); //先画成黑色

    if (mImage.size().width() <= 0)
        return;

    ///将图像按比例缩放成和窗口一样大小
    QImage img = mImage.scaled(this->size(),Qt::KeepAspectRatio);

    int x = this->width() - img.width();
    int y = this->height() - img.height();

    x /= 2;
    y /= 2;

    painter.drawImage(QPoint(x,y),img); //画出图像
}

void PlayWidget::slotGetOneFrame(QImage img)
{
    mImage = img;
    update();
}

