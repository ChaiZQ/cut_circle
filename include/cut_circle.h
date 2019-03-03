#ifndef EIGEN_ICOSPHERE_H
#define EIGEN_ICOSPHERE_H

#include <Eigen/Core>
#include <vector>

class IcoSphere
{
public:
	IcoSphere(float _x, float _y, float _r, int _max_num_vertex, int _level);

	const std::vector<Eigen::Vector2f>& vertices() const { return mVertices; }
	const std::vector<int>& indices(int level) const;
	std::vector<Eigen::Vector2f> mVertices;  //triangle vertex coordinate
	std::vector<std::vector<int>*> mIndices; //triangle vectex number
	
	float x;
	float y;
	float r;
	int num_vertex;
	int max_num_vertex;
	int level;

	~IcoSphere();
protected:
	void _subdivide();
	std::vector<int> mListIds;
};

#endif // EIGEN_ICOSPHERE_H
