#include "cut_circle.h"
#include <map>
#include <iostream>

using namespace Eigen;
using namespace std;

IcoSphere::IcoSphere(float _x=0, float _y=0, float _r=1, int _max_num_vertex=1, int _level=1)
{
	x=_x;
	y=_y;
	r = _r;
	level=_level;

	float A = 1.0/2*r;
	float B = sqrt(3.0)/2*r;
	
	float vdata[7][2] = 
	{
		{0.0f+x,	0.0f+y}, 
		{A+x,		B+y  }, 
		{1.0f*r+x, 	0.0f*r+y}, 
		{A+x,		-B+y },
		{-A+x,		-B+y },
		{-1.0f*r+x,	0.0f*r+y},
		{-A+x,		B+y  },
	};

	int tindices[6][3] = 
	{
		{0,1,2},
		{0,2,3},
		{0,3,4},
		{0,4,5},
		{0,5,6},
		{0,6,1}
	};

	for (int i = 0; i < 7; i++)
		mVertices.push_back(Map<Vector2f>(vdata[i]));
	mIndices.push_back(new std::vector<int>);
	std::vector<int>& indices = *mIndices.back();
	for (int i = 0; i < 6; i++)
	{
		for (int k = 0; k < 3; k++)
			indices.push_back(tindices[i][k]);
	}
	mListIds.push_back(0);

	while(mIndices.size()<level)
		_subdivide();

	num_vertex=mVertices.size();
}

const std::vector<int>& IcoSphere::indices(int level) const
{
	while (level>=int(mIndices.size()))
		const_cast<IcoSphere*>(this)->_subdivide();
	return *mIndices[level];
}

void IcoSphere::_subdivide(void)
{
	cout<<"subdivide once"<<endl;
	typedef unsigned long long Key;
	std::map<Key,int> edgeMap;
	const std::vector<int>& indices = *mIndices.back();
	mIndices.push_back(new std::vector<int>);
	std::vector<int>& refinedIndices = *mIndices.back();
	int end = indices.size();
	for (int i=0; i<end; i+=3)
	{
    int ids0[3],  // indices of outer vertices
        ids1[3];  // indices of edge vertices
        for (int k=0; k<3; ++k)
        {
        	int k1 = (k+1)%3;
        	int e0 = indices[i+k];
        	int e1 = indices[i+k1];
        	ids0[k] = e0;
        	if (e1>e0)
        		std::swap(e0,e1);
        	Key edgeKey = Key(e0) | (Key(e1)<<32);
        	std::map<Key,int>::iterator it = edgeMap.find(edgeKey);
        	if (it==edgeMap.end())
        	{
        		ids1[k] = mVertices.size();
        		edgeMap[edgeKey] = ids1[k];
        		mVertices.push_back( (mVertices[e0]+mVertices[e1])/2);
        	}
        	else
        		ids1[k] = it->second;
        }
        refinedIndices.push_back(ids0[0]); refinedIndices.push_back(ids1[0]); refinedIndices.push_back(ids1[2]);
        refinedIndices.push_back(ids0[1]); refinedIndices.push_back(ids1[1]); refinedIndices.push_back(ids1[0]);
        refinedIndices.push_back(ids0[2]); refinedIndices.push_back(ids1[2]); refinedIndices.push_back(ids1[1]);
        refinedIndices.push_back(ids1[0]); refinedIndices.push_back(ids1[1]); refinedIndices.push_back(ids1[2]);
    }
    mListIds.push_back(0);
}

IcoSphere::~IcoSphere()
{
	cout<<"delete icosphere"<<endl;
}
