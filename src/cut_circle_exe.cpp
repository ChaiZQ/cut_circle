#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <iterator>
#include <set>
#include <Eigen/Core>
#include "cut_circle.h"
#define THREAD_SIZE (2*PAGE_SIZE)

using namespace std;
using namespace cv;
using namespace Eigen;

vector <double> vertices;
vector<Eigen::Vector2f> vec_coordinate;//coordinates of all vetex
float c=3.1415926/180.0f;
int xc,yc,r,num_points,level;

void PointWrite(Eigen::Vector2f vec,FileStorage& fs)
{
	fs<<"[:" << vec[0] << vec[1] << "]";
}

void IcosphereWrite(FileStorage& fs)
{
	fs<<"r"<<r;
	fs<<"num"<<num_points;
	fs<<"coordinate"<<"[";
	for(int i = 0;i<(int)vec_coordinate.size();i++)
	{
		Eigen::Vector2f tem_vec = vec_coordinate[i];
		PointWrite(tem_vec,fs);
	}
	fs<<"]";
}

int main(int argc,char *argv[])
{
	// XML used to store coordinates of  icosohedron
	cv::FileStorage fs("coordinate.xml", cv::FileStorage::WRITE);
	fs<<"data"<<"[";

	// init a new icohedron at diameter r (m)
	xc=100;
	yc=100;
	r =100;
	num_points=1;
	level=2;

	IcoSphere icosphere = IcoSphere(xc, yc, r, num_points, level);
	vec_coordinate.clear();
	vec_coordinate = icosphere.vertices();
	cout<<"number of points: "<<icosphere.num_vertex<<endl;
	
	// store coordinates into XML files
	fs<<"{";
	IcosphereWrite(fs);
	fs<<"}";
	
	cv::Mat img(480,640,CV_8UC3);
	for (int i=0;i<vec_coordinate.size();i++)
	{

		cv::circle(img,Point(vec_coordinate[i][0],vec_coordinate[i][1]),8,CV_RGB(255,0,0),2);
		//void circle(CV_IN_OUT Mat& img, Point center, int radius, const Scalar& color, int thickness=1, int lineType=8, int shift=0)

		std::cout<<vec_coordinate[i][0]<<" "<<vec_coordinate[i][1]<<std::endl;
		imshow("test", img);
		cv::waitKey(100);
	}
	cv::circle(img,Point(100,100),100,CV_RGB(0,255,0),2);
	imshow("test", img);
	waitKey(100);
	fs<<"]";
	fs.release();
	return 1;
}
