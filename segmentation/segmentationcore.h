#ifndef SEGMENTATIONCORE_H
#define SEGMENTATIONCORE_H
#include "segmentationdata.h"

class SegmentationCore : public SegmentationData
{
public:
    SegmentationCore();
    virtual ~SegmentationCore();
    SegmentationCore(String imageFile, String seedFile);
    void minimizeEnergy();
//    void getSegmentedImage(QVector<QImage> &segmentedQImages, QImage& contourQImage);
//    void getImageWithContour(const Mat& classes, const Mat& image, Mat& contourIm);

private:
    Mat segmentationMatrix;
protected:
    const Mat& getSegmentationMatrix() const;
};

#endif // SEGMENTATIONCORE_H
