#include "segmentationmarkerwidget.h"
#include "markerbutton.h"
#include <QHBoxLayout>
#include <QSpinBox>
#include <QVector>
#include <QDebug>



SegmentationMarkerWidget::SegmentationMarkerWidget(QWidget *parent) :
    QWidget(parent)
{
    //Initialize vector that contains 2 colors used for the buttons in this widget
    colorList = QVector<QColor >()<<Qt::red<< Qt::blue;

    //initialize member variables
    clickedColorIndex = -1;

    //default number of markers
    nMarkers = 2;

    layout = new QHBoxLayout(this);

    //Create marker buttons
    createMarkers();
}
QColor SegmentationMarkerWidget::getColorFromIndex(int index)
{//takes an index and returns the color of the marker by that index

    int n = colorList.size();

    //If index out of range return blank QColor
    if (index < 0 || index > n)
        return QColor();

    return colorList[index];
}

SegmentationMarkerWidget::~SegmentationMarkerWidget()
{
}

void SegmentationMarkerWidget::on_button_clicked()
{
    //This is a slot for all marker buttons. It casts calling object to a MarkerButton object,
    //then reads the index of the object. The index is later used to find the selected color.

    QObject* clickedObject = sender();
    MarkerButton* clickedButton = qobject_cast<MarkerButton*>(clickedObject);

    //emit a signal with the color of the clicked button/ new pen color
    emit colorSelected(clickedButton->getColor());
}
void SegmentationMarkerWidget::createMarkers()
{//Creates buttons to represent each marker color
    for(int i = 0; i < nMarkers; i++)
    {
        colorButton.append(new MarkerButton(this));
        colorButton[i]->setColor(colorList[i]);
        layout->addWidget(colorButton[i]);
        connect(colorButton[i], SIGNAL(clicked()), this, SLOT(on_button_clicked()));
        layout->addWidget(colorButton[i]);
    }
}

