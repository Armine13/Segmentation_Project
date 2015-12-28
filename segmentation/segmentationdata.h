#ifndef SEGMENTATIONDATA_H
#define SEGMENTATIONDATA_H
#include <QImage>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <Eigen/Sparse>


using namespace std;
using namespace cv;

QImage  cvMatToQImage( const Mat &inMat );

class SegmentationData
{
public:
    SegmentationData();
    SegmentationData(String, String);
    virtual ~SegmentationData();

//    void getSegmentedImage(QVector<QImage>&, QImage&);
    double getWeights(int, int) const;
    int getImgRows() const;
    int getImgCols() const;
    Vec3b getIntensity(int, int) const;
    int getSeedFromMatrix(int, int) const;
    int getSeedFromVector(int) const;

    int getSeedNumber() const;
//    void getImageWithContour(const Mat& classes, const Mat& image, Mat& contourImage);
    Size getImgSize() const;
    int getImgType() const;
    const Mat &getOrigImage() const;

private:
    bool computeWeights();
    void readSeeds(const Mat& seedImage);
    bool minimizeEnergy();
    //QImage cvMatToQImage( const Mat & );

    int imgRows;
    int imgCols;
    int nSeeds;
    Mat originalImage;
    Eigen::Matrix<char, Eigen::Dynamic, Eigen::Dynamic> seed;

//    Mat SegmentationDataImage;
//    Mat SegmentationDataMatrix;
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> w; //weights
    Eigen::SparseMatrix<double> W_mat; //sparse matrix of weights
protected:
    const Eigen::SparseMatrix<double>& getWeightsMatrix() const;
};

#endif // SegmentationData_H
