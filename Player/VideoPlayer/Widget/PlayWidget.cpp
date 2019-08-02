#include "stdafx.h"
#include "PlayWidget.h"
#include "ProgressWidget.h"
#include "ControlWidget.h"

using namespace std;
PlayWidget::PlayWidget(QWidget* parent, const string& strStreamFile) : QWidget(parent)
{
	mVLayout = new QVBoxLayout(this);//纵向布局
	mVLayout->setContentsMargins(0, 0, 0, 0);//布局的四周外边距
	mEmptyWidget = new QWidget(this);
	mProgressWidget = new ProgressWidget(this);
	mpControlWidget = new ControlWidget(this);

    mVLayout->addWidget(mEmptyWidget , 16);//透明占位区
	mVLayout->addWidget(mProgressWidget, 2);//进度条区
	mVLayout->addWidget(mpControlWidget, 2);//控制区

	update();
}

PlayWidget::~PlayWidget()
{
	delete mVLayout;
	delete mEmptyWidget;
}

void PlayWidget::Draw(const QImage& img)
{
	mImage = img;
	this->update();
}

// 绘图
void PlayWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setBrush(Qt::black);
    painter.drawRect(0, 0, this->width(), this->height()); //先画成黑色

    if (mImage.size().width() <= 0)
    {
        return;
    }

    ///将图像按比例缩放成和窗口一样大小
    QImage img = mImage.scaled(this->size(),Qt::KeepAspectRatio);

    int x = this->width() - img.width();
    int y = this->height() - img.height();

    x /= 2;
    y /= 2;

    painter.drawImage(QPoint(x,y),img); //画出图像
}

