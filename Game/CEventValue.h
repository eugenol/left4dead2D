#pragma once

template<typename T>
class CEventValue
{
public:
	CEventValue( T value );
	~CEventValue();

	operator T() { return m_currentValue; }
	operator T() const { return m_currentValue; }
	bool HasChanged();
	void operator=( const T value );
	
private:
	T m_currentValue;
	T m_previousValue;
};

template<typename T>
CEventValue<T>::CEventValue(T value)
	:
	m_currentValue(value),
	m_previousValue(value)
{
}

template<typename T>
CEventValue<T>::~CEventValue()
{
}

template<typename T>
bool CEventValue<T>::HasChanged()
{
	return !(m_previousValue == m_currentValue);
}

template<typename T>
void CEventValue<T>::operator=(const T value)
{
	m_previousValue = m_currentValue;
	m_currentValue = value;
}
