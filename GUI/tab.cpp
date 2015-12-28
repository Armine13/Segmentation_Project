#include "GUI/tab.h"
#include "ui_tab.h"
#include "GUI/scribblearea.h"
#include "segmentation/segmentimage.h"
#include <QDebug>
#include <QFileDialog>
#include <QElapsedTimer>


Tab::Tab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab)
{
    ui->setupUi(this);
    //Number of classes for this segmentation is two
    nClasses = 2;

    //Initialization of variables
    fileName = QString();
    seedImgName = QString();
    segmentedQImages = QVector<QImage>();

    //Initializing flags
    imgOpen = false;
    segmented = false;
}

Tab::~Tab()
{
    delete ui;

    //remove seed image
    if (!seedImgName.isEmpty())
        QFile::remove(seedImgName);
}

int Tab::getNClasses() const
{//returns number of classes. In this implementation it's always 2

    return nClasses;
}

void Tab::openImage(QString fName)
{//Open and display an image using its name and path

    //If an image is already open, remove the image first
    if (imgOpen)
    {
        ui->gridLayout_main->removeWidget(scribbleImage);
        scribbleImage->deleteLater();
    }

    fileName = fName;
    //Create a ScribbleArea with the opened image
    //it will allow to draw on the chosen image
    scribbleImage = new ScribbleArea(ui->label_image);//scribbleImage is displayed in a label
    //so the label is set to be parent

    //open image in scribble area
    scribbleImage->openImage(fileName);
    imgOpen = true;
    ui->label_image->setText("");

    //insert the scribble area into the layout
    ui->gridLayout_main->addWidget(scribbleImage,0,0);


    //align image in center of label
    ui->gridLayout_main->setAlignment(scribbleImage, Qt::AlignCenter);


    // create the seed image, with name = <filename> + "seed.bmp"
    seedImgName = fileName;
    seedImgName.chop(4);
    seedImgName += "seed.bmp";
    scribbleImage->createSeedImage(seedImgName);
}

bool Tab::isImageLoaded() const
{//returns true if an image has been opened

    return imgOpen;
}

void Tab::setPenColor(QColor clr)
{//propagates the new marker color to scribble widget for painting

    scribbleImage->setPenColor(clr);
}
QString Tab::getOpenImageName() const
{
    return fileName;
}

void Tab::startSegmentation()
{   // This function creates an object of SegmentImage, which performs segmentation
    //and returns segmented images. These images are then displayed in labels of a Tab object

    //Save the seed image into a file
    scribbleImage->saveSeedImage(seedImgName);

    QElapsedTimer myTimer;
    myTimer.start();

    // Initialize segmentation using given file names
    // and perform segmentation
    SegmentImage seg(fileName.toStdString(), seedImgName.toStdString());
    contourQImage = QImage();


    qDebug()<<"Segmentation in "<<myTimer.elapsed()<<" ms";

    // Retrieve segmented images by reference
    seg.getSegmentedImage(segmentedQImages, contourQImage);

    // Display segmented images in labels
    ui->label_seg_1->setPixmap(QPixmap::fromImage(segmentedQImages[0]));
    ui->label_seg->setPixmap(QPixmap::fromImage(segmentedQImages[1]));
    ui->label_cont->setPixmap(QPixmap::fromImage(contourQImage));

    // Adjust sizes of labels to contained images
    ui->label_seg_1->setMinimumSize(segmentedQImages[0].size());
    ui->label_seg->setMinimumSize(segmentedQImages[1].size());
    ui->label_cont->setMinimumSize(contourQImage.size());

    //Enable flag
    segmented = true;
}
void Tab::saveImages(const QString imagePath) const
{
    //This function is called when saveAs action is triggered.
    //It saved images with appropriate names

    int len = imagePath.length();
    QString path = imagePath;//Original file name
    //<filename>_1.*
    segmentedQImages[0].save(QString(path.insert(len-4,"_1")));
    path = imagePath;
    //<filename>_2.*
    segmentedQImages[1].save(QString(path.insert(len-4,"_2")));
    path = imagePath;
    //<filename>_contour.*
    contourQImage.save(QString(path.insert(len-4,"_contour")));
}
bool Tab::isSegmented() const
{// Necessary while saving images,
    // to check if segmentation has been performed and completed

    return segmented;
}
