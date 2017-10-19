#pragma once
class CScreen
{
public:
	CScreen();
	virtual ~CScreen();

	virtual void Update() = 0;
	virtual void Draw() = 0;
	//virtual CScreen* SetNextScteern(CScreen* NextScreen) = 0;
	
};

//class ScreenState
//{
//public:
//	ScreenState() {}
//	virtual ~ScreenState() {}
//

//	virtual void ChangeState() = 0;
//	virtual bool GetReturnToMenu() { return m_returnToMenu; }
//	virtual void SetReturnToMenu() { m_returnToMenu = false; }
//private:
//	bool m_returnToMenu = false;
//};