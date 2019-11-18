#pragma once
#include <QWidget>
#include "ProgressWidget.h"
#include "PlayButton.h"


class ControlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ControlWidget(QWidget *parent);

	inline void setPlaying(bool _val) { playBtn.setPlaying(_val); }
signals:
	void checkChangePlayBtn();

public slots:
	inline void progressChanged(double _val) { progress_.changeProgress(_val); }

protected:
	virtual void paintEvent(QPaintEvent* event);

private:
	ProgressWidget progress_;
	PlayButton playBtn;
};

