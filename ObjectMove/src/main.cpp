/********************** Problem *************************
Give an object position, we can move, rotate, scale locally
and repeat N times, e.g. (R, T, S, R, T, T, R) x N, to get 
final position of the object
***********************************************************/
#if defined(NDEBUG)
#undef NDEBUG
#endif

#include <iostream>
#include <cassert>

constexpr double PI = 3.14159265358979;

inline double Radian(double angle)
{
	return angle / 180.f * PI;
}

template<typename T>
T FastPow(T base, long long n)
{
	T ret(1);
	while (n)
	{
		if (n & 1)
			ret = ret * base;
		base = base * base;
		n >>= 1;
	}
	return ret;
}

struct Vec2
{
	double x, y, w;
	Vec2(double x = 0, double y = 0, double w = 1) : x(x), y(y), w(w) {}
	const double operator[](int i) const 
	{ 
		assert((i >= 0) && (i <= 2));
		return *(&x + i); 
	}
	double& operator[](int i) 
	{
		assert((i >= 0) && (i <= 2));
		return *(&x + i); 
	}
	Vec2 operator*(double value) const
	{ 
		return Vec2(x * value, y * value, w * value); 
	}
	Vec2 operator/(double value) const
	{ 
		assert(value != 0);
		return Vec2(x / value, y / value, w / value); 
	}

	friend inline std::ostream& operator<<(std::ostream& os, const Vec2& v)
	{
		os << "[" << v.x << ", " << v.y << "]";
		return os;
	}
};

class Matrix3
{
private:
	double mMat[3][3];
public:
	Matrix3(double value = 1)
	{
		memset(mMat, 0, sizeof(mMat));
		for (int i = 0; i < 3; ++i)
			mMat[i][i] = value;
	}

	Matrix3(
		double m00, double m01, double m02,
		double m10, double m11, double m12,
		double m20, double m21, double m22)
	{
		mMat[0][0] = m00; mMat[0][1] = m01; mMat[0][2] = m02;
		mMat[1][0] = m10; mMat[1][1] = m11; mMat[1][2] = m12;
		mMat[2][0] = m20; mMat[2][1] = m21; mMat[2][2] = m22;
	}

	Matrix3(const Matrix3& mat) 
	{
		memcpy(mMat, mat.mMat, sizeof(mMat));
	}

	Matrix3(double mat[3][3])
	{
		memcpy(mMat, mat, sizeof(mat));
	}

	Matrix3& operator=(const Matrix3& mat)
	{
		memcpy(mMat, mat.mMat, sizeof(mMat));
		return *this;
	}

	double* operator[](int i)
	{
		assert((i >= 0) && (i <= 2));
		return mMat[i];
	}

	const double* operator[](int i) const
	{
		assert((i >= 0) && (i <= 2));
		return mMat[i];
	}

	Matrix3 operator+(const Matrix3& mat) const
	{
		Matrix3 ret(0.f);
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				ret[i][j] = mMat[i][j] + mat[i][j];
			}
		}
		return ret;
	}

	Matrix3 operator*(const Matrix3& mat) const
	{
		Matrix3 ret(0.f);
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				for (int k = 0; k < 3; ++k)
				{
					ret.mMat[i][j] += mMat[i][k] * mat.mMat[k][j];
				}
			}
		}
		return ret;
	}

	Vec2 operator*(const Vec2& v) const 
	{
		Vec2 ret(0, 0, 0);
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				ret[i] += mMat[i][j] * v[j];
			}
		}
		if ((ret.w != 0) && (ret.w != 1))
			ret = ret / ret.w;
		return ret;
	}

	static Matrix3 Rotate(double dTheta)
	{
		return Matrix3(
			std::cos(Radian(dTheta)), -std::sin(Radian(dTheta)), 0,
			std::sin(Radian(dTheta)), std::cos(Radian(dTheta)), 0,
			0, 0, 1);
	}

	static Matrix3 Translate(double dx, double dy)
	{
		return Matrix3(
			1, 0, dx,
			0, 1, dy,
			0, 0, 1
		);
	}

	static Matrix3 Scale(double s)
	{
		return Matrix3(
			s, 0, 0,
			0, s, 0,
			0, 0, 1
		);
	}

	friend std::ostream& operator<<(std::ostream& os, const Matrix3& v)
	{
		os << "[" << std::endl;
		for (int i = 0; i < 3; ++i)
		{
			std::cout << "   ";
			for (int j = 0; j < 3; ++j)
			{
				if (j < 2)
					os << v.mMat[i][j] << ", ";
				else
					os << v.mMat[i][j] << std::endl;
			}
		}
		os << "]";
		return os;
	}
};


int main()
{
	Vec2 point0(-0.5, -0.5), point1(0.5, -0.5), point2(0.5, 0.5), point3(-0.5, 0.5);
	Matrix3 T = Matrix3::Rotate(22) * Matrix3::Translate(0.7, 0.5) * Matrix3::Rotate(33) ;
	std::cout << T << std::endl;
	long long n = 98850540134501;
	Matrix3 TT = FastPow(T, n);
	std::cout << TT * point0 << ", "
		<< TT * point1 << ", " 
		<< TT * point2 << ", "
		<< TT * point3 << std::endl;

	return 0;
}