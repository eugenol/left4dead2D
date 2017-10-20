#pragma once
#include <utility>

//-------------------------------------------------------

class CTwoDVector
{
public:
	CTwoDVector();
	CTwoDVector(double x, double y );
	CTwoDVector( const CTwoDVector& v); //copy constructor
	~CTwoDVector();

	CTwoDVector& operator=(const CTwoDVector& v); //copy assignment

	//operators

	CTwoDVector operator-();

	CTwoDVector operator+(const CTwoDVector& v);
	CTwoDVector operator-(const CTwoDVector& v);
	CTwoDVector operator*(const double& d);
	CTwoDVector operator/(const double& d);

	CTwoDVector& operator+=( const CTwoDVector& v );
	CTwoDVector& operator-=( const CTwoDVector& v );

	bool operator==( const CTwoDVector& v );
	bool operator!=( const CTwoDVector& v );
	

	CTwoDVector EuclideanNorm();
	double DistanceToSq(const CTwoDVector& v);
	double DistanceTo(const CTwoDVector& v);
	double Magnitude();

	double DotProduct(const CTwoDVector& v);
	
	double m_x;
	double m_y;

	const double epsilon = 1e-10;
};

//-------------------------------------------------------

CTwoDVector operator*(const double& d, const CTwoDVector& v);