#include "stdafx.h"
#include "ProgressWidget.h"

ProgressWidget::ProgressWidget(QWidget *parent) : QWidget(parent)
{
    mpContainerWidgett = new QWidget(this);//进度条区
    mpProgressBar = new QWidget(mpContainerWidgett);

    QPalette objProgressWidgetPal(mpContainerWidgett->palette());
    objProgressWidgetPal.setColor(QPalette::Background ,QColor(255, 255, 255, 30));//白色 30透明度
    mpContainerWidgett->setAutoFillBackground(true);
    mpContainerWidgett->setPalette(objProgressWidgetPal);

    QPalette objPorgressBarPal(mpProgressBar->palette());
    objPorgressBarPal.setColor(QPalette::Background ,QColor(255, 255, 0, 255));//黄色不透明
    mpProgressBar->setAutoFillBackground(true);
    mpProgressBar->setPalette(objPorgressBarPal);
}

ProgressWidget::~ProgressWidget()
{

}

void ProgressWidget::paintEvent(QPaintEvent *event)
{
    mpContainerWidgett->resize(this->width(), this->height());
    int iPorgressWidgetWidth = mpContainerWidgett->width();
    int iProgressWidgetHeight = mpContainerWidgett->height();
    mpProgressBar->resize(iPorgressWidgetWidth*96/100, iProgressWidgetHeight/5);
    mpProgressBar->move(iPorgressWidgetWidth*2/100, iProgressWidgetHeight / 2 - mpProgressBar->height() / 2);
}
