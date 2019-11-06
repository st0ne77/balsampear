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
	void ProgressChanged(double progress);

protected:
	virtual void paintEvent(QPaintEvent *event);
	virtual void mousePressEvent(QMouseEvent* event);

protected:
	double Progress_;
};

#endif // PROGRESSWIDGET_H
