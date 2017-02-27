#include"GameScene.h"
#include"HelloWorldScene.h"

#include "SimpleAudioEngine.h"
#include<cmath>
USING_NS_CC;
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
    auto anode=Node::create();
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
	/*auto */enemy=Sprite::create("enemy20x20.png");
	enemy->setPosition(Point(.8*x,.8*y));
	this->addChild(enemy,1);
	
	auto func=CallFuncN::create(CC_CALLBACK_1(GameScene::enemymove,this));
	enemy->runAction(Sequence::create(func,NULL));
	this->schedule(schedule_selector(GameScene::updata));
	
	
		
	
	return true;
}
bool GameScene::iscollision(Point p1,float x1,float y1,Point p2,float x2,float y2)
{
//	MessageBox("3#","#");
	if(abs(p1.x - p2.x) < x1 + x2 && abs(p1.y - p2.y) < y1 + y2)
    {
        return true;
    }
    return false;
}
void GameScene::updata(float delta)
{
//	MessageBox("2#","#");
	Ref* obj=NULL;
//	MessageBox("2#","#");
	auto s=static_cast<Sprite *>(obj);
//	MessageBox("2#","#");
	if(GameScene::iscollision(enemy->getPosition(),20,20,player->getPosition(),20,20))
	{
		CC_CALLFUNC_1(GameScene::over);
	}
	
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
void GameScene::menu(Ref* pSender)
{
	auto d=Director::getInstance();
	//d->pause();
//	d->stopAnimation();
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

void GameScene::over(Ref* pSender)
{
	log("game over");
	
}


void GameScene::resume(Ref* pSender)
{
	auto d=Director::getInstance();
	///d->resume();
//	d->startAnimation();
	mb->setEnabled(true);
	
	lm->removeFromParentAndCleanup(true);
	
	
}
void GameScene::back(Ref* pSender)
{
    Director::getInstance()->replaceScene(HelloWorld::createScene());
}

