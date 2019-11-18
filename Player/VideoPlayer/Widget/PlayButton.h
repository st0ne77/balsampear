#ifndef CONTROLBUTTON_H
#define CONTROLBUTTON_H
#include <QWidget>

class PlayButton: public QWidget
{
    Q_OBJECT
public:
    explicit PlayButton(QWidget *parent = 0);
	~PlayButton() {}

	inline void setPlaying(bool val) { playing = val; update(); }
protected:
	virtual void paintEvent(QPaintEvent* event);
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void leaveEvent(QEvent* event);
	virtual void enterEvent(QEvent* event);
private:
	QPainterPath calcRoundTriangle(int x, int y, int side);
	QPainterPath calcPauseArea(int x, int y, int side);
private:
	QPainterPath playArea;
	bool enter;
	bool playing;
};

#endif // CONTROLBUTTON_H
