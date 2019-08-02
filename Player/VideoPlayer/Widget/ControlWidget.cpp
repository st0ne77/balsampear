#include "stdafx.h"
#include "ControlWidget.h"
#include "ControlButton.h"
#include <QHBoxLayout>

ControlWidget::ControlWidget(QWidget *parent) : QWidget(parent)
{
    mHBoxLayout = new QHBoxLayout(this);
    mpControlButton = new ControlButton(this);

    mpControlButton->setText("play");

    mHBoxLayout->addWidget(mpControlButton, 2);
    mHBoxLayout->addWidget(new QWidget(), 18);


    QPalette objControlBtnPal(mpControlButton->palette());
    objControlBtnPal.setColor(QPalette::Background, QColor(255, 0, 0, 255));//红色 显眼一点，先用着
    mpControlButton->setAutoFillBackground(true);
    mpControlButton->setPalette(objControlBtnPal);

}



