#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include"GameScene.h"
#include"HelloWorldScene.h"
#include<cmath>
#include<ctime>
USING_NS_CC;
using namespace cocos2d;
using namespace CocosDenshion;
extern bool music;
extern bool sound;
extern int score;
extern int gametime;
const int v=150;
const int youspeed=120;
Scene* GameScene::createScene()
{
	auto scene=Scene::create();
	auto layer=GameScene::create();
	scene->addChild(layer);
	return scene;
}
bool GameScene::init()
{
	if(!Layer::init()/*WithColor(Color4B(255,0,0, 255))*/)
    {
        return false;
    }
    srand((unsigned)time(0));
    score=0;
	gametime=0;
    anode=Node::create();
	this->addChild(anode,0);
	auto s=Director::getInstance()->getWinSize();
	x=s.width;
	y=s.height;
	
	auto lb=Label::createWithTTF("<","fonts/lucida_console.ttf",22);
	auto ib=MenuItemLabel::create(lb,this,menu_selector(GameScene::menu));
	mb=Menu::create(ib,NULL);
	mb->alignItemsVertically();
	mb->setPosition(Point(15,s.height-15));	
	this->addChild(mb,5);
	
	auto iright=MenuItemImage::create("ctrpanel/right.png","ctrpanel/right.png");
	iright->setTarget(this,menu_selector(GameScene::right));
	iright->setPosition(Point(x-20,30));
	auto idown=MenuItemImage::create("ctrpanel/down.png","ctrpanel/down.png");
	idown->setTarget(this,menu_selector(GameScene::down));
	idown->setPosition(Point(x-40,10));
	auto ileft=MenuItemImage::create("ctrpanel/left.png","ctrpanel/left.png");
	ileft->setTarget(this,menu_selector(GameScene::left));
	ileft->setPosition(Point(x-60,30));
	auto iup=MenuItemImage::create("ctrpanel/up.png","ctrpanel/up.png");
	iup->setTarget(this,menu_selector(GameScene::up));
	iup->setPosition(Point(x-40,50));
	auto menupanel=Menu::create(iright,idown,ileft,iup,NULL);
	menupanel->setPosition(Point::ZERO);
	menupanel->setAnchorPoint(Point(0,0));
	this->addChild(menupanel,5);
	
	player=Sprite::create("player20x20.png");
	player->setPosition(Point(.5*x,.5*y));
	this->addChild(player,2);
	
	timelabel=LabelAtlas::create("0123456789","fonts/myttf_cmd_48x54_number.png",48,54,'0');
	timelabel->setPosition(Point(x-50-20,y-80+30));
	timelabel->setString("0");
	timelabel->setScale(.75);
	this->addChild(timelabel,0);
	
	scorelabel=LabelAtlas::create("0123456789","fonts/myttf_cmd_48x54_number.png",48,54,'0');
	scorelabel->setPosition(Point(x-50-20,y-80-30));
	scorelabel->setString("0");
	scorelabel->setScale(.75);
	this->addChild(scorelabel,0);
	
	this->schedule(schedule_selector(GameScene::updata));
	this->schedule(schedule_selector(GameScene::timer),1.0f);
	
	SimpleAudioEngine *engine=SimpleAudioEngine::getInstance();
	engine->preloadBackgroundMusic("music/gamemusic.mp3");
	engine->preloadEffect("music/bomb.wav");
	engine->preloadEffect("music/getfood.wav");
	GameScene::musicplay();
	
	enemyarray=__Array::create();
	enemyarray->retain();
	foodarray=__Array::create();
	foodarray->retain();
	
	this->schedule(schedule_selector(GameScene::newenemy),.5);
	this->schedule(schedule_selector(GameScene::newfood),.5);
	
	auto dispatcher=Director::getInstance()->getEventDispatcher();
	auto touchlistener=EventListenerTouchOneByOne::create();
	touchlistener->onTouchBegan=CC_CALLBACK_2(GameScene::playertouch,this);
	touchlistener->onTouchMoved=CC_CALLBACK_2(GameScene::empty,this);
	touchlistener->onTouchEnded=CC_CALLBACK_2(GameScene::empty,this);
	dispatcher->addEventListenerWithSceneGraphPriority(touchlistener,this);
	
	
	
	
	
	return true;
}
void GameScene::empty(Touch *touch,Event *pEvent)
{
}
bool GameScene::playertouch(Touch *touch,Event *pEvent)
{
	Point touchlocation=touch->getLocation();
	Point gotopoint=this->convertToNodeSpace(touchlocation);
	Point initpoint=player->getPosition();
	float gototime;
	float distance=sqrt((gotopoint.x-initpoint.x)*(gotopoint.x-initpoint.x)+(gotopoint.y-initpoint.y)*(gotopoint.y-initpoint.y));
	gototime=distance/youspeed;
	
	auto move=MoveTo::create(gototime,gotopoint);
	player->stopAllActions();
	player->runAction(move);
	return true;
}
bool GameScene::iscollision(Sprite *s1,Sprite *s2)
{
	if(s1->boundingBox().intersectsRect(s2->boundingBox()))
    {
        return true;
    }
    return false;
}
void GameScene::updata(float delta)
{
	if(!isgame)
	{
		return;
	}
	Ref* obj=NULL;
	CCARRAY_FOREACH(enemyarray,obj)
	{
		auto s=static_cast<Sprite *>(obj);
		if(iscollision(player,s))
		{
			if(isgame)
			{
				GameScene::gover();
			}
		}
		if(s->getPosition().x==-20 && s->getPosition().x==-20)
		{
			enemyarray->removeObject(s);
			s->removeFromParent();
		}
	}
	CCARRAY_FOREACH(foodarray,obj)
	{
		auto s=static_cast<Sprite *>(obj);
		if(s->getPosition().x==-20 && s->getPosition().x==-20)
		{
			foodarray->removeObject(s);
		}
		if(iscollision(player,s))
		{
			foodarray->removeObject(s);
			GameScene::getfoodsound();
			s->removeFromParent();
			
			score++;
			char tt[20];
			sprintf(tt,"%d",score);
			scorelabel->setString(tt);
		}
	}
}
void GameScene::newenemy(float delta)
{
	int xory=rand()%2;
	int lorr=rand()%2;
	double randx,randy;
	double mvx,mvy;
	double ttime;
	if(xory==1&&lorr==1)
	{
		randx=0;
		randy=rand()%(int)y;
		mvx=x;
		mvy=0;
		ttime=x/v;
	}
	if(xory==0&&lorr==1)
	{
		randx=rand()%(int)x;
		randy=0;
		mvx=0;
		mvy=y;
		ttime=y/v;
	}
	if(xory==0&&lorr==0)
	{
		randx=rand()%(int)x;
		randy=y;
		mvx=0;
		mvy=-y;
		ttime=y/v;
	}
	if(xory==1&&lorr==0)
	{
		randx=x;
		randy=rand()%(int)y;
		mvx=-x;
		mvy=0;
		ttime=x/v;
	}
	auto enemy=Sprite::create("enemy20x20.png");
	enemy->setPosition(Point(randx,randy));
	enemyarray->addObject(enemy);
	this->addChild(enemy,3);
	auto move=MoveBy::create(ttime,Point(mvx,mvy));
	auto back=MoveTo::create(0.0000001,Point(-20,-20));
	enemy->runAction(Sequence::create(move,back,NULL));
//	MessageBox("a","a");
}
void GameScene::newfood(float delta)
{
	int xory=rand()%2;
	int lorr=rand()%2;
	double randx,randy;
	double mvx,mvy;
	double ttime;
	if(xory==1&&lorr==1)
	{
		randx=0;
		randy=rand()%(int)y;
		mvx=x;
		mvy=0;
		ttime=x/v;
	}
	if(xory==0&&lorr==1)
	{
		randx=rand()%(int)x;
		randy=0;
		mvx=0;
		mvy=y;
		ttime=y/v;
	}
	if(xory==0&&lorr==0)
	{
		randx=rand()%(int)x;
		randy=y;
		mvx=0;
		mvy=-y;
		ttime=y/v;
	}
	if(xory==1&&lorr==0)
	{
		randx=x;
		randy=rand()%(int)y;
		mvx=-x;
		mvy=0;
		ttime=x/v;
	}
	auto food=Sprite::create("food10x10.png");
	food->setPosition(Point(randx,randy));
	foodarray->addObject(food);
	this->addChild(food,3);
	auto move=MoveBy::create(ttime,Point(mvx,mvy));
	auto back=MoveTo::create(0.0000001,Point(-20,-20));
	food->runAction(Sequence::create(move,back,NULL));
}
void GameScene::timer(float delta)
{
	gametime++;
	char tt[20];
	sprintf(tt,"%d",gametime);
	timelabel->setString(tt);
	sprintf(tt,"%d",score);
	scorelabel->setString(tt);
}
void GameScene::up(Ref* pSender)
{
	double a=player->getPosition().x;
	double b=player->getPosition().y+20;
	auto move=MoveTo::create(.3,Point(a,b));
	player->runAction(move);
}
void GameScene::down(Ref* pSender)
{
	double a=player->getPosition().x;
	double b=player->getPosition().y-20;
	auto move=MoveTo::create(.3,Point(a,b));
	player->runAction(move);
}
void GameScene::left(Ref* pSender)
{
	double a=player->getPosition().x-20;
	double b=player->getPosition().y;
	auto move=MoveTo::create(.3,Point(a,b));
	player->runAction(move);
}
void GameScene::right(Ref* pSender)
{
	double a=player->getPosition().x+20;
	double b=player->getPosition().y;
	auto move=MoveTo::create(.3,Point(a,b));
	player->runAction(move);
}

