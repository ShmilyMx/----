#include "GameScene.h"
#include "CommDate.h"

GameScene::GameScene()
{
	auto size = sizeof(Star *)*STAR_WEDTH*STAR_HEIGHT;
	m_stars = (Star **)malloc(size);
	memset(m_stars, 0, size);
	begin = Vec2::ZERO;
	m_max = 0;
	m_number = 0;
	m = 0;
	score = 0;
	level = 1;
	isCheck = false;
}

GameScene::~GameScene()
{
	CC_SAFE_FREE(m_stars);
}

Scene *GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	do
	{
		CC_BREAK_IF(!Layer::init());

		//添加背景
		auto bg = Sprite::create(GAMESCENE_BACKGROUND);
		bg->setPosition(VISIBLE_ORIGIN + Vec2(VISIBLE_SIZE) / 2);
		this->addChild(bg);

		//添加star
		createStar();

		auto labelSco = Label::createWithTTF(("Score:"), "haibaoti.ttf", 32);
		labelSco->setPosition(VISIBLE_SIZE.width / 2 - 150, VISIBLE_SIZE.height - 80);
		this->addChild(labelSco);
		labelSco->setColor(Color3B::ORANGE);
		
		

		//分数
		auto labelScore = Label::createWithTTF("0", "haibaoti.ttf", 32);
		labelScore->setPosition(VISIBLE_SIZE.width / 2 -100, VISIBLE_SIZE.height - 80-labelScore->getContentSize().height/2);
		this->addChild(labelScore, 100, 100);
		labelScore->setColor(Color3B::ORANGE);
		labelScore->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		

		auto labelGoalsco = Label::createWithTTF(("GoalScore:"), "haibaoti.ttf", 32);
		labelGoalsco->setPosition(VISIBLE_SIZE.width / 2+50 , VISIBLE_SIZE.height - 80);
		this->addChild(labelGoalsco);
		labelGoalsco->setColor(Color3B::ORANGE);



		//目标分数
		auto labelGoalscore = Label::createWithTTF("300", "haibaoti.ttf", 32);
		labelGoalscore->setPosition(VISIBLE_SIZE.width / 2 + 130, VISIBLE_SIZE.height - 80-labelGoalsco->getContentSize().height/2);
		this->addChild(labelGoalscore, 100, 101);
		labelGoalscore->setColor(Color3B::ORANGE);
		labelGoalscore->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		

		//添加监听事件
		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = [=](Touch *touch, Event *){
			begin = touch->getLocation();
			scheduleUpdate();
		
			for (auto i = 0; i < STAR_WEDTH*STAR_HEIGHT; i++)
			{
				if (m_stars[i] && m_stars[i]->getBoundingBox().containsPoint(touch->getLocation()))
				{
					m_stars[i]->setRemove(true);
					m_vecstar.pushBack(m_stars[i]);
				}
			}
		
			/*if (isCheck)
			{
				for (auto i = 0; i < STAR_WEDTH*STAR_HEIGHT; i++)
				{
					if (m_stars[i] && m_stars[i]->getBoundingBox().containsPoint(touch->getLocation()))
					{
						m_stars[i]->setRemove(true);
						m_vecstar.pushBack(m_stars[i]);
					}
				}
				isCheck = false;
			}*/
			isCheck = false;
			
			return true;
		};
		listener->onTouchEnded = [](Touch *touch, Event *){
		
		};

		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

		//定时器函数
		scheduleUpdate();
		return true;
	} while (0);
	return false;
}

void GameScene::createStar()
{
	for (auto row = 0; row < STAR_WEDTH; row++)
	{
		for (auto col = 0; col < STAR_HEIGHT; col++)
		{
			auto star = Star::createStar(row, col);
			auto x = star->getContentSize().width*col;
			auto y = star->getContentSize().height*row;
			star->setPosition(x, y);
			star->setAnchorPoint(Vec2::ZERO);
			this->addChild(star);
			m_stars[row*STAR_WEDTH + col] = star;
		}
	}
}

