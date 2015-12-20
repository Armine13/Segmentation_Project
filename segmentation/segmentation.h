#ifndef SEGMENTATION_H
#define SEGMENTATION_H
//#define EIGEN_YES_I_KNOW_SPARSE_MODULE_IS_NOT_STABLE_YET
#include <QImage>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <Eigen/Dense>
//#include <eigen-eigen-b30b87236a1b/Eigen>
#include <Eigen/Sparse>


using namespace std;
using namespace cv;

QImage  cvMatToQImage( const Mat &inMat );

class Segmentation
{
public:
    Segmentation();
    Segmentation(String, String);
    ~Segmentation();

    void getSegmentedImage(QVector<QImage>&, QImage&);
    double getWeights(int, int) const;
    int getImgRows() const;
    int getImgCols() const;
    Vec3b getIntensity(int, int) const;
    int getSeedFromMatrix(int, int) const;
    int getSeedFromVector(int) const;

    int getSeedNumber() const;
    void getImageWithContour(const Mat& classes, const Mat& image, Mat& contourImage);

private:
    bool computeWeights();
    bool readSeeds(const Mat& seedImage);
    bool minimizeEnergy();
    //QImage cvMatToQImage( const Mat & );

    int imgRows;
    int imgCols;
    int nSeeds;
    Mat originalImage;
    Eigen::Matrix<char, Eigen::Dynamic, Eigen::Dynamic> seed;

//    Mat segmentationImage;
    Mat segmentationMatrix;
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> w; //weights
    Eigen::SparseMatrix<double> W_mat; //sparse matrix of weights

};

#endif // SEGMENTATION_H
