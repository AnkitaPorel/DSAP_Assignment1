#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>
#include <float.h>

using namespace std;
using namespace cv;

void calculateEnergy(Mat& img,Mat& energy)
{
    Mat gray;
    cvtColor(img,gray,COLOR_BGR2GRAY);
    Mat grad_x;
    Sobel(gray,grad_x,CV_64F,1,0,3);
    Mat grad_y;
    Sobel(gray,grad_y,CV_64F,0,1,3);
    Mat square_grad_x,square_grad_y,grad_combined,magnitude;
    multiply(grad_x,grad_x,square_grad_x);
    multiply(grad_y,grad_y,square_grad_y);
    add(square_grad_x,square_grad_y,grad_combined);
    sqrt(grad_combined,magnitude);
    normalize(magnitude,energy,0,255,NORM_MINMAX,CV_8UC3);
    imshow("Energy Function Image",energy);
}

int* seamIdentification(Mat& energy)
{
    int* seam=new int[energy.rows];
    Mat indexDp(energy.rows,energy.cols,CV_32S,-1);
    Mat dp(energy.rows,energy.cols,CV_64F,FLT_MAX);
    for(int i=0;i<energy.cols;i++)
        dp.at<double>(0,i)=energy.at<uchar>(0,i);
    double minEnergy=FLT_MAX;
    int minIndex=0;
    for(int i=1;i<energy.rows;i++)
    {
        for(int j=0;j<energy.cols;j++)
        {
            double x=dp.at<double>(i-1,j),y=0,z=0;
            if(j>0)
                y=dp.at<double>(i-1,j-1);
            else
                y=FLT_MAX;
            if(j<energy.cols-1)
                z=dp.at<double>(i-1,j+1);
            else
                z=FLT_MAX;
            if(x<y)
            {
                minEnergy=x;
                minIndex=j;
            }
            else
            {
                minIndex=j-1;
                minEnergy=y;
            }
            if(z<minEnergy)
            {
                minEnergy=z;
                minIndex=j+1;
            }
            dp.at<double>(i,j)=minEnergy+energy.at<uchar>(i,j);
            indexDp.at<int>(i,j)=minIndex;
        }
    }
    minIndex=0;
    minEnergy=FLT_MAX;
    for(int i=0;i<energy.cols;i++)
    {
        if(dp.at<double>(energy.rows-1,i)<minEnergy)
        {
            minEnergy=dp.at<double>(energy.rows-1,i);
            minIndex=i;
        }
    }
    for(int i=energy.rows-1;i>=0;i--)
    {
        seam[i]=minIndex;
        minIndex=indexDp.at<int>(i,minIndex);
    }
    return seam;
}

void seamRemoval(Mat& img,int* seam)
{
    Mat newImg(img.rows,img.cols-1,img.type());
    for(int i=0;i<img.rows;i++)
    {
        int k=0;
        for(int j=0;j<img.cols;j++)
        {
            if(j!=seam[i])
            {
                newImg.at<Vec3b>(i,k)=img.at<Vec3b>(i,j);
                k++;
            }
        }
    }
    img=newImg;
}

int main()
{
    while(true)
    {
        cout<<"\nPress 1 to continue,0 to Exit\n>>";
        int choice;
        cin>>choice;
        if(choice==0)
            return 0;
        else if(choice==1)
        {
            string ipImgPath;
            cout<<"\nEnter image file name,with path >>";
            cin>>ipImgPath;
            Mat ipImage=imread(ipImgPath,IMREAD_COLOR);
            if(ipImage.empty())
            {
                cout<<"\nImage file not found";
                continue;
            }
            cout<<"\nEnter desired new width of image: ";
            int newWidth;
            cin>>newWidth;
            cout<<"\nEnter desired height of image: ";
            int newHeight;
            cin>>newHeight;
            if(newHeight>ipImage.rows || newWidth>ipImage.cols)
            {
                cout<<"\nDesired image size is bigger. ";
                break;
            }
            while(ipImage.cols>newWidth)
            {
                Mat energy;
                calculateEnergy(ipImage,energy);
                int* seam=seamIdentification(energy);
                for(int i=0;i<ipImage.rows;i++)
                    ipImage.at<Vec3b>(i,seam[i])=Vec3b(0,0,255);
                imshow("Low Energy Line",ipImage);
                waitKey(50);
                seamRemoval(ipImage,seam);
            }
            while(ipImage.rows>newHeight)
            {
                Mat transposeImg;
                transpose(ipImage,transposeImg);
                Mat energy;
                calculateEnergy(transposeImg,energy);
                int* seam=seamIdentification(energy);
                for(int i=0;i<transposeImg.rows;i++)
                    transposeImg.at<Vec3b>(i,seam[i])=Vec3b(0,0,255);
                Mat tmp;
                transpose(transposeImg,tmp);
                imshow("Low Energy Line",tmp);
                waitKey(50);
                seamRemoval(transposeImg,seam);
                transpose(transposeImg,ipImage);
            }
            imshow("Resized Image",ipImage);
            waitKey(0);
        }
        else
            cout<<"\nInvalid choice";
    }
    return 0;
}