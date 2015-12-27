#include "GUI/tab.h"
#include "ui_tab.h"
#include "GUI/scribblearea.h"
#include "segmentation/segmentation.h"
#include <QDebug>
#include <QFileDialog>
#include <QElapsedTimer>

#include <QGroupBox>;
Tab::Tab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab)
{
    ui->setupUi(this);
    nClasses = 2;
    scribbleImage = new ScribbleArea(this);
    fileName = QString();
    seedImgName = QString();
    segmentedQImages = QVector<QImage>();
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
//    ui->horizontalLayout->removeWidget(ui->label_image);
    ui->gridLayout_main->removeWidget(ui->label_image);

    ui->gridLayout_main->addWidget(scribbleImage,0,0);

//    QSpacerItem* hspacer = new QSpacerItem(50,50);

//    QSpacerItem* hspacer2 = new QSpacerItem(50,50);
//    ui->horizontalLayout->addSpacerItem(hspacer);
//    ui->gridLayout_main->

//    ui->horizontalLayout->addWidget(scribbleImage);
//    scribbleImage->setSizeIncrement(ui->horizontalLayout->sizeHint());

    // Update stylesheet of scribble area

    scribbleImage->setStyleSheet(QString("text-align:center; border-style: dotted; border-color: grey;border-width: 1.5px;border-radius: 3px;color: grey;"));
//    ui->gridLayout_main->setContentsMargins(1, 1, 1, 1);

//    ui->horizontalLayout->setAlignment(scribbleImage, Qt::AlignHCenter);

//    ui->horizontalLayout->addSpacerItem(hspacer2);

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

    // Run segmentation using given file names
    Segmentation seg(fileName.toStdString(), seedImgName.toStdString());

    qDebug()<<"SEGMENTATION in "<<myTimer.elapsed();




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

    //Adjust main layout to images
//    ui->gridLayout_main->setContentsMargins(1, 1, 1, 1);
}
void Tab::saveImages(const QString imagePath) const
{
    int len = imagePath.length();
    QString path = imagePath;
    segmentedQImages[0].save(QString(path.insert(len-4,"_1")));
    path = imagePath;
    segmentedQImages[1].save(QString(path.insert(len-4,"_2")));
    path = imagePath;
    contourQImage.save(QString(path.insert(len-4,"_contour")));
}
