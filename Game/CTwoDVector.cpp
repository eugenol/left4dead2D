#include "CTwoDVector.h"
#include <cmath>

//-------------------------------------------------------

CTwoDVector::CTwoDVector()
	:
	m_x(0),
	m_y(0)
{
}

//-------------------------------------------------------

CTwoDVector::CTwoDVector( double x, double y )
	:
	m_x(x),
	m_y(y)
{
}

//-------------------------------------------------------

CTwoDVector::CTwoDVector( const CTwoDVector& v )
	:
	m_x(v.m_x),
	m_y(v.m_y)
{
}

//-------------------------------------------------------

CTwoDVector::~CTwoDVector()
{
}

//-------------------------------------------------------

CTwoDVector& CTwoDVector::operator=( const CTwoDVector& v )
{
	m_x = v.m_x;
	m_y = v.m_y;
	return *this;
}

CTwoDVector CTwoDVector::operator-()
{
	return CTwoDVector(-m_x, -m_y);
}

CTwoDVector CTwoDVector::operator+( const CTwoDVector& v )
{
	return CTwoDVector(m_x + v.m_x, m_y + v.m_y);
}

CTwoDVector CTwoDVector::operator-( const CTwoDVector& v )
{
	return CTwoDVector( m_x - v.m_x, m_y - v.m_y );
}

CTwoDVector CTwoDVector::operator*( const double& d )
{
	return CTwoDVector( m_x*d, m_y*d );
}

//-------------------------------------------------------

CTwoDVector CTwoDVector::operator/( const double& d )
{
	return CTwoDVector( m_x / d, m_y / d);
}

//-------------------------------------------------------

CTwoDVector& CTwoDVector::operator+=(const CTwoDVector& v)
{
	m_x += v.m_x;
	m_y += v.m_y;
	return *this;
}

//-------------------------------------------------------

CTwoDVector& CTwoDVector::operator-=( const CTwoDVector& v )
{
	m_x -= v.m_x;
	m_y -= v.m_y;
	return *this;
}

//-------------------------------------------------------

bool CTwoDVector::operator==( const CTwoDVector& v )
{
	if( abs(m_x -v.m_x) < epsilon && abs(m_y - v.m_y) < epsilon )
	{
		return true;
	}
	return false;
}

//-------------------------------------------------------

bool CTwoDVector::operator!=( const CTwoDVector& v )
{
	return !(*this == v);
}

CTwoDVector CTwoDVector::EuclideanNorm()
{
	CTwoDVector result = *this;
	result = result/Magnitude();
	return result;
}

//-------------------------------------------------------

double CTwoDVector::DistanceToSq( const CTwoDVector& v )
{
	double dX = m_x - v.m_x;
	double dY = m_y - v.m_y;
	return dX*dX + dY*dY;
}

//-------------------------------------------------------

double CTwoDVector::DistanceTo( const CTwoDVector& v )
{
	return sqrt( DistanceToSq( v ) );
}

//-------------------------------------------------------

double CTwoDVector::Magnitude()
{
	return sqrt( m_x*m_x + m_y*m_y);
}

//-------------------------------------------------------

double CTwoDVector::DotProduct( const CTwoDVector& v )
{
	return (m_x*v.m_x + m_y*v.m_y);
}

//-------------------------------------------------------

CTwoDVector operator*( const double& d, const CTwoDVector& v )
{
	CTwoDVector result(v);
	return result * 2;
}

//-------------------------------------------------------



