/*
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//#include <windows.h>
#define KEY_DOWN(vk_code) (GetAsyncKeyState(vk_code) & 0x8000 ? 1 : 0)
#define KEY_UP(vk_code) (GetAsyncKeyState(vk_code) & 0x8000 ? 0 : 1)
#endif
*/

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
const int youspeed=200;
int weaponlevel=1;
int bomb=3;
int life=3;
Scene* GameScene::createScene()
{
	weaponlevel=1;
	bomb=3;
	life=3;
	auto scene=Scene::create();
	auto layer=GameScene::create();
	scene->addChild(layer);
	return scene;
}
bool GameScene::init()
{
	if(!Layer::init())
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
	
	auto ib=MenuItemImage::create("back.png","back.png");
	ib->setTarget(this,menu_selector(GameScene::menu));
	mb=Menu::create(ib,NULL);
	mb->alignItemsVertically();
	mb->setPosition(Point(15,s.height-15));	
	this->addChild(mb,5);
	
	auto lbomb=LabelTTF::create("bomb","Arial",22);
	auto ibomb=MenuItemLabel::create(lbomb,this,menu_selector(GameScene::releasebomb));
	auto mbomb=Menu::create(ibomb,NULL);
	mbomb->alignItemsVertically();
	mbomb->setPosition(Point(x-40,20));
	this->addChild(mbomb,5);
	
	
	
	player=Sprite::create("player20x20.png");
	player->setPosition(Point(.5*x,.5*y-100));
	this->addChild(player,2);
	
	timelabel=LabelAtlas::create("0123456789","fonts/myttf_cmd_48x54_number.png",48,54,'0');
	timelabel->setPosition(Point(x-50,y-80+50));
	timelabel->setString("0");
	timelabel->setScale(.5);
	this->addChild(timelabel,1);
	
	bomblabel=LabelAtlas::create("0123456789","fonts/myttf_cmd_48x54_number.png",48,54,'0');
	bomblabel->setPosition(Point(x-50,y-80+20));
	bomblabel->setString("3");
	bomblabel->setScale(.5);
	this->addChild(bomblabel,1);
	
	lifelabel=LabelAtlas::create("0123456789","fonts/myttf_cmd_48x54_number.png",48,54,'0');
	lifelabel->setPosition(Point(x-50,y-80-10));
	lifelabel->setString("3");
	lifelabel->setScale(.5);
	this->addChild(lifelabel,1);
	/*
	scorelabel=LabelAtlas::create("0123456789","fonts/myttf_cmd_48x54_number.png",48,54,'0');
	scorelabel->setPosition(Point(x-50-20,y-80-30));
	scorelabel->setString("0");
	scorelabel->setScale(.6);
	this->addChild(scorelabel,0);
	*/
	this->schedule(schedule_selector(GameScene::timer),1.0f);
	this->schedule(schedule_selector(GameScene::shoot),0.25f);
	this->schedule(schedule_selector(GameScene::updata),.05f);
	this->schedule(schedule_selector(GameScene::enemyshoot),1.0f);
	this->schedule(schedule_selector(GameScene::bg),1.0f);
	
	SimpleAudioEngine *engine=SimpleAudioEngine::getInstance();
	engine->preloadBackgroundMusic("music/gamemusic.mp3");
	GameScene::musicplay();
	
	
	auto dispatcher=Director::getInstance()->getEventDispatcher();
	auto touchlistener=EventListenerTouchOneByOne::create();
	touchlistener->onTouchBegan=CC_CALLBACK_2(GameScene::playertouch,this);
	touchlistener->onTouchMoved=CC_CALLBACK_2(GameScene::empty,this);
	touchlistener->onTouchEnded=CC_CALLBACK_2(GameScene::empty,this);
	dispatcher->addEventListenerWithSceneGraphPriority(touchlistener,this);
	
	playerbullet=__Array::create();
	playerbullet->retain();
	enemybullet=__Array::create();
	enemybullet->retain();
	enemy=__Array::create();
	enemy->retain();
	
	GameScene::newboss();
	bosslife=30;
	isboss=true;
	
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
void GameScene::notimmume()
{
	isimmume=false;
}
/*
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
*/
void GameScene::updata(float delta)
{
	if(!isgame) return;
	
	Ref* obj=NULL;
	CCARRAY_FOREACH(playerbullet,obj)
	{
		auto s=static_cast<Sprite *>(obj);
		if(s->getPosition().y>640)
		{
			playerbullet->removeObject(s);
			s->removeFromParent();
		}
	}
	CCARRAY_FOREACH(playerbullet,obj)
	{
		auto b=static_cast<Sprite *>(obj);
		CCARRAY_FOREACH(enemy,obj)
		{
			auto e=static_cast<Sprite *>(obj);
			if(iscollision(e,b))
			{
				GameScene::blast(e->getPosition().x,e->getPosition().y);
				enemy->removeObject(e);
				playerbullet->removeObject(e);
				e->removeFromParent();
				b->removeFromParent();
			}
		}
		
	}
//	log("1");
	auto temp1=__Array::create();
	CCARRAY_FOREACH(enemybullet,obj)
	{
//		log("2");
		auto s=static_cast<Sprite *>(obj);
//		log("3");
		if(s->getPosition().y<0 || s->getPosition().y>640 || s->getPosition().x>400 || s->getPosition().x<0)
		{
//			log("4");
			
//			enemybullet->removeObject(s);
//			log("5");
			s->removeFromParent();
			temp1->addObject(s);
//			log("6");
		}
//		log("7");
	}
	CCARRAY_FOREACH(temp1,obj)
	{
		auto ss=static_cast<Sprite *>(obj);
		enemybullet->removeObject(ss);
	}
//	log("8");
	if(!isimmume)
	{
		if(isboss)
		{
			if(iscollision(boss,player))
			{
				GameScene::die();
				GameScene::blast(player->getPosition().x,player->getPosition().y);
			}
		}
		
		
		CCARRAY_FOREACH(enemybullet,obj)
		{
			auto s=static_cast<Sprite *>(obj);
			if(iscollision(player,s))
			{
				enemybullet->removeObject(s);
				s->removeFromParent();
				GameScene::die();
				GameScene::blast(player->getPosition().x,player->getPosition().y);
			}
		}
		
	}
	
	if(isboss)
	{
		CCARRAY_FOREACH(playerbullet,obj)
		{
			auto s=static_cast<Sprite *>(obj);
			if(iscollision(s,boss))
			{
				bosslife--;
				playerbullet->removeObject(s);
				s->removeFromParent();
			}
		}
	
		if(bosslife<0)
		{
			GameScene::blast(boss->getPosition().x,boss->getPosition().y);
			boss->removeFromParent();
			isboss=false;
			this->runAction(Sequence::create(DelayTime::create(.5),CallFunc::create(this,callfunc_selector(GameScene::win)),NULL));
		}
	}
	////////////////////////////////////////////
	/*
	#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	if(KEY_DOWN(VK_LEFT))
	{
		CCLog("left-----------");
	}
	if(KEY_DOWN(VK_DOWN))
	{
		CCLog("down-----------");
	}
	#endif
	*/
}
void GameScene::timer(float delta)
{
	gametime++;
	char tt[20];
	sprintf(tt,"%d",gametime);
	timelabel->setString(tt);
}
void GameScene::enemyshoot(float delta)
{
	if(isboss)
	{
		auto bullet0=Sprite::create("enemybullet15x15.png");
		bullet0->setPosition(boss->getPosition());
		bullet0->runAction(MoveBy::create(4.0,Point(0,600)));
		this->addChild(bullet0,3);
		enemybullet->addObject(bullet0);
		
		auto bullet2=Sprite::create("enemybullet15x15.png");
		bullet2->setPosition(boss->getPosition());
		bullet2->runAction(MoveBy::create(4.0,Point(0,-600)));
		this->addChild(bullet2,3);
		enemybullet->addObject(bullet2);
		
		auto bullet3=Sprite::create("enemybullet15x15.png");
		bullet3->setPosition(boss->getPosition());
		bullet3->runAction(MoveBy::create(4.0,Point(600,0)));
		this->addChild(bullet3,3);
		enemybullet->addObject(bullet3);
		
		auto bullet4=Sprite::create("enemybullet15x15.png");
		bullet4->setPosition(boss->getPosition());
		bullet4->runAction(MoveBy::create(4.0,Point(-600,0)));
		this->addChild(bullet4,3);
		enemybullet->addObject(bullet4);
		
		auto bullet5=Sprite::create("enemybullet15x15.png");
		bullet5->setPosition(boss->getPosition());
		bullet5->runAction(MoveBy::create(5.0,Point(-600,-600)));
		this->addChild(bullet5,3);
		enemybullet->addObject(bullet5);
		
		auto bullet6=Sprite::create("enemybullet15x15.png");
		bullet6->setPosition(boss->getPosition());
		bullet6->runAction(MoveBy::create(5.0,Point(600,-600)));
		this->addChild(bullet6,3);
		enemybullet->addObject(bullet6);
	}
	Ref* obj=NULL;
	CCARRAY_FOREACH(enemy,obj)
	{
		auto s=static_cast<Sprite *>(obj);
		auto b=Sprite::create("enemybullet15x15.png");
		b->setPosition(s->getPosition());
		
	}
	
	
	
}
void GameScene::bg(float delta)
{
	auto b1=Sprite::create("bg.png");
	double x=rand()%400;
	b1->setPosition(Point(x,700));
	b1->runAction(Sequence::create(MoveBy::create(5+rand()%4,Point(0,-800)),CallFuncN::create(this,callfuncN_selector(GameScene::rm)),NULL));
	this->addChild(b1,0);
}
void GameScene::shoot(float delta)
{
	if(weaponlevel>3) weaponlevel=3;
	if(weaponlevel==1)
	{
		auto bullet=Sprite::create("playerbullet10x10.png");
		bullet->setPosition(player->getPosition());
		bullet->runAction(MoveBy::create(1.0,Point(0,650)));
		this->addChild(bullet,3);
		playerbullet->addObject(bullet);
	}
	if(weaponlevel==2)
	{
		auto bullet=Sprite::create("playerbullet10x10.png");
		bullet->setPosition(player->getPosition());
		bullet->runAction(MoveBy::create(1.0,Point(0,650)));
		this->addChild(bullet,3);
		playerbullet->addObject(bullet);
		auto bullet2=Sprite::create("playerbullet10x10.png");
		bullet2->setPosition(player->getPosition());
		bullet2->runAction(MoveBy::create(1.0,Point(-75,650)));
		this->addChild(bullet2,3);
		playerbullet->addObject(bullet2);
		auto bullet3=Sprite::create("playerbullet10x10.png");
		bullet3->setPosition(player->getPosition());
		bullet3->runAction(MoveBy::create(1.0,Point(75,650)));
		this->addChild(bullet3,3);
		playerbullet->addObject(bullet3);
	}
	if(weaponlevel==3)
	{
		auto bullet=Sprite::create("playerbullet10x10.png");
		bullet->setPosition(player->getPosition());
		bullet->runAction(MoveBy::create(1.0,Point(0,650)));
		this->addChild(bullet,3);
		playerbullet->addObject(bullet);
		auto bullet2=Sprite::create("playerbullet10x10.png");
		bullet2->setPosition(player->getPosition());
		bullet2->runAction(MoveBy::create(1.0,Point(-75,650)));
		this->addChild(bullet2,3);
		playerbullet->addObject(bullet2);
		auto bullet3=Sprite::create("playerbullet10x10.png");
		bullet3->setPosition(player->getPosition());
		bullet3->runAction(MoveBy::create(1.0,Point(75,650)));
		this->addChild(bullet3,3);
		playerbullet->addObject(bullet3);
		auto bullet4=Sprite::create("playerbullet10x10.png");
		bullet4->setPosition(player->getPosition());
		bullet4->runAction(MoveBy::create(1.0,Point(-160,650)));
		this->addChild(bullet4,3);
		playerbullet->addObject(bullet4);
		auto bullet5=Sprite::create("playerbullet10x10.png");
		bullet5->setPosition(player->getPosition());
		bullet5->runAction(MoveBy::create(1.0,Point(160,650)));
		this->addChild(bullet5,3);
		playerbullet->addObject(bullet5);
	}
}
void GameScene::releasebomb(Ref* pSender)
{
	if(bomb==0) return;
	bomb--;
	char tt[20];
	sprintf(tt,"%d",bomb);
	bomblabel->setString(tt);
	Ref* obj=NULL;
	auto temp1=__Array::create();
	CCARRAY_FOREACH(enemybullet,obj)
	{
		log("1");
		auto s=static_cast<Sprite *>(obj);
		log("2");
	//	printf("%lf\n\n",s->getPosition().x);
		GameScene::blast(s->getPosition().x,s->getPosition().y);
		log("3");
	//	enemybullet->removeObject(s);
		log("4");
		s->removeFromParent();
		temp1->addObject(s);
		log("5");
	}
	CCARRAY_FOREACH(temp1,obj)
	{
		auto ss=static_cast<Sprite *>(obj);
		enemybullet->removeObject(ss);
	}
	for(int i=0;i<=x;i+=30)
	{
		for(int j=0;j<=90;j+=30)
		{
			auto b=Sprite::create("playerbullet10x10.png");
			playerbullet->addObject(b);
			b->setPosition(Point(i,j));
			b->runAction(MoveBy::create(1.0,Point(0,650)));
			this->addChild(b,3);
		}
	}
	
}
void GameScene::newenemy()
{
	auto sp=Sprite::create("enemy20x20.png");
	sp->setPosition(Point(rand()%400,640));
	auto a1=MoveBy::create(8.0,Point(0,650));
	auto a2=RepeatForever::create(Sequence::create(MoveBy::create(1.0,Point(-150,0)),MoveBy::create(1.0,Point(150,0)),NULL));
	sp->runAction(a1);
	sp->runAction(a2);
	this->addChild(sp,3);
	enemy->addObject(sp);
}
void GameScene::newboss()
{
	boss=Sprite::create("enemy80x40.png");
	boss->setPosition(Point(x/2+150,y/2+200));
	
	auto left=MoveBy::create(4.0,Point(-300,0));
	auto right=MoveBy::create(4.0,Point(300,0));
	auto seq=Sequence::create(left,right,NULL);
	boss->runAction(RepeatForever::create(seq));
	
	this->addChild(boss,2);
}
void GameScene::die()
{
	if(life==0)
	{
		isgame=false;
		this->runAction(Sequence::create(DelayTime::create(.7),CallFunc::create(this,callfunc_selector(GameScene::gover)),NULL));
		return;
	}
	life--;
	char tt[20];
	sprintf(tt,"%d",life);
	lifelabel->setString(tt);
	player->runAction(Blink::create(1.0,4));
	isimmume=true;
	auto seq=Sequence::create(DelayTime::create(1.0),CallFunc::create(this,callfunc_selector(GameScene::notimmume)),NULL);
	this->runAction(seq);
}
void GameScene::blast(double x,double y)
{
	auto b1=Sprite::create("blast10x10.png");
	auto b2=Sprite::create("blast10x10.png");
	auto b3=Sprite::create("blast10x10.png");
	auto b4=Sprite::create("blast10x10.png");
	auto b5=Sprite::create("blast10x10.png");
	b1->setPosition(Point(x,y));
	b2->setPosition(Point(x,y));
	b3->setPosition(Point(x,y));
	b4->setPosition(Point(x,y));
	b5->setPosition(Point(x,y));
	b1->runAction(Sequence::create(MoveBy::create(.8,Point(30,25)),CallFuncN::create(this,callfuncN_selector(GameScene::rm)),NULL));
	b2->runAction(Sequence::create(MoveBy::create(.8,Point(25,-25)),CallFuncN::create(this,callfuncN_selector(GameScene::rm)),NULL));
	b3->runAction(Sequence::create(MoveBy::create(.8,Point(-25,20)),CallFuncN::create(this,callfuncN_selector(GameScene::rm)),NULL));
	b4->runAction(Sequence::create(MoveBy::create(.8,Point(-20,-10)),CallFuncN::create(this,callfuncN_selector(GameScene::rm)),NULL));
	b5->runAction(Sequence::create(MoveBy::create(.8,Point(-10,-25)),CallFuncN::create(this,callfuncN_selector(GameScene::rm)),NULL));
	this->addChild(b1,2);
	this->addChild(b2,2);
	this->addChild(b3,2);
	this->addChild(b4,2);
	this->addChild(b5,2);
}
void GameScene::rm(Node *sp)
{
	sp->removeFromParent();
}
void GameScene::menu(Ref* pSender)
{
	auto d=Director::getInstance();
	d->pause();
	auto s=d->getWinSize();
	mb->setEnabled(false);
	lm=LayerColor::create(Color4B(0,0,255,127),200,150);
	lm->ignoreAnchorPointForPosition(false);
	lm->setPosition(Point(s.width/2,s.height/2));
	this->addChild(lm,5);
	auto labeltitle=LabelTTF::create("GAME IS PAUSED","Arial",24);
	labeltitle->setPosition(Point(100,120));
	lm->addChild(labeltitle,6);
	auto lb=LabelTTF::create("back to main menu","Arial",18);
	auto ib=MenuItemLabel::create(lb,this,menu_selector(GameScene::back));
	auto lr=LabelTTF::create("resume game","Arial",18);
	auto ir=MenuItemLabel::create(lr,this,menu_selector(GameScene::resume));
	auto mm=Menu::create(ib,ir,NULL);
	
	
	mm->alignItemsVerticallyWithPadding(15);
	mm->setPosition(Point(100,60));
	lm->addChild(mm,3);
	
}
void GameScene::gover()
{
	isgame=false;
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	auto d=Director::getInstance();
	d->pause();
	auto s=d->getWinSize();
	mb->setEnabled(false);
	lover=LayerColor::create(Color4B(0,0,255,127),200,150);
	lover->ignoreAnchorPointForPosition(false);
	lover->setPosition(Point(s.width/2,s.height/2));
	this->addChild(lover,6);
	auto labeltitle=LabelTTF::create("GAME OVER","Arial",24);
	labeltitle->setPosition(Point(100,120));
	lover->addChild(labeltitle,3);
	
	auto lb=LabelTTF::create("back to main menu","Arial",18);
	auto ib=MenuItemLabel::create(lb,this,menu_selector(GameScene::back));
	auto lr=LabelTTF::create("restart game","Arial",18);
	auto ir=MenuItemLabel::create(lr,this,menu_selector(GameScene::restart));
	auto mm=Menu::create(ib,ir,NULL);
	
	mm->alignItemsVerticallyWithPadding(15);
	mm->setPosition(Point(100,60));
	lover->addChild(mm,3);
	log("game over");
}
void GameScene::win()
{
	isgame=false;
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	auto d=Director::getInstance();
	d->pause();
	auto s=d->getWinSize();
	mb->setEnabled(false);
	lwin=LayerColor::create(Color4B(0,0,255,127),200,150);
	lwin->ignoreAnchorPointForPosition(false);
	lwin->setPosition(Point(s.width/2,s.height/2));
	this->addChild(lwin,6);
	auto labeltitle=LabelTTF::create("YOU WIN","Arial",24);
	labeltitle->setPosition(Point(100,120));
	lwin->addChild(labeltitle,3);
	
	auto lb=LabelTTF::create("back to main menu","Arial",18);
	auto ib=MenuItemLabel::create(lb,this,menu_selector(GameScene::back));
	auto lr=LabelTTF::create("replay game","Arial",18);
	auto ir=MenuItemLabel::create(lr,this,menu_selector(GameScene::restart));
	auto mm=Menu::create(ib,ir,NULL);
	
	mm->alignItemsVerticallyWithPadding(15);
	mm->setPosition(Point(100,60));
	lwin->addChild(mm,3);
	log("you win");
}
/*
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
*/
void GameScene::musicplay()
{
	auto engine=SimpleAudioEngine::getInstance();
	engine->stopBackgroundMusic(); 
	if(music)
	{
		engine->playBackgroundMusic("music/gamemusic.mp3",true);
	}
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
	move->setTag(5);
//	player->stopAllActions();
	player->stopActionByTag(5);
	player->runAction(move);
	return true;
}
void GameScene::endbegin()
{
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}
void GameScene::resume(Ref* pSender)
{
	auto d=Director::getInstance();
	d->resume();
	mb->setEnabled(true);
	lm->removeFromParentAndCleanup(true);
}
void GameScene::restart(Ref* pSender)
{
	auto d=Director::getInstance();
	d->resume();
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    Director::getInstance()->replaceScene(GameScene::createScene());
}

void GameScene::back(Ref* pSender)
{
	
	auto d=Director::getInstance();
	d->resume();
	GameScene::endbegin();
}

