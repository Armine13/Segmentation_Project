#include "segmentationmarkerwidget.h"
#include "markerbutton.h"
#include <QHBoxLayout>
#include <QSpinBox>
#include <QVector>
#include <QDebug>

//Initialize static vector that contains 5 colors
QVector< QColor> SegmentationMarkerWidget::colorList = QVector<QColor >()<<Qt::red<< Qt::blue<< Qt::green<< Qt::cyan<< Qt::yellow;

QColor SegmentationMarkerWidget::getColorFromIndex(int index)
{//takes an index and returns the color of the marker by that index

    int n = colorList.length();

    //If index out of range return blank QColor
    if (index < 0 || index > n)
        return QColor();

    return colorList[index];
}

SegmentationMarkerWidget::SegmentationMarkerWidget(QWidget *parent) :
    QWidget(parent)
{
    //initialize member variables
    minMarkers = 2;
    maxMarkers = 5;
    clickedColorIndex = -1;

    //default number of markers
    nMarkers = 2;

    spinBox = new QSpinBox(this);

    spinBox->setValue(nMarkers);

    spinBox->setMaximum(maxMarkers);
    spinBox->setMinimum(minMarkers);
    connect(spinBox, SIGNAL(valueChanged(int)), this, SLOT(numberOfMarkersChanged(int)));

    layout = new QHBoxLayout(this);
    layout->addWidget(spinBox);
    createMarkers();
}

SegmentationMarkerWidget::~SegmentationMarkerWidget()
{
}

bool SegmentationMarkerWidget::numberOfMarkersChanged(int value)
{//When the number of markers has changed adjust the corresponding buttons

    //check if n is in proper range
    if (value < minMarkers || value > maxMarkers) return false;

    if (value < nMarkers)//number decreased
    {//remove extra buttons
        for(int i = nMarkers - 1; i > value - 1; i--)
        {
            layout->removeWidget(colorButton[i]);
            delete colorButton[i];
            colorButton.pop_back();
        }
    }
    else if (value > nMarkers)//number increased
    {//create buttons
        for(int i = nMarkers; i < value; i++)
        {
            colorButton.append(new MarkerButton(this));
            colorButton[i]->setColor(colorList[i]);
            layout->addWidget(colorButton[i]);
            connect(colorButton[i], SIGNAL(clicked()), this, SLOT(on_button_clicked()));
        }
    }
    //update the number of markers
    nMarkers = value;

    //update the value in QSpinBox
    spinBox->setValue(nMarkers);
    return true;
}

void SegmentationMarkerWidget::on_button_clicked()
{//This is a slot for all marker buttons. It casts calling object to a MarkerButton object,
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

int SegmentationMarkerWidget::getMarkerNumber() const
{
    return nMarkers;
}
void SegmentationMarkerWidget::setMarkerNumber(int n)
{
    numberOfMarkersChanged(n);
}
