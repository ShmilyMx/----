#include "cocos2d.h"

USING_NS_CC;

class Star :public Sprite
{
public:
	Star();
	static Star *createStar(int, int);
	bool initStar(int, int);

	CC_SYNTHESIZE(int, m_row, Row);
	CC_SYNTHESIZE(int, m_col, Col);
	CC_SYNTHESIZE(int, m_index, Index);
	CC_SYNTHESIZE(bool, m_canremove, Remove);
	CC_SYNTHESIZE(bool, m_ischecked, Checked);
	CC_SYNTHESIZE(bool, m_can, Can);
	CC_SYNTHESIZE(int, m_score, Score);

};