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
	//����star�ľ���
	void createStar();
	//�������õ�star��ӵ�������
	Star **m_stars;
	//��Ŵ�����Χ��ͬ�ĵ�
	Vector<Star *>m_vecstar;
	Vector<Star *>m_vec;

	//��¼���λ��
	Vec2 begin;
	//��Ч����
	Sprite *sp;


	//���ϼ��
	void upCheck(int);
	//���¼��
	void downCheck(int);
	//������
	void leftCheck(int);
	//���Ҽ��
	void rightCheck(int);

	//�Ƴ�star
	void removeStar();

	//�����ƶ�
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