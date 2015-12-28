#ifndef SEGMENTATIONMARKERWIDGET_H
#define SEGMENTATIONMARKERWIDGET_H

#include "markerbutton.h"
#include <QWidget>
#include <QColor>
#include <QSpinBox>
#include <QHBoxLayout>


class SegmentationMarkerWidget : public QWidget
{
    Q_OBJECT

public:
    SegmentationMarkerWidget(QWidget *parent = 0);
    ~SegmentationMarkerWidget();
    int getMarkerNumber() const;
    void setMarkerNumber(int n);
    QColor getColorFromIndex(int index);

private slots:
    void on_button_clicked();
signals:
    void colorSelected(QColor);

private:

    int nMarkers;
    int clickedColorIndex;
    QVector< QColor> colorList;

    void createMarkers();

    QHBoxLayout* layout;
    QVector <MarkerButton* > colorButton;
};

#endif // SEGMENTATIONMARKERWIDGET_H
