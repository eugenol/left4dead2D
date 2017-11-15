#pragma once
#include "CTwoDVector.h"
#include <vector>

class CPath
{
public:
	CPath();
	CPath(std::vector<CTwoDVector>& path);
	~CPath();

	void operator=(std::vector<CTwoDVector>& path);

	void AddNode(CTwoDVector node) { m_path.push_back(node); }
	CTwoDVector& GetNextNode() { return m_path[m_currentIndex++]; }

	size_t Size() { return m_path.size(); }
	CTwoDVector& operator[](size_t idx) { return m_path[idx]; }

	void Draw();

private:
	std::vector<CTwoDVector> m_path;
	size_t m_currentIndex = 0;
};