void GameScene::update(float)
{
	for (auto i = 0; i < 100; i++)
	{
		if (!m_stars[i]) continue;
		m_stars[i]->setCan(false);
	}
	checkStar();
	auto ww = 0;
	for (auto i = 0; i < 100; i++)
	{
		if (!m_stars[i]) continue;
		if (m_stars[i]&&m_stars[i]->getCan())
		{
			ww++;
		}
	}
	if (ww ==0)
	{
		unscheduleUpdate();
		
		if (score>=300*level)
		{
			for (auto i = 0; i < 100; i++)
			{
				if (!m_stars[i]) continue;

				auto number = random(1, 5);
				switch (number)
				{
				case 1:
				{
					sp = Sprite::create("red.png");
					break;
				}
				case 2:
				{
					sp = Sprite::create("blue.png");
					break;
				}
				case 3:
				{
					sp = Sprite::create("orange.png");
					break;
				}
				case 4:
				{
					sp = Sprite::create("purple.png");
					break;
				}
				case 5:
				{
					sp = Sprite::create("green.png");
					break;
				}
				default:
					break;
				}
				sp->setPosition(m_stars[i]->getPosition());
				auto scale = random(3, 4);
				sp->setScale(scale*0.1);
				float x = random(0, (int)VISIBLE_SIZE.width);
				float y = random(0, (int)VISIBLE_SIZE.height);
				auto move = MoveTo::create(0.5f, Vec2(x, y));
				sp->runAction(Sequence::create(Spawn::create(DelayTime::create(1),RotateBy::create(0.5f, 1000), move, nullptr), RemoveSelf::create(), nullptr));
				this->addChild(sp);
				/*this->removeChild(m_stars[i]);*/
				m_stars[i]->runAction(Sequence::create(DelayTime::create(1), RemoveSelf::create(), nullptr));
				m_stars[i] = nullptr;			
				
			}
			auto win = Sprite::create("stage_clear.png");
			win->setPosition(VISIBLE_ORIGIN + Vec2(VISIBLE_SIZE) / 2);
			win->setScale(0.5f);
			this->addChild(win);
			win->runAction(Sequence::create(Spawn::create(RotateBy::create(2.0f, 360), ScaleTo::create(2.0f, 1), nullptr), DelayTime::create(1), CallFunc::create([=](){
				createStar();
				log("=========");
				m_max = 0;
				m_number = 0;
				m = 0;
				level++;
				auto label = dynamic_cast<Label *>(this->getChildByTag(101));
				label->setString(StringUtils::format("%d", 300 * level));
			}), RemoveSelf::create(), nullptr));
		}
	}


	if (m_vecstar.size() == 0) return;
	if (m_vec.size() != m_vecstar.size())
	{
		m_vec = m_vecstar;
		for (auto star : m_vec)
		{
			/*log("=========%f,%f",star->getPositionX(),star->getPositionY());*/
			if (star->getChecked()) continue;
			int indexX = star->getPositionY() / 48;
			int indexY = star->getPositionX() / 48;
			auto index = indexX*STAR_WEDTH + indexY;
			star->setChecked(true);
			upCheck(index);
			downCheck(index);
			leftCheck(index);
			rightCheck(index);
		}
	}
	else
	{
		if (m_vecstar.size()==1)
		{
			m_vecstar.at(0)->setRemove(false);
			m_vecstar.at(0)->setChecked(true);
		}
		//isCheck = true;
		if (m_vecstar.size() != 1 && isCheck == false)
		{
			isChecked();
			removeStar();
		}
		/*else
		{


			
			m_vec.clear();
			m_vecstar.clear();
		}*/
		
		m_vec.clear();
		m_vecstar.clear();
	}

}

void GameScene::upCheck(int index)
{
	if (m_stars[index]->getRow() >= STAR_HEIGHT-1) return;
	auto nextIndex = index+STAR_WEDTH;
	if (m_stars[nextIndex] && m_stars[nextIndex]->getIndex() == m_stars[index]->getIndex())
	{
		m_vecstar.pushBack(m_stars[nextIndex]);
		m_stars[nextIndex]->setRemove(true);
	}
}

void GameScene::downCheck(int index)
{
	if (m_stars[index]->getRow() <= 0) return;
	auto nextIndex = index-STAR_WEDTH;
	if (m_stars[nextIndex] && m_stars[nextIndex]->getIndex() == m_stars[index]->getIndex())
	{
		m_vecstar.pushBack(m_stars[nextIndex]);
		m_stars[nextIndex]->setRemove(true);
	
	}
}

