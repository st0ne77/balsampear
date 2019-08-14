#ifndef CONTROLBUTTON_H
#define CONTROLBUTTON_H
#include <QPushButton>

class ControlButton: public QPushButton
{
    Q_OBJECT
public:
    explicit ControlButton(QWidget *parent = 0);
    ~ControlButton();

	void setPlaying(bool _val);

protected:
	virtual void enterEvent(QEvent* event);
	virtual void leaveEvent(QEvent* event);
	bool mbPlaying;

};

#endif // CONTROLBUTTON_H
