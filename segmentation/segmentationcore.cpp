#include "segmentationcore.h"
#include "segmentationdata.h"
#include <string>
#include <QElapsedTimer>
#include <QDebug>
#include <opencv2/core/eigen.hpp>

SegmentationCore::SegmentationCore()
{}

SegmentationCore::SegmentationCore(String imageFile, String seedFile)
    :SegmentationData(imageFile,seedFile)//call SegmentationData constructor
{
    //Initialize segmentationMatrix, which will contain the results after segmentation:
    // each pixel will contain a value of seed1 or seed2
    segmentationMatrix = Mat( getImgSize(), getImgType());

    //If no seeds provided or their number is not 2, exit
    if (getSeedNumber() != 2) return;

    //Compute segmentation
    minimizeEnergy();
}
SegmentationCore::~SegmentationCore()
{}

void SegmentationCore::minimizeEnergy()
{
    int rows = getImgRows();
    int cols = getImgCols();
    int size = rows*cols;

    Eigen::SparseMatrix<double> Is(size, size);

    //Is is a diagonal matrix, with Is(i,i) = 1 when seed(i) != 0
    for(int i = 0; i < size; i++)
        if (getSeedFromVector(i) > 0)
            Is.coeffRef(i,i) = 1;

    Eigen::SparseMatrix<double> A(size,size);
    Eigen::SparseMatrix<double> W_mat;
    W_mat = getWeightsMatrix();
    //A = A + D, where D is diagonal matrix, with D(i,i) = valency of pixel
    for(int i = 0; i < size; i++)
        for(int c = 0; c < 4; c++)//columns of matrix of weight = number of neighbors
            A.coeffRef(i,i) += getWeights(i, c); //valency of pixel = sum of weights for a pixel

    Eigen::VectorXd b = Eigen::VectorXd::Zero(size);
    //read
    for(int i = 0; i < size; i++)
        b(i) = getSeedFromVector(i);

    A = A - W_mat;// A = L = D - W

    A = A * A;
    //A = L^2

    A = A + Is; //A = Is + L^2

    Eigen::SimplicialLDLT<Eigen::SparseMatrix<double> > ldlt;

    ldlt.compute(A);

    Eigen::VectorXd segmentationVector;
    segmentationVector.resize(size);

    //b contains results of segmentation
    segmentationVector = ldlt.solve(b);

    //reshape b into a matrix segmentationMatrix
    cv::eigen2cv(segmentationVector,segmentationMatrix);
    segmentationMatrix = segmentationMatrix.reshape(0,rows);
}
const Mat& SegmentationCore::getSegmentationMatrix() const
{
    return segmentationMatrix;
}