void GameScene::leftCheck(int index)
{
	if (m_stars[index]->getCol() <= 0) return;
	auto nextIndex = index-1;
	if (m_stars[nextIndex] && m_stars[nextIndex]->getIndex() == m_stars[index]->getIndex())
	{
		m_vecstar.pushBack(m_stars[nextIndex]);
		m_stars[nextIndex]->setRemove(true);
			
	}
}

void GameScene::rightCheck(int index)
{
	if (m_stars[index]->getCol() >= STAR_WEDTH-1) return;
	auto nextIndex =index + 1;
	if (m_stars[nextIndex] && m_stars[nextIndex]->getIndex() == m_stars[index]->getIndex())
	{
		m_vecstar.pushBack(m_stars[nextIndex]);
		m_stars[nextIndex]->setRemove(true);
	}
	scheduleUpdate();
}

void GameScene::removeStar()
{
	auto cnt = 0;
	for (auto i = 0; i < STAR_HEIGHT*STAR_WEDTH; i++)
	{
		if (m_stars[i] && m_stars[i]->getRemove())
		{
			score += m_stars[i]->getScore();
			for (auto i = 0; i < 15; i++)
			{
				auto number = random(1, 5);
				switch (number)
				{
				case 1:
				{
					sp = Sprite::create("red.png");
					break;
				}
				case 2:
				{
					sp = Sprite::create("blue.png");
					break;
				}
				case 3:
				{
					sp = Sprite::create("orange.png");					
					break;
				}
				case 4:
				{
					sp = Sprite::create("purple.png");
					break;
				}
				case 5:
				{
					sp = Sprite::create("green.png");
					break;
				}
				default:
					break;
				}
				sp->setPosition(begin);
				auto scale = random(3, 4);
				sp->setScale(scale*0.1);
				float x = random(0, (int)VISIBLE_SIZE.width);
				float y = random(0, (int)VISIBLE_SIZE.height);
				auto move = MoveTo::create(0.5f, Vec2(x, y));
				sp->runAction(Sequence::create(Spawn::create(RotateBy::create(0.5f, 1000), move, nullptr), RemoveSelf::create(), nullptr));
				this->addChild(sp);
			}

			/*auto pe = ParticleSystemQuad::create("star.plist");
			pe->setPosition(Vec2(begin));
			this->addChild(pe,500);*/
			cnt++;
			this->removeChild(m_stars[i]);
			m_stars[i] = nullptr;
		}
	}
	
	moveDown();
	for (auto col = 0; col < 10-m_max; col++)
	{
		if (m_stars[col]==nullptr)
		{
			m += m_number;
			moveLeft(col,m);
			break;
		}
	}
	
	if (cnt>=5 && cnt<=6)
	{
		auto combo = Sprite::create("combo_1.png");
		combo->setPosition(VISIBLE_SIZE / 2);
		combo->setScale(0.5f);
		this->addChild(combo);
		combo->runAction(Sequence::create(ScaleTo::create(0.5f, 2),RemoveSelf::create(), nullptr));
	}
	else if (cnt>=7 &&cnt<=9)
	{
		auto combo = Sprite::create("combo_2.png");
		combo->setPosition(VISIBLE_SIZE / 2);
		combo->setScale(0.5f);
		this->addChild(combo);
		combo->runAction(Sequence::create(ScaleTo::create(0.5f, 2), RemoveSelf::create(), nullptr));
	}
	else if (cnt>=10)
	{
		auto combo = Sprite::create("combo_3.png");
		combo->setPosition(VISIBLE_SIZE / 2);
		combo->setScale(0.5f);
		this->addChild(combo);
		combo->runAction(Sequence::create(ScaleTo::create(0.5f, 2), RemoveSelf::create(), nullptr));
	}

	auto labelscore = dynamic_cast<Label *>(this->getChildByTag(100));
	labelscore->setString(StringUtils::format("%d", score));
}

