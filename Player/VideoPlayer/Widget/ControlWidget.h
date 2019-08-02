#ifndef CONTROLWIDGET_H
#define CONTROLWIDGET_H

#include <QWidget>

class QHBoxLayout;
class ControlButton;
class ControlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ControlWidget(QWidget *parent = 0);

signals:

public slots:

private:
    QHBoxLayout *mHBoxLayout;//横向布局
    ControlButton *mpControlButton;
};

#endif // CONTROLWIDGET_H
