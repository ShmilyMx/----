#include "Star.h"



Star::Star()
{
	m_col = 0;
	m_row = 0;
	m_index = 0;
	m_canremove = false;
	m_ischecked = false;
	m_score = 5;
	m_can = false;
}
Star *Star::createStar(int row, int col)
{
	auto star = new Star();
	if (star &&star->initStar(row,col))
	{
		star->autorelease();
		return star;
	}
	CC_SAFE_DELETE(star);
	return nullptr;
}


bool Star::initStar(int row, int col)
{
	do
	{
		m_index = random(1, 5);
		switch (m_index)
		{
		case 1:
		{
			CC_BREAK_IF(!Sprite::initWithFile("red.png"));
			this->m_row = row;
			this->m_col = col;
			break;
		}
		case 2:
		{
			CC_BREAK_IF(!Sprite::initWithFile("blue.png"));
			this->m_row = row;
			this->m_col = col;
			break;
		}
		case 3:
		{
			CC_BREAK_IF(!Sprite::initWithFile("orange.png"));
			this->m_row = row;
			this->m_col = col;
			break;
		}
		case 4:
		{
			CC_BREAK_IF(!Sprite::initWithFile("purple.png"));
			this->m_row = row;
			this->m_col = col;
			break;
		}
		case 5:
		{
			CC_BREAK_IF(!Sprite::initWithFile("green.png"));
			this->m_row = row;
			this->m_col = col;
			break;
		}
		default:
			break;
		}
		return true;
	} while (0);
	return false;
}
