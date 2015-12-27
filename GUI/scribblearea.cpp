// Scribble QT example
//#include <QtWidgets>
#include <QImage>
#include <QString>
#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include "scribblearea.h"

//! [0]
ScribbleArea::ScribbleArea(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    scribbling = false;
    myPenWidth = 10;
    myPenColor = Qt::blue;
    enabled = false;
}
ScribbleArea::~ScribbleArea()
{

    //    saveImage("seed", &selectionImage);
}
void ScribbleArea::openImage(const QString &fileName)
{
    QImage loadedImage;

    // exit if image not loaded properly
    if (!loadedImage.load(fileName))
        return;

    // convert to rgb just in case
    image = loadedImage.convertToFormat(QImage::Format_RGB32);

    //adjust widget size to the image
    this->setMinimumSize(image.size());
    update();
}

void ScribbleArea::createSeedImage(const QString &fileName)
{
    //create empty image with the same size as the opened image
    //    selectionImage = QImage((&(image.size())) ;
    selectionImage = QImage(image.size(), QImage::Format_RGB32);
    qDebug()<<selectionImage.size();
    //set background color to white
    selectionImage.fill(qRgb(255, 255, 255));
}

void ScribbleArea::setPenColor(const QColor &newColor)
{
    enabled = true;
    myPenColor = newColor;
}

void ScribbleArea::mousePressEvent(QMouseEvent *event)
{
    if (!enabled) return;
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        scribbling = true;
    }
}

void ScribbleArea::mouseMoveEvent(QMouseEvent *event)
{
    if (!enabled) return;
    if ((event->buttons() & Qt::LeftButton) && scribbling)
        drawLineTo(event->pos());
}

void ScribbleArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (!enabled) return;
    if (event->button() == Qt::LeftButton && scribbling) {
        drawLineTo(event->pos());
        scribbling = false;
    }
}

void ScribbleArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);

    //http://stackoverflow.com/questions/7276330/qt-stylesheet-for-custom-widget
    // This enables styling of the widget
    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void ScribbleArea::drawLineTo(const QPoint &endPoint)
{
    if (!enabled) return;
    QPainter painter(&image);
    QPainter painter2(&selectionImage);

    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawLine(lastPoint, endPoint);

    painter2.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                         Qt::RoundJoin));
    painter2.drawLine(lastPoint, endPoint);

    int rad = (myPenWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized()
           .adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}

bool ScribbleArea::saveSeedImage(QString fName, const char *fileFormat)
{
    //TODO: this function must be able to save multiple formats

    //The seed image will be saved into the resources folder in the project directory
    if (selectionImage.save(fName)) {
        return true;
    } else {
        return false;
    }
}
const QImage& ScribbleArea::getSelection()
{
    return selectionImage;
}
