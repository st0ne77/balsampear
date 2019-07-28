#include "progresswidget.h"
#include <QProgressBar>

ProgressWidget::ProgressWidget(QWidget *parent) : QWidget(parent)
{
    mHBoxLayout = new QHBoxLayout(this);
    mHBoxLayout->setContentsMargins(0, 0, 0, 0);//四个方向全部不留空白区

    mHBoxLayout->setSpacing(0);



    mpProgressWidget = new QWidget();//进度条区
    mpControlWidget = new QWidget();


    //QProgressBar *pProgressBar = new QProgressBar(pProgressWidget);//进度条
    //pProgressBar->setRange(0, );
    //pProgressBar->setMinimumWidth(pProgressWidget->width());
    //pProgressBar->setMaximumWidth(pProgressWidget->width());
    //pProgressBar->move(0, pProgressWidget->height() / 2 - pProgressBar->height() / 2);


    mHBoxLayout->addWidget(mpProgressWidget , 17);
    mHBoxLayout->addWidget(mpControlWidget , 3);

    mpRect = new QWidget(mpProgressWidget);
}

ProgressWidget::~ProgressWidget()
{

}

void ProgressWidget::paintEvent(QPaintEvent *event)
{
    QPalette pal(mpControlWidget->palette());
    pal.setColor(QPalette::Background , QColor(0xff, 0, 0));
    mpControlWidget->setAutoFillBackground(true);
    mpControlWidget->setPalette(pal);

    QPalette pal1(mpProgressWidget->palette());
    pal1.setColor(QPalette::Background ,QColor(0, 0, 0, 0));
    mpProgressWidget->setAutoFillBackground(true);
    mpProgressWidget->setPalette(pal1);

    mpRect->resize(mpProgressWidget->width() , mpProgressWidget->height() / 5);

    QPalette pal2(mpRect->palette());
    pal2.setColor(QPalette::Background ,QColor(0xff , 0x00, 0, 0x30));
    mpRect->setAutoFillBackground(true);
    mpRect->setPalette(pal2);

    mpRect->move(0, mpProgressWidget->height() / 2 - mpRect->height() / 2);
}
