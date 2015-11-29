#include "cocos2d.h"
#include "Star.h"

USING_NS_CC;

class GameScene :public Layer
{
public:
	GameScene();
	~GameScene();
	static Scene *createScene();
	bool init();
	CREATE_FUNC(GameScene);
	void update(float);
private:
	//创建star的矩阵
	void createStar();
	//将创建好的star添加到矩阵中
	Star **m_stars;
	//存放触摸周围相同的点
	Vector<Star *>m_vecstar;
	Vector<Star *>m_vec;

	//记录点的位置
	Vec2 begin;
	//特效星星
	Sprite *sp;


	//向上检测
	void upCheck(int);
	//向下检测
	void downCheck(int);
	//向左检测
	void leftCheck(int);
	//向右检测
	void rightCheck(int);

	//移除star
	void removeStar();

	//向下移动
	void moveDown();
	void moveLeft(int,int);


	int m_max;
	int m_number;
	int m;
	int score;
	int level;
	bool isCheck;
	Texture2D *texture;

	void isChecked();


	void checkStar();

	void rightCheck(Star *);
	void upCheck(Star *);
};