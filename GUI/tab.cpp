#include "GUI/tab.h"
#include "ui_tab.h"
#include "GUI/scribblearea.h"
#include "segmentation/segmentation.h"
#include <QDebug>
#include <QFileDialog>
#include <QElapsedTimer>

Tab::Tab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab)
{
    ui->setupUi(this);
    nClasses = 2;
    scribbleImage = new ScribbleArea(this);
    fileName = QString();
    seedImgName = QString();
    imgOpen = false;
}
Tab::~Tab()
{
    delete ui;

    //remove seed image
    if (!seedImgName.isEmpty())
        QFile::remove(seedImgName);
}

int Tab::getNClasses() const
{
    return nClasses;
}
void Tab::setNClasses(int n)
{
    if (n < 2 || n > 5) return;
    else nClasses = n;
}
void Tab::openImage(QString fName)
{
    fileName = fName;
    scribbleImage->openImage(fileName);
    imgOpen = true;

    qDebug()<< fileName;
    //make the label invisible and instead display the image
    if (ui->label_image->isVisible())  ui->label_image->setVisible(false);
    ui->horizontalLayout->addWidget(scribbleImage);

    // create the seed image, with name = <filename> + "seed.bmp"
    seedImgName = fileName;
    seedImgName.chop(4);
    seedImgName += "seed.bmp";

    scribbleImage->createSeedImage(seedImgName);
}
bool Tab::isImageLoaded() const
{
    return imgOpen;
}
void Tab::setPenColor(QColor clr)
{//propagates the new pen color to scribble widget for painting

    scribbleImage->setPenColor(clr);
}
QString Tab::getOpenImageName() const
{
    return fileName;
}

void Tab::startSegmentation()
{

    //Save the seed image into a file
    qDebug()<<seedImgName;
    scribbleImage->saveSeedImage(seedImgName);

    QElapsedTimer myTimer;
    myTimer.start();
    Segmentation seg(fileName.toStdString(), seedImgName.toStdString());
    qDebug()<<"SEGMENTATION in "<<myTimer.elapsed();

    QVector<QImage> segmentedQImages = QVector<QImage>();
    QImage contourQImage;
    seg.getSegmentedImage(segmentedQImages, contourQImage);
    ui->label_seg->setPixmap(QPixmap::fromImage(contourQImage));
}
