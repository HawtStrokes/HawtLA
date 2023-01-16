#pragma once
#include <vector>

namespace HLA
{
	class Matrix;
	//bool IsDiagonal(Matrix);
	//bool IsTriangular(Matrix);
	//bool IsSymmetric(Matrix);
	bool IsSquare(Matrix&);
	double Dot(const std::vector<double>& v, const std::vector<double>& w);
	double TwoVectorAngle(const std::vector<double>& v, const std::vector<double>& w);
	Matrix Zero(size_t m, size_t n);

}
