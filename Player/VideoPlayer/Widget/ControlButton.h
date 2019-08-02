#ifndef CONTROLBUTTON_H
#define CONTROLBUTTON_H
#include <QPushButton>

class ControlButton: public QPushButton
{
    Q_OBJECT
public:
    explicit ControlButton(QWidget *parent = 0);
    ~ControlButton();
};

#endif // CONTROLBUTTON_H
