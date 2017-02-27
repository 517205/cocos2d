#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
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
	this->addChild(player,1);
	
	/*
	enemy=Sprite::create("enemy20x20.png");
	enemy->setPosition(Point(.8*x,.8*y));
	this->addChild(enemy,1);
	
	auto func=CallFuncN::create(CC_CALLBACK_1(GameScene::enemymove,this));
	enemy->runAction(Sequence::create(func,NULL));
	*/
	this->schedule(schedule_selector(GameScene::updata));
	
	SimpleAudioEngine *engine=SimpleAudioEngine::getInstance();
	engine->preloadBackgroundMusic("music/gamemusic.mp3");
	engine->preloadEffect("music/bomb.wav");
	GameScene::musicplay();
	
	enemyarray=__Array::create();
	enemyarray->retain();
	
	this->schedule(schedule_selector(GameScene::newenemy),1);
	
	
	
	
	
	return true;
}
/*
bool GameScene::iscollision(Point p1,float x1,float y1,Point p2,float x2,float y2)
{
	if(abs(p1.x - p2.x) < x1 + x2 && abs(p1.y - p2.y) < y1 + y2)
    {
        return true;
    }
    return false;
}
*/
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
	/*
	if(GameScene::iscollision(enemy,player))
	{
		isgame=false;
		SimpleAudioEngine::getInstance()->stopBackgroundMusic(); 
		GameScene::gameoversound();
		//this->runAction(Sequence::create(CallFunc::create(this,callfunc_selector(GameScene::gover))));
		//CC_CALLBACk_1(GameScene::gover,this);
		GameScene::endbegin();
	}
	*/
	Ref* obj=NULL;
	CCARRAY_FOREACH(enemyarray,obj)
	{
		auto s=static_cast<Sprite *>(obj);
		if(iscollision(player,s))
		{
			GameScene::endbegin();
		}
		if(s->getPosition().x==-20 && s->getPosition().x==-20)
		{
			enemyarray->removeObject(s);
			score++;
		}
	}
//	MessageBox("b","b");
}
void GameScene::newenemy(float delta)
{
	int xory=rand()%2;
	int lorr=rand()%2;
	double randx,randy;
	double mvx,mvy;
	if(xory==1&&lorr==1)
	{
		randx=0;
		randy=rand()%(int)y;
		mvx=x;
		mvy=0;
	}
	if(xory==0&&lorr==1)
	{
		randx=rand()%(int)x;
		randy=0;
		mvx=0;
		mvy=y;
	}
	if(xory==0&&lorr==0)
	{
		randx=rand()%(int)x;
		randy=y;
		mvx=0;
		mvy=-y;
	}
	if(xory==1&&lorr==0)
	{
		randx=x;
		randy=rand()%(int)y;
		mvx=-x;
		mvy=0;
	}
	
	
	auto enemy=Sprite::create("enemy20x20.png");
	enemy->setPosition(Point(randx,randy));
	enemyarray->addObject(enemy);
	this->addChild(enemy,3);
	auto move=MoveBy::create(2.0,Point(mvx,mvy));
	auto back=MoveTo::create(0.001,Point(-20,-20));
	enemy->runAction(Sequence::create(move,back,NULL));
	
//	MessageBox("a","a");
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
/*
void GameScene::enemymove(Node *pSender)
{
	auto s=(Sprite *)pSender;
	double b=s->getPosition().y;
//	double dy=20;
	
	if(b>y)
	{
		s->setPosition(Point(s->getPosition().x,0));
	}
	
	auto move=MoveBy::create(.5,Point(0,20));
	auto func=CallFuncN::create(CC_CALLBACK_1(GameScene::enemymove,this));
	s->runAction(Sequence::create(move,func,NULL));
	
	
}
*/
void GameScene::menu(Ref* pSender)
{
	auto d=Director::getInstance();
	d->stopAnimation();
	auto s=d->getWinSize();
	mb->setEnabled(false);
	
	lm=LayerColor::create(Color4B(0,0,255,127),200,150);
	lm->ignoreAnchorPointForPosition(false);
	lm->setPosition(Point(s.width/2,s.height/2));
	this->addChild(lm,2);
	
	auto labeltitle=Label::createWithTTF("GAME IS PAUSED","fonts/lucida_console.ttf",24);
	labeltitle->setPosition(Point(100,120));
	lm->addChild(labeltitle,3);
	
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
void GameScene::endbegin()
{
//	MessageBox("%d","you score");
	log("\nyou score:\n",score);
	Director::getInstance()->replaceScene(HelloWorld::createScene());
//	GameScene::gover(scene);
//	this->runAction(Sequence::create(CallFunc::create(this,callfunc_selector(GameScene::gover)),NULL));
}
void GameScene::gover(Ref* pSender)
{
	auto d=Director::getInstance();
	d->stopAnimation();
	auto s=d->getWinSize();
	mb->setEnabled(false);
	
	lover=LayerColor::create(Color4B(0,0,255,127),200,150);
	lover->ignoreAnchorPointForPosition(false);
	lover->setPosition(Point(s.width/2,s.height/2));
	this->addChild(lover,2);
	
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
	lm->addChild(mm,3);
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
	enemyarray->release();
    Director::getInstance()->replaceScene(HelloWorld::createScene());
}

