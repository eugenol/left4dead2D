#pragma once
class CTwoDVector
{
public:
	CTwoDVector();
	CTwoDVector( int x, int y );
	CTwoDVector( const CTwoDVector& obj); //copy constructor
	~CTwoDVector();

	CTwoDVector& operator=(const CTwoDVector& obj); //copy assignment

	//operators
	CTwoDVector operator+(const CTwoDVector& obj);
	CTwoDVector operator-(const CTwoDVector& obj);
	CTwoDVector operator*(const int& obj);
	CTwoDVector operator/(const int& obj);
	bool operator==( const CTwoDVector& obj );


	double DistanceToSq(const CTwoDVector& obj);
	double DistanceTo(const CTwoDVector& obj);
	double Magnitude();
	
	int m_x;
	int m_y;
};