void GameScene::moveDown()
{
	for (auto col = 0; col < STAR_HEIGHT; col++)
	{
		auto cnt = 0;
		for (auto row = 0; row < STAR_WEDTH; row++)
		{
			auto star = m_stars[row*STAR_WEDTH + col];
			if (!star)
			{
				cnt++;
			}
			else if (cnt > 0)
			{
				auto newRow = star->getRow() - cnt;
				m_stars[newRow*STAR_WEDTH + star->getCol()] = star;
				m_stars[star->getRow()*STAR_WEDTH + star->getCol()] = nullptr;
				star->setRow(newRow);

				auto length = (star->getContentSize().height) * cnt;
				auto time = length / VISIBLE_SIZE.height*1.5f;
				star->runAction(MoveBy::create(time, Vec2(0, -length)));
			}
		}
	}


}

void GameScene::moveLeft(int c,int m)
{
	m_number = 0;
	for (auto row = 0; row < STAR_WEDTH; row++)
	{
		
		for (auto col = c; col < STAR_WEDTH - m; col++)
		{
			auto star = m_stars[row*STAR_WEDTH + col];
			if (!star)
			{
				/*if (row !=0)
				{
					continue;
				}
				else
				{
					cnt++;
				}*/
				if (row == 0)
				{
					m_number++;
				}
				
				
			}
			else if (m_number > 0)
			{
				auto newCol = star->getCol() - m_number;
				m_stars[star->getRow()*STAR_WEDTH + newCol] = star;
				m_stars[star->getRow()*STAR_WEDTH + star->getCol()] = nullptr;
				star->setCol(newCol);

				auto length = (star->getContentSize().width) * m_number;
				auto time = length / VISIBLE_SIZE.width*1.5f;
				star->runAction(MoveBy::create(time, Vec2(-length, 0)));
			}
		}
	}
	m_max += m_number;
}

void GameScene::checkStar()
{
	for (auto row = 0; row < STAR_HEIGHT; row++)
	{
		for (auto col = 0; col < STAR_WEDTH; col++)
		{
			if (!m_stars[row*STAR_WEDTH + col])
			{
				continue;
			}
			rightCheck(m_stars[row*STAR_WEDTH + col]);
			upCheck(m_stars[row*STAR_WEDTH + col]);
		}
	}
}

void GameScene::rightCheck(Star *star)
{

	auto number = 1;
	auto nextIcon = star->getRow()*STAR_WEDTH + star->getCol() + 1;
	while (nextIcon< (star->getRow() + 1)*STAR_WEDTH)
	{
		if (m_stars[nextIcon] && star->getIndex() == m_stars[nextIcon]->getIndex())
		{
			number++;

		}
		else
		{
			break;
		}
		nextIcon++;
	}
	if (number >= 2)
	{
		while (number > 0)
		{
			auto index = star->getRow()*STAR_WEDTH + star->getCol() + number - 1;
			m_stars[index]->setCan(true);
			number--;
		}
	}
}

void GameScene::upCheck(Star *star)
{
	auto number = 1;
	auto nextIcon = (star->getRow() + 1)*STAR_WEDTH + star->getCol();
	while (nextIcon< STAR_WEDTH*STAR_HEIGHT)
	{
		if (m_stars[nextIcon] && star->getIndex() == m_stars[nextIcon]->getIndex())
		{
			number++;

		}
		else
		{
			break;
		}
		nextIcon += STAR_WEDTH;
	}
	if (number >= 2)
	{

		while (number > 0)
		{
			auto index = (star->getRow() + number - 1)*STAR_WEDTH + star->getCol();
			m_stars[index]->setCan(true);
			number--;
		}
	}
}


void GameScene::isChecked()
{
	for (auto i = 0; i < 100; i++)
	{
		if (m_stars[i] &&m_stars[i]->getRemove())
		{
			auto number = m_stars[i]->getIndex();
			switch (number)
			{
			case 1:
			{
				texture = Director::getInstance()->getTextureCache()->addImage("red_heart.png");

				break;
			}
			case 2:
			{
				texture = Director::getInstance()->getTextureCache()->addImage("blue_heart.png");

				break;
			}
			case 3:
			{

				texture = Director::getInstance()->getTextureCache()->addImage("orange_heart.png");

				break;
			}
			case 4:
			{
				texture = Director::getInstance()->getTextureCache()->addImage("purple_heart.png");


				break;
			}
			case 5:
			{
				texture = Director::getInstance()->getTextureCache()->addImage("green_heart.png");


				break;
			}
			default:
				break;
			}
			m_stars[i]->setTexture(texture);
		}

	}
	isCheck = true;
}