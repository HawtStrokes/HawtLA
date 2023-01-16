#include "Common.h"
#include "Matrix.h"
#include "MatrixExceptions.h"


namespace HLA
{
	bool IsSquare(Matrix& mat)
	{
		const Size sz = mat.Shape();
		if (sz.c == sz.r) return true;
		return false;
	}

	double Dot(const std::vector<double>& v, const std::vector<double>& w)
	{
		double dot = 0;

		
		for (size_t i = 0; i < v.size(); ++i)
		{
			dot += v.at(i) * w.at(i);
		}
		return dot;
	}

	double TwoVectorAngle(const std::vector<double>& v, const std::vector<double>& w)
	{
		if (v.size() != w.size())
			throw DimensionError("Incompatible Dimensions, cannot get angle between two vectors.");
		const double dot = Dot(v, w);

		const auto vMatNorm = Matrix{ {v} ,{v.size(), 1 } }.Norm(2);
		const auto wMatNorm = Matrix{ { w } ,{ w.size(), 1 } }.Norm(2);
		const double theta = dot / (vMatNorm * wMatNorm);
		return acos(theta); // angle in radians
	}

	Matrix Zero(size_t m, size_t n)
	{
		return Matrix{std::vector<double>(m * n, 0), {m, n}};
	}
}