void GameScene::menu(Ref* pSender)
{
	auto d=Director::getInstance();
	d->stopAnimation();
	auto s=d->getWinSize();
	mb->setEnabled(false);
	lm=LayerColor::create(Color4B(0,0,255,127),200,150);
	lm->ignoreAnchorPointForPosition(false);
	lm->setPosition(Point(s.width/2,s.height/2));
	this->addChild(lm,5);
	auto labeltitle=Label::createWithTTF("GAME IS PAUSED","fonts/lucida_console.ttf",24);
	labeltitle->setPosition(Point(100,120));
	lm->addChild(labeltitle,6);
	auto lb=Label::createWithTTF("back to main menu","fonts/lucida_console.ttf",18);
	auto ib=MenuItemLabel::create(lb,this,menu_selector(GameScene::back));
	auto lr=Label::createWithTTF("resume game","fonts/lucida_console.ttf",18);
	auto ir=MenuItemLabel::create(lr,this,menu_selector(GameScene::resume));
	auto mm=Menu::create(ib,ir,NULL);
	
	
	mm->alignItemsVerticallyWithPadding(15);
	mm->setPosition(Point(100,60));
	lm->addChild(mm,3);
	
}


void GameScene::musicplay()
{
	auto engine=SimpleAudioEngine::getInstance();
	engine->stopBackgroundMusic(); 
	if(music)
	{
		engine->playBackgroundMusic("music/gamemusic.mp3",true);
	}
}
void GameScene::gameoversound()
{
	auto engine=SimpleAudioEngine::getInstance();
	if(sound)
	{
		engine->playEffect("music/bomb.wav");
	}
}
void GameScene::getfoodsound()
{
	auto engine=SimpleAudioEngine::getInstance();
	if(sound)
	{
		engine->playEffect("music/getfood.wav");
	}
}
void GameScene::endbegin()
{
	Director::getInstance()->replaceScene(HelloWorld::createScene());
//	GameScene::gover();
}
void GameScene::gover()
{
	isgame=false;
	GameScene::gameoversound();
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	auto d=Director::getInstance();
	d->stopAnimation();
	auto s=d->getWinSize();
	mb->setEnabled(false);
	lover=LayerColor::create(Color4B(0,0,255,127),200,150);
	lover->ignoreAnchorPointForPosition(false);
	lover->setPosition(Point(s.width/2,s.height/2));
	this->addChild(lover,6);
	auto labeltitle=Label::createWithTTF("GAME OVER","fonts/lucida_console.ttf",24);
	labeltitle->setPosition(Point(100,120));
	lover->addChild(labeltitle,3);
	
	auto lb=Label::createWithTTF("back to main menu","fonts/lucida_console.ttf",18);
	auto ib=MenuItemLabel::create(lb,this,menu_selector(GameScene::back));
	auto lr=Label::createWithTTF("restart game","fonts/lucida_console.ttf",18);
	auto ir=MenuItemLabel::create(lr,this,menu_selector(GameScene::restart));
	auto mm=Menu::create(ib,ir,NULL);
	
	mm->alignItemsVerticallyWithPadding(15);
	mm->setPosition(Point(100,60));
	lover->addChild(mm,3);
	log("game over");
}
void GameScene::resume(Ref* pSender)
{
	auto d=Director::getInstance();
	d->startAnimation();
	mb->setEnabled(true);
	lm->removeFromParentAndCleanup(true);
}
void GameScene::restart(Ref* pSender)
{
	auto d=Director::getInstance();
	d->startAnimation();
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    Director::getInstance()->replaceScene(GameScene::createScene());
}
void GameScene::back(Ref* pSender)
{
	
	auto d=Director::getInstance();
	d->startAnimation();
//	enemyarray->release();
//	foodarray->release();
	GameScene::endbegin();
}

