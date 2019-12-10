#pragma once

#include "QWidget"

class ProgressWidget : public QWidget
{
	Q_OBJECT
public:
	explicit ProgressWidget(QWidget* parent = 0);

	~ProgressWidget();

signals:

public slots:
	void changeProgress(double progress);

protected:
	virtual void paintEvent(QPaintEvent* event);
	virtual void mousePressEvent(QMouseEvent* event);

protected:
	double Progress_;
};