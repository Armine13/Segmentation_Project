#ifndef TAB_H
#define TAB_H

#include "scribblearea.h"
#include <QWidget>

namespace Ui {
class Tab;
}

class Tab : public QWidget
{
    Q_OBJECT

public:
    Tab(QWidget *parent = 0);
    int getNClasses() const;
    void openImage(QString);
    ~Tab();
    void setPenColor(QColor);
    QString getOpenImageName() const;
    void startSegmentation();
    bool isImageLoaded() const;
    bool isSegmented() const;
    void saveImages(const QString) const;


private:
    Ui::Tab *ui;
    int nClasses;
    ScribbleArea* scribbleImage;
    QString fileName;
    QString seedImgName;
    bool imgOpen;
    bool segmented;
    QVector<QImage> segmentedQImages;
    QImage contourQImage;
};

#endif // TAB_H
