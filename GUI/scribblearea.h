#ifndef SCRIBBLEAREA_H
#define SCRIBBLEAREA_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>

// Copied and modified from http://doc.qt.io/qt-5/qtwidgets-widgets-scribble-example.html

class ScribbleArea : public QWidget
{
    Q_OBJECT

public:
    ScribbleArea(QWidget *parent = 0);
    ~ScribbleArea();
    void openImage(const QString &fileName);
    void createSeedImage(const QString &fileName);
    bool saveSeedImage(QString fileName);

    void setPenColor(const QColor &newColor);

    const QImage& getSelection();

private:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

    void drawLineTo(const QPoint &endPoint);

    bool scribbling;
    bool enabled;
    int myPenWidth;
    QColor myPenColor;
    QImage image;
    QImage selectionImage;
    QPoint lastPoint;
};

#endif
