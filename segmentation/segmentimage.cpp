#include "segmentimage.h"
#include "segmentationcore.h"

SegmentImage::SegmentImage()
{
}
SegmentImage::~SegmentImage()
{
}
SegmentImage::SegmentImage(String imageFile, String seedFile)
    :SegmentationCore(imageFile, seedFile)
{
}
void SegmentImage::getSegmentedImage(QVector<QImage> &segmentedQImages, QImage& contourQImage)
{
    //Returns segmented and contour images using references

    int rows = getImgRows();
    int cols = getImgCols();
    int nSeeds = getSeedNumber();

    Mat segmentationMatrix = getSegmentationMatrix();
    QVector<Mat > segmentedImages;// This will contain two segmented images: background and foreground



    //initialize both segmented images by setting background to be white
    for(int i = 0; i < nSeeds; i++)
    {
        segmentedImages.append(Mat( getImgSize(), getImgType()));
        segmentedImages[i].setTo(cv::Scalar(255, 255, 255));
    }

    //If wrong number of seeds provided, return blank images
    if(nSeeds != 2)
    {
        segmentedQImages.resize(2);
        segmentedQImages[0] = QImage(rows, cols, QImage::Format_RGB16);
        segmentedQImages[0].fill(Qt::white);
        segmentedQImages[1] = QImage(rows, cols, QImage::Format_RGB16);
        segmentedQImages[1].fill(Qt::white);
        contourQImage = QImage(rows, cols, QImage::Format_RGB16);
        contourQImage.fill(Qt::white);
        return;
    }

    for(int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++ )
            {
                // seed value #1 is 1 and #2 is 2
                // So using 1.5 as threshold we separate foreground from background
                if (segmentationMatrix.at<double>(i, j) >= 1.5)
                    segmentedImages[0].at<Vec3b>(i, j) = getIntensity(i,j);
                else
                    segmentedImages[1].at<Vec3b>(i,j) = getIntensity(i,j);
            }
    //Find contours and return the image with drawn contours
    Mat contourIm;
    //Compute the contour image
    getImageWithContour(getOrigImage(), contourIm);//contour image returned via reference

    //Save two SegmentationData images(one for background, one for foreground) into a QVector segmentedQImages
     segmentedQImages.clear();
    for(int i = 0; i < nSeeds; i++)
        segmentedQImages.push_back(cvMatToQImage(segmentedImages[i]));//convert to QImage and save in a vector

    //Convert the contour image into a QImage
    contourQImage = cvMatToQImage(contourIm);

    // All three images are returned through a reference
}
void SegmentImage::getImageWithContour( const Mat& image, Mat& contourIm)
{
    //    Find countours by first using Canny edge detection, then cv::findContours

        int lowThreshold = 1;
        int ratio = 3;
        int kernel_size = 3;

        //Edge Detection
        Mat edgesImage = Mat( image.size(), image.type());
        edgesImage.setTo(cv::Scalar(255, 255, 255));
        //
        Mat classes = getSegmentationMatrix(); //This matrix contains the results of segmentation
        classes.convertTo(classes, CV_8U);//conversion required for Canny
        //Canny Edge detection
        Canny(classes, edgesImage, lowThreshold, lowThreshold*ratio, kernel_size );

        //Finding contours
        vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;
         findContours( edgesImage, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

         contourIm = image;

         // Draw contours
         Scalar color = Scalar( 0, 0,255 ); //red
         for( int i = 0; i< contours.size(); i++ )
              drawContours( contourIm, contours, i, color, 2, 8, hierarchy, 0, Point() );

         //http://docs.opencv.org/2.4/doc/tutorials/imgproc/shapedescriptors/find_contours/find_contours.html
}

