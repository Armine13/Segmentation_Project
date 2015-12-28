#include "Segmentationdata.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>
#include <QDebug>
#include <QElapsedTimer>
using namespace std;

SegmentationData::SegmentationData()
{}
SegmentationData::SegmentationData(String imageFile, String seedFile)
{
    //Read the image and its seed image
    originalImage = imread(imageFile);
    Mat seedImage = imread(seedFile);

    assert(!originalImage.empty());
    assert(!seedImage.empty());

    //find dimensions of the image
    imgRows = originalImage.rows;
    imgCols = originalImage.cols;

    computeWeights();

    //Extract seeds
    readSeeds(seedImage);

}
SegmentationData::~SegmentationData()
{}
int SegmentationData::getImgRows() const
{
    return originalImage.rows;
}
int SegmentationData::getImgCols() const
{
    return originalImage.cols;
}
Size SegmentationData::getImgSize() const
{//Returns the size of the image in cv::Size
    return originalImage.size();
}
int SegmentationData::getImgType() const
{
    return originalImage.type();
}
const Mat& SegmentationData::getOrigImage() const
{
    return originalImage;
}

bool SegmentationData::computeWeights()
{
    //Compute the weights and save into matrices w and W_mat.
    //w is a row*col x 4 matrix, each row containing weights for 4 neighbors
    //W_mat is a sparse matrix of size row*col x row*col.

    float beta = 0.7;
    //double sigma = 0;
    int rows = getImgRows();
    int cols = getImgCols();
    int size = rows * cols;

    //weights of edges
    w = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>::Zero(size, 4);
    W_mat = Eigen::SparseMatrix<double>(size,size);

    //Reserve space for weights matrix
    W_mat.reserve(Eigen::VectorXi::Constant(size,4));//sparse matrix of weights

    int index = 0;

    int nrm = 0; // norm
    float epsilon = 0.000001;

    for (int y = 0; y < rows; y++)
        for (int x = 0; x < cols; x++)
        {
            //up (neighbor above)
            if (y - 1 >= 0 )
            {
                nrm = norm(getIntensity(y,x), getIntensity(y - 1,x),NORM_INF);

                w(index, 0) = exp( - beta * pow(nrm,2) / (nrm+epsilon)) + epsilon;

                W_mat.coeffRef(index, (y - 1) * cols + x) = w(index, 0);
//                W_mat uses indices of two neighboring pixels to save the weight
            }

            //right
            if (x + 1 < cols)
            {
                nrm = norm(getIntensity(y,x), getIntensity(y,x + 1),NORM_INF);

                w(index, 1) = exp( - beta * pow(nrm,2) / (nrm+epsilon)) + epsilon;

                W_mat.coeffRef(index, y * cols + x + 1) = w(index, 1);
            }

            //down
            if (y + 1 < rows)
            {
                nrm = norm(getIntensity(y,x), getIntensity(y + 1,x),NORM_INF);
                w(index, 2) = exp( - beta * pow(nrm,2) / (nrm+epsilon)) + epsilon;

                W_mat.coeffRef(index, (y + 1) * cols + x) = w(index, 2);

            }

            //left
            if (x - 1 >= 0)
            {
                nrm = norm(getIntensity(y,x), getIntensity(y,x - 1),NORM_INF);
                w(index, 3) = exp( - beta * pow(nrm,2) / (nrm+epsilon)) + epsilon;

                W_mat.coeffRef(index, y * cols + x - 1) = w(index, 3);
            }
            index++;//value of the current row in matrix w
        }
    return true;
}
Vec3b SegmentationData::getIntensity(int y, int x) const
{ //Returns intensity value at (y,x)
    assert (y >= 0 && y < getImgRows() && x >= 0 && x < getImgCols());
    return originalImage.at<Vec3b>(y, x);
}
double SegmentationData::getWeights(int i, int j) const
{
    //Returns the weight from matrix w
    // i = pixel indx,j = neighbor(0-3)

    assert (j < 4 && j >= 0 && i < getImgCols()*getImgRows() && i >= 0);
    return w(i, j);
}
const Eigen::SparseMatrix<double>& SegmentationData::getWeightsMatrix() const
{
    return W_mat;
}

void SegmentationData::readSeeds(const Mat &seedImage)
{
    int rows = getImgRows();
    int cols = getImgCols();
    vector<Vec3b >::iterator idxIter;
    int idx;
    Vec3b white = Vec3b(255, 255, 255);
    Vec3b color;
    vector< Vec3b > s;//seed colors will be saved into this vector

    //assert seed image has the same dimentions as the original image
    assert(seedImage.rows == rows && seedImage.cols == cols);

    //initialize seed with zeros
    seed = Eigen::Matrix<char, Eigen::Dynamic, Eigen::Dynamic>::Zero(rows, cols);

    for(int y = 0; y < rows; y++)
        for(int x = 0; x < cols; x++)
        {
            color = seedImage.at<Vec3b>(y, x);
            if (! (color == white) )
            {
                idxIter = find(s.begin(), s.end(), color); //find color in saved seeds
                idx = idxIter - s.begin();
                if ( idx == s.size())//if seed not in vector s, add
                    s.push_back(color);
                seed(y, x) = idx + 1;//save index in seed matrix (+1 to avoid 0)..?
            }
        }
    nSeeds = s.size(); // number of seed classes
}

int SegmentationData::getSeedFromMatrix(int y, int x) const
{
    // Returns the seed value read from image
    // (x,y) is a point in the seed image

    assert (y >= 0 && y < getImgRows()  && x >= 0 && x < getImgCols());
    return int(seed(y, x));
}

int SegmentationData::getSeedFromVector(int i) const
{ // Returns i-th value in the seed matrix read from file

    assert (i >= 0 && i < getImgRows()* getImgCols());
    //converts i into row and column
    return int(seed(i / getImgCols(), i % getImgCols()));
}

int SegmentationData::getSeedNumber() const//returns the number of seed classes
{
    return nSeeds;
}

QImage  cvMatToQImage( const Mat &inMat )
//independent function that converts Mat into QImage
//http://asmaloney.com/2013/11/code/converting-between-cvmat-and-qimage-or-qpixmap/
{
    switch ( inMat.type() )
    {
    // 8-bit, 4 channel
    case CV_8UC4:
    {
        QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB32 );

        return image;
    }

        // 8-bit, 3 channel
    case CV_8UC3:
    {
        QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB888 );

        return image.rgbSwapped();
    }

        // 8-bit, 1 channel
    case CV_8UC1:
    {
        static QVector<QRgb>  sColorTable;

        // only create our color table once
        if ( sColorTable.isEmpty() )
        {
            for ( int i = 0; i < 256; ++i )
                sColorTable.push_back( qRgb( i, i, i ) );
        }

        QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_Indexed8 );

        image.setColorTable( sColorTable );

        return image;
    }

    default:
        qWarning() << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
        break;
    }

    return QImage();
}
