#ifndef PROGRESSWIDGET_H
#define PROGRESSWIDGET_H
#include <QWidget>

class ProgressWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ProgressWidget(QWidget *parent = 0);

    ~ProgressWidget();

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *event);

protected:
    QWidget *mpContainerWidgett;
    QWidget *mpProgressBar;
};

#endif // PROGRESSWIDGET_H
