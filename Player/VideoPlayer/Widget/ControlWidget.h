#ifndef CONTROLWIDGET_H
#define CONTROLWIDGET_H

#include <QWidget>

class QHBoxLayout;
class ControlButton;
class PlayerTimer;
class ControlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ControlWidget(QWidget *parent, PlayerTimer *playTimer);

signals:

public slots:
	void changePlayStatus();

private:
    QHBoxLayout *mHBoxLayout;//横向布局
    ControlButton *mpControlButton;
	PlayerTimer* mpPlayTimer;
	bool mbPlying;
};

#endif // CONTROLWIDGET_H
