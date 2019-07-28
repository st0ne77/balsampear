#ifndef PROGRESSWIDGET_H
#define PROGRESSWIDGET_H

#include <QWidget>
#include <QHBoxLayout>

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
    QHBoxLayout *mHBoxLayout;
    QWidget *mpProgressWidget;
    QWidget *mpControlWidget;
    QWidget *mpRect;
};

#endif // PROGRESSWIDGET_H
