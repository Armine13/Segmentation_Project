#ifndef SEGMENTIMAGE_H
#define SEGMENTIMAGE_H
#include "segmentationcore.h"

class SegmentImage: private SegmentationCore
{
public:
    SegmentImage();
    SegmentImage(String imageFile, String seedFile);
    ~SegmentImage();
    void getSegmentedImage(QVector<QImage> &segmentedQImages, QImage& contourQImage);
private:
    void getImageWithContour(const Mat& image, Mat& contourIm);
};

#endif // SEGMENTIMAGE_H
