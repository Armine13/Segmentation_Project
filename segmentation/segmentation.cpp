#include "segmentation.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <Eigen/Dense>
#include <string>
#include <QWidget>
#include <QDebug>
#include <algorithm>
#include <Eigen/Dense>
#include <Eigen/SparseCholesky>
#include <Eigen/SparseCore>

#include <Eigen/IterativeLinearSolvers>
#include <Eigen/Cholesky>

//Eigen/include/src/IterativeLinearSolvers/BiCGSTAB.h
#include <QElapsedTimer>
using namespace cv;
using namespace std;
using Eigen::Matrix;
using Eigen::VectorXd;
using Eigen::SparseView;

Segmentation::Segmentation()
{}
Segmentation::Segmentation(String imageFile, String seedFile)
{
    originalImage = imread(imageFile);

    imgRows = originalImage.rows;
    imgCols = originalImage.cols;

    Mat seedImage = imread(seedFile);

    assert(!originalImage.empty());
    assert(!seedImage.empty());
    segmentationMatrix = VectorXd();
//    segmentedImage = Mat( originalImage.size(), originalImage.type());
//    segmentedImage.setTo(cv::Scalar(255, 255, 255));
    QElapsedTimer myTimer;
    myTimer.start();

    computeWeights();
    qDebug()<<"compute Weights: "<<myTimer.elapsed() <<endl;

    myTimer.restart();
    readSeeds(seedImage);
    qDebug()<<"readSeeds: "<<myTimer.elapsed() <<endl;

    minimizeEnergy();

}
Segmentation::~Segmentation()
{}
int Segmentation::getImgRows() const
{
    return originalImage.rows;
}
int Segmentation::getImgCols() const
{
    return originalImage.cols;
}
QImage Segmentation::getSegmentedImage()
{
    int rows = getImgRows();
    int cols = getImgCols();
    int size = rows*cols;
    QVector<Mat > segmentedImages;
    for(int i = 0; i < nSeeds; i++)
    {
        segmentedImages.append(Mat( originalImage.size(), originalImage.type()));
        segmentedImages[i].setTo(cv::Scalar(255, 255, 255));
    }
    Mat mytemp = Mat( originalImage.size(), originalImage.type());
    mytemp.setTo(cv::Scalar(255, 255, 255));

    //    Mat segmentedImage = Mat( originalImage.size(), originalImage.type());
    //    segmentedImage
    //            http://stackoverflow.com/questions/5026965/how-to-convert-an-opencv-cvmat-to-qimage
    //    QImage imgOut= QImage((uchar*) segmentedImage.data, segmentedImage.cols, segmentedImage.rows, segmentedImage.step, QImage::Format_RGB888);

    // thresholding the values of segmentationMatrix with th = mean of seedValue

    if (nSeeds == 2)
        for(int i = 0; i < size; i++)
        {
            int y = i / cols;
            int x = i % cols;
            if (segmentationMatrix(i) >= 1.5)
            {
                segmentedImages[0].at<Vec3b>(y, x) = getIntensity(y, x);
                mytemp.at<Vec3b>(y, x) = getIntensity(y, x);
            }
            else
                segmentedImages[1].at<Vec3b>(y, x) = getIntensity(y, x);

        }
    cv::cvtColor(segmentationMatrix, cimg, CV_GRAY2RGB);
    QVector<QImage> convertedIMages;
    for(int i = 0; i < nSeeds; i++)
        convertedIMages.append(cvMatToQImage(segmentedImages[i]));

    return cvMatToQImage(segmentedImages[1]);

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
bool Segmentation::computeWeights()
{
    // compute the size of matrix w

    float beta = 0.7;
    //double sigma = 0;
    int rows = getImgRows();
    int cols = getImgCols();
    int size = rows * cols;
    w = Matrix<double, Eigen::Dynamic, Eigen::Dynamic>::Zero(size, 4);//weights of edges
    W_mat = Eigen::SparseMatrix<double>(size,size);
     W_mat.reserve(Eigen::VectorXi::Constant(size,4));
//    W_mat = Eigen::SparseMatrix<double>::Zero(size, size); //sparse matrix of weights
    int index = 0;

    int nrm = 0; // norm
    float epsilon = 0.000001;

    for (int y = 0; y < rows; y++)
        for (int x = 0; x < cols; x++)
        {

            //            sigma = 0;

            //up
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
Vec3b Segmentation::getIntensity(int y, int x) const
{
    assert (y >= 0 && y < getImgRows() && x >= 0 && x < getImgCols());
    return originalImage.at<Vec3b>(y, x);
}
double Segmentation::getWeights(int i, int j) const// i = pixel indx,j = neighbor(0-3)
{
    assert (j < 4 && j >= 0 && i < getImgCols()*getImgRows() && i >= 0);
    return w(i, j);
}

bool Segmentation::readSeeds(const Mat &seedImage)
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
    seed = Matrix<char, Eigen::Dynamic, Eigen::Dynamic>::Zero(rows, cols);

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
    nSeeds = s.size(); // number of seed classes(2 for basic case)
    return true;
}

int Segmentation::getSeedFromMatrix(int y, int x) const
{
    assert (y >= 0 && y < getImgRows()  && x >= 0 && x < getImgCols());
    return int(seed(y, x));
}

int Segmentation::getSeedFromVector(int i) const
{
    assert (i >= 0 && i < getImgRows()* getImgCols());
    return int(seed(i / getImgCols(), i % getImgCols()));
}

int Segmentation::getSeedNumber() const//returns the number of seed classes
{
    return nSeeds;
}
bool Segmentation::minimizeEnergy()
{
    QElapsedTimer myTimer;



    int rows = getImgRows();
    int cols = getImgCols();
    int size = rows*cols;

    Eigen::SparseMatrix<double> Is(size, size);

    //Is is a diagonal matrix, with Is(i,i) = 1 when seed(i) != 0
    for(int i = 0; i < size; i++)
        if (getSeedFromVector(i) > 0)
            Is.coeffRef(i,i) = 1;

    Eigen::SparseMatrix<double> A(size,size);
    W_mat.reserve(Eigen::VectorXi::Constant(size,6));
    //A = A + D, where D is diagonal matrix, with D(i,i) = valency of pixel
    for(int i = 0; i < size; i++)
        for(int c = 0; c < 4; c++)//columns of matrix of weight = number of neighbors
            A.coeffRef(i,i) += getWeights(i, c); //valency of pixel = sum of weights for a pixel



    VectorXd b = VectorXd::Zero(size);
    //read
    for(int i = 0; i < size; i++)
        b(i) = getSeedFromVector(i);

    A = A - W_mat;// A = L = D - W

    A = A * A;
    //A = L^2

    A = A + Is; //A = Is + L^2


    Eigen::SimplicialLDLT<Eigen::SparseMatrix<double> > ldlt;


    myTimer.start();
    ldlt.compute(A);

    qDebug()<<"compute "<<myTimer.elapsed();

    myTimer.restart();
//    VectorXd v;

    segmentationMatrix.resize(size);
    segmentationMatrix = ldlt.solve(b);
//    v.resize(size);
//    v = ldlt.solve(b);

    qDebug()<<" solved "<<myTimer.elapsed();

//    // thresholding the values of v with th = mean of seedValue
//    for(int i = 0; i < size; i++)
//    {
//        if (v(i) >= 1.5)
//        {
//            int y = i / cols;
//            int x = i % cols;
//            segmentedImage.at<Vec3b>(y, x) = getIntensity(y, x);
//        }
//    }
    //imshow("asdf",segmentedImage);
    return true;
}
