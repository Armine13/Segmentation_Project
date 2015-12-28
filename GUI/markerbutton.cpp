#include "markerbutton.h"
#include <QToolButton>

MarkerButton::MarkerButton(QWidget *parent) :
    QToolButton(parent)
{
    //Initialize button parameters
    buttonIndex = -1;
    setAutoRaise(true);
    color = QColor();
}
MarkerButton::MarkerButton(int index, QWidget *parent) :
    QToolButton(parent)
{
    setIndex(index);//Index of button in order it is displayed
    setAutoRaise(true);
}
void MarkerButton::setIndex(int index)
{
    if (index >= 0 && index < 100)
        buttonIndex = index;
}
int MarkerButton::getIndex() const
{
    return buttonIndex;
}
void MarkerButton::setColor(const QColor clr)
{
    color = clr;
    setStyleSheet(QString("background-color:%1").arg(color.name()));
}
const QColor& MarkerButton::getColor() const
{
    return color;
}
