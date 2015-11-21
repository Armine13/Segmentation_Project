#ifndef MARKERBUTTON_H
#define MARKERBUTTON_H

#include <QToolButton>

class MarkerButton : public QToolButton
{
    Q_OBJECT
public:
    MarkerButton(QWidget *parent = 0);
    MarkerButton(int index, QWidget *parent = 0);
    void setIndex(int index);
    int getIndex() const;

    void setColor(const QColor);
    const QColor& getColor() const;

private:
    int buttonIndex;
    QColor color;

};

#endif // MARKERBUTTON_H
