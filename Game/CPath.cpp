#include "CPath.h"
#include <allegro5/allegro_primitives.h>


CPath::CPath()
{
}

CPath::CPath( std::vector<CTwoDVector>& path )
	:
	m_path(path)
{
}

CPath::~CPath()
{
}

void CPath::operator=( std::vector<CTwoDVector>& path )
{
	m_path = path;
}

void CPath::Draw()
{
	for( size_t i = 0; i < m_path.size() - 1; ++i)
	{
		al_draw_line(m_path[i].m_x, m_path[i].m_y, m_path[i + 1].m_x, m_path[i + 1].m_y, al_map_rgb( 255, 0, 255 ), 2);
	}
}
