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

CTwoDVector::CTwoDVector( int x, int y )
	:
	m_x(x),
	m_y(y)
{
}

//-------------------------------------------------------

CTwoDVector::CTwoDVector( const CTwoDVector& obj )
	:
	m_x(obj.m_x),
	m_y(obj.m_y)
{
}

//-------------------------------------------------------

CTwoDVector::~CTwoDVector()
{
}

//-------------------------------------------------------

CTwoDVector& CTwoDVector::operator=( const CTwoDVector& obj )
{
	m_x = obj.m_x;
	m_y = obj.m_y;
	return *this;
}

CTwoDVector CTwoDVector::operator+( const CTwoDVector& obj )
{
	CTwoDVector result;
	result.m_x = this->m_x + obj.m_x;
	result.m_y = this->m_y + obj.m_y;
	return result;
}

CTwoDVector CTwoDVector::operator-( const CTwoDVector& obj )
{
	CTwoDVector result;
	result.m_x = this->m_x - obj.m_x;
	result.m_y = this->m_y - obj.m_y;
	return result;
}

CTwoDVector CTwoDVector::operator*( const int& obj )
{
	CTwoDVector result;
	result.m_x = this->m_x*obj;
	result.m_y = this->m_y*obj;
	return result;
}

//-------------------------------------------------------

CTwoDVector CTwoDVector::operator/( const int& obj )
{
	CTwoDVector result;
	result.m_x = this->m_x/obj;
	result.m_y = this->m_y/obj;
	return result;
}

//-------------------------------------------------------

bool CTwoDVector::operator==( const CTwoDVector& obj )
{
	return(m_x == obj.m_x && m_y == obj.m_y);
}

//-------------------------------------------------------

double CTwoDVector::DistanceToSq( const CTwoDVector& obj )
{
	int dX = this->m_x - obj.m_x;
	int dY = this->m_y - obj.m_y;
	double result = dX*dX + dY*dY;
	return result;
}

//-------------------------------------------------------

double CTwoDVector::DistanceTo( const CTwoDVector& obj )
{
	return sqrt( DistanceToSq( obj ) );
}

//-------------------------------------------------------

double CTwoDVector::Magnitude()
{
	int dX = this->m_x;
	int dY = this->m_y;
	double result = sqrt(dX*dX + dY*dY);
	return result;
}

//-------------------------------------------------------



