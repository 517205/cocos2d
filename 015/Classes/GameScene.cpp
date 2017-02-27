#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "extensions/cocos-ext.h"
#include"GameScene.h"
#include"HelloWorldScene.h"
#include "HPSprite.h"
#include<cmath>
#include<ctime>

#include "base/CCUserDefault.h"  
#include "platform/CCCommon.h"  
#include "platform/CCFileUtils.h"  
#define USERDEFAULT_ROOT_NAME    "userDefaultRoot"  
#define XML_FILE_NAME "UserDefault.xml"   
#define SaveStringToXML CCUserDefault::sharedUserDefault()->setStringForKey  
#define SaveIntegerToXML CCUserDefault::sharedUserDefault()->setIntegerForKey  
#define SaveBooleanToXML CCUserDefault::sharedUserDefault()->setBoolForKey  
#define LoadStringFromXML CCUserDefault::sharedUserDefault()->getStringForKey  
#define LoadIntegerFromXML CCUserDefault::sharedUserDefault()->getIntegerForKey  
#define LoadBooleanFromXML CCUserDefault::sharedUserDefault()->getBoolForKey 
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d;
using namespace CocosDenshion;
extern bool music;
extern bool sound;
extern bool console;
extern int money;
extern int wave;
extern int life;
int tsid;//tower selected id
int moveid;
bool isselect=false;//select tower 4 up or sell
bool isgame=true;
Sprite *movingsp;
HPSprite* towersel;
char cmoney[25];
char clife[25];
char cwave[25];
char aaa[50];
int dx[]={0 ,0 ,1 ,-1};
int dy[]={1 ,-1,0 ,0 };
int map[17][12]={
{1,1,1,1,1,901,1,1,1,1,1,1},
{21,0,0,0,0,902,0,0,0,0,0,1},
{1,0,0,0,0,903,0,0,0,0,0,1},
{22,0,0,0,0,904,0,0,0,0,0,1},
{1,0,0,0,0,905,0,0,0,0,0,1},
{23,0,0,0,0,906,907,908,909,0,0,1},
{1,0,0,0,0,0,0,0,910,0,0,1},
{24,0,0,0,0,0,0,0,911,0,0,1},
{1,0,0,0,0,0,0,0,912,0,0,1},
{1,0,0,0,0,0,0,0,913,0,0,1},
{1,0,0,0,0,0,0,0,914,0,0,1},
{1,0,0,920,919,918,917,916,915,0,0,1},
{1,0,0,921,0,0,0,0,0,0,0,1},
{1,0,0,922,0,0,0,0,0,0,0,1},
{1,0,0,923,0,0,0,0,0,0,0,1},
{1,0,0,924,0,0,0,0,0,0,0,1},
{1,1,1,999,1,1,1,1,1,1,1,1}
};
int enemynum[5][10]={
{0},
{0,5,0,0,10,0,0,5,5,0},
{0,0,5,0,0,10,0,5,0,5},
{0,0,0,5,0,0,10,0,5,5},
{1,0,0,0,0,0, 0,0,0,0}
};
int towerlist[5][10]={
{0},
{125,100,100,50,150,70,100,150,350},
{75,150,65,50,150,70,100,150,350},
{175,75,80,50,150,70,100,150,350},
{300,250,200,50,150,70,100,150,350}
};//[id][] cost,range,damage,up2lv2need_rate,up2lv3need_rate,sell_rate,lv1damage_rate,lv2damage_rate,lv3damage_rate
int enemylist[5][10]={
{0},
{100,60,1},
{300,45,2},
{50,100,1},
{5000,35,5},
};//[id][] health,speed,damage
Scene* GameScene::createScene()
{
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
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    if(console)
    {
    	AllocConsole();  
		freopen("CONIN$", "r", stdin);  
		freopen("CONOUT$", "w", stdout);  
		freopen("CONOUT$", "w", stderr);
    }
    #endif
    GameScene::myInit();
	//select
	lselect=LayerColor::create(Color4B(0,255,255,127),120,120);
	lselect->setPosition(Point(-120,-120));
	this->addChild(lselect,10);
	auto iup=MenuItemImage::create("td/up.png","td/up.png");
	iup->setTarget(this,menu_selector(GameScene::towerup));
	iup->setPosition(Point(20,40+20));
	auto isell=MenuItemImage::create("td/sell.png","td/sell.png");
	isell->setTarget(this,menu_selector(GameScene::towersell));
	isell->setPosition(Point(40*2+20,40+20));
	mselect=Menu::create(iup,isell,NULL);
	mselect->setPosition(Point(0,0));
	lselect->addChild(mselect,2);
	tmoneyup=LabelAtlas::create(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~","fonts/mylabel_cmd_9_18.png",10,18,' ');
	tmoneyup->setPosition(Point(0,20));
	tmoneyup->setString("0");
	tmoneyup->setScale(20/18);
	lselect->addChild(tmoneyup,2);
	tmoneysell=LabelAtlas::create(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~","fonts/mylabel_cmd_9_18.png",10,18,' ');
	tmoneysell->setPosition(Point(80,20));
	tmoneysell->setString("0");
	tmoneysell->setScale(20/18);
	lselect->addChild(tmoneysell,2);
	tinfo=LabelAtlas::create(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~","fonts/mylabel_cmd_9_18.png",10,18,' ');
	tinfo->setPosition(Point(0,80));
	tinfo->setString("0");
	tinfo->setScale(20/18);
	lselect->addChild(tinfo,2);
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	SaveIntegerToXML("abc",123);
	SaveStringToXML("adcd","hello");
	int aaa=LoadIntegerFromXML("abc");
	log("%d",aaa);
	
	log("init end");
	return true;
}
void GameScene::towerup(Ref* pSender)
{
	if(towersel->lv!=3)
	{
		GameScene::shownews("Tower up!",1);
		drawnode->clear();
		lselect->setPosition(Point(-120,-120));
		towersel->lv++;
		towersel->damage=(int)towerlist[towersel->id][2]*towerlist[towersel->id][5+towersel->lv]/(double)100;
		towersel->worth+=(int)towerlist[towersel->id][0]*towerlist[towersel->id][1+towersel->lv]/(double)100;
		money-=(int)towerlist[towersel->id][0]*towerlist[towersel->id][1+towersel->lv]/(double)100;
		sprintf(cmoney,"Money:%d",money);
		lmoney->setString(cmoney);
		log("lv=%d:damage=%d,worth=%d",towersel->lv,towersel->damage,towersel->worth);
	}
}
void GameScene::towersell(Ref* pSender)
{
	GameScene::shownews("Tower sold!",1);
	drawnode->clear();
	lselect->setPosition(Point(-120,-120));
	map[towersel->xx][towersel->yy]=0;
	money+=(int)(towersel->worth*towerlist[towersel->id][5]/(double)100);
	sprintf(cmoney,"Money:%d",money);
	lmoney->setString(cmoney);
	tower->removeObject(towersel);
	towersel->main->removeFromParent();
}
void GameScene::updata(float delta)
{
	//tower shoot
	//enemy die
	
	//tower money enough ?
	if(money<125)
		no1->setPosition(Point(40*1+20,20));
	else
		no1->setPosition(Point(-40,-40));
	if(money<75)
		no2->setPosition(Point(40*3+20,20));
	else
		no2->setPosition(Point(-40,-40));
	if(money<175)
		no3->setPosition(Point(40*5+20,20));
	else
		no3->setPosition(Point(-40,-40));
	if(money<300)
		no4->setPosition(Point(40*7+20,20));
	else
		no4->setPosition(Point(-40,-40));
	//judge new wave
	int j=0;
	Ref* obj=NULL;
    CCARRAY_FOREACH(enemy,obj)
	{
		auto s=static_cast<HPSprite *>(obj);
		j++;
	}
	if(j==0)
	{
		wave++;
		sprintf(cwave,"Wave:%d",wave);
		lwave->setString(cwave);
		GameScene::shownews("Next wave coming!",1);
		moveid=0;
		for(int k=1;k<=4;k++)
		{
			if(enemynum[k][wave%10]!=0)
			{
				auto func=CallFuncN::create(CC_CALLBACK_1(GameScene::newenemy,this,k));
				auto rep=Repeat::create(func,enemynum[k][wave%10]);
				this->runAction(rep);
			}
		}
	}
}
void GameScene::shoot(float delta)
{
}
void GameScene::save(Ref* pSender)
{
	
	
}
bool GameScene::playertouch(Touch *touch,Event *pEvent)
{
	Point touchlocation=touch->getLocation();
	Point p=this->convertToNodeSpace(touchlocation);
	int tx=p.x/40;
	int ty=p.y/40;
	//diselect tower
	if(isselect)
	{
		isselect=false;
		lselect->setPosition(Point(-120,-120));
		drawnode->clear();
	}
	//select tower
	if(map[tx][ty]==100)
	{
		isselect=true;
		Ref* obj=NULL;
		CCARRAY_FOREACH(tower,obj)
		{
			auto s=static_cast<HPSprite *>(obj);
			if(s->xx==tx && s->yy==ty)
				towersel=s;
		}
		lselect->setPosition(Point(tx*40+20-60,ty*40+20-60));
		char ttt[50];
		sprintf(ttt,"%d",(int)(towersel->worth*towerlist[towersel->id][5]/(double)100));
		tmoneysell->setString(ttt);
		sprintf(ttt,"tower%d,damage=%d",towersel->id,towersel->damage);
		tinfo->setString(ttt);
		if(towersel->lv!=3)
		{
			sprintf(ttt,"%d",(int)(towerlist[towersel->id][0]*towerlist[towersel->id][2+towersel->lv]/(double)100));
			tmoneyup->setString(ttt);
		}
		else
		{
			tmoneyup->setString("MAX");
		}
		drawnode->drawDot(Point(tx*40+20,ty*40+20),towerlist[towersel->id][1],Color4F(0,1,0,0.4));
	}
	//build tower
	if(map[tx][ty]>20 && map[tx][ty]<=25)
	{
		tsid=map[tx][ty]-20;
		if(towerlist[tsid][0]<=money)
		{
			log("%d:start",tsid);
			char sppath[25];
			sprintf(sppath,"td/tower/tower%d.png",tsid);
			movingsp=Sprite::create(sppath);
			movingsp->setPosition(-40,-40);
			this->addChild(movingsp,10);
		}
		else tsid=0;
	}
	return true;
}
void GameScene::touchmove(Touch *touch,Event *pEvent)
{
	Point touchlocation=touch->getLocation();
	Point p=this->convertToNodeSpace(touchlocation);
//	log("%d move to:%f,%f",tsid,p.x,p.y);
	if(tsid!=0)
	{
		Point p2;
		p2.x=((int)p.x/40)*40+20;
		p2.y=((int)p.y/40)*40+20;
		movingsp->setPosition(p2);
		drawnode->clear();
		if(map[(int)p2.x/40][(int)p2.y/40]==0)
			drawnode->drawDot(p2,towerlist[tsid][1], Color4F(0,1,0,0.4));
		else
			drawnode->drawDot(p2,towerlist[tsid][1], Color4F(1,0,0,0.4));
	}
}
void GameScene::touchend(Touch *touch,Event *pEvent)
{
	Point touchlocation=touch->getLocation();
	Point p=this->convertToNodeSpace(touchlocation);
	int tx=p.x/40;
	int ty=p.y/40;
	if(tsid!=0)
	{
		log("%d drop at:%f,%f",tsid,p.x,p.y);
		movingsp->removeFromParent();
		drawnode->clear();
		if(map[tx][ty]==0)
		{
			money-=towerlist[tsid][0];
			sprintf(cmoney,"Money:%d",money);
			lmoney->setString(cmoney);
			GameScene::shownews("Tower placed!",1);
			GameScene::newtower(tx,ty,tsid);
		}
		else
		{
			GameScene::shownews("Illegal placing",1);
		}
		tsid=0;
	}
}
void GameScene::newenemy(Node* node,int id)
{
	moveid++;
	char t[50];
	sprintf(t,"td/enemy/enemy%d.png",id);
	auto sp=new HPSprite();
	sp->main=Sprite::create(t);
	sp->id=id;
	sp->hp=enemylist[id][0];
	sp->damage=enemylist[id][2];
	sp->speed=enemylist[id][1];
	sp->fromx=0+20-40*moveid;sp->fromy=200+20;
	sp->tox=40+20;sp->toy=200+20;
	sp->hasgone=-40*moveid;
	sp->main->setPosition(Point(0+20-40*moveid,200+20));
	this->addChild(sp->main,3);
	enemy->addObject(sp);
	if(isgame) GameScene::mainmove(this,sp);
}
void GameScene::newtower(int xx,int yy,int id)
{
	map[xx][yy]=100;
	auto tt=new HPSprite();
	char ch[50];
	sprintf(ch,"td/tower/tower%d.png",id);
	tt->main=Sprite::create(ch);
	tt->xx=xx;tt->yy=yy;
	tt->id=id;
	tt->range=towerlist[id][1];
	tt->damage=towerlist[id][2];
	tt->lv=1;
	tt->main->setPosition(Point(xx*40+20,yy*40+20));
	tt->worth=towerlist[id][0];
	this->addChild(tt->main,3);
	tower->addObject(tt);
}
void GameScene::mainmove(Node* node,HPSprite* sp)
{
	//reach
	if(abs(sp->main->getPosition().x-sp->tox)<1e-2 && abs(sp->main->getPosition().y-sp->toy)<1e-2)
	{
		sp->hasgone+=40;
		sp->fromx=sp->tox;sp->fromy=sp->toy;
		int xx=sp->fromx/40;
		int yy=sp->fromy/40;
		if(map[xx][yy]==999)
		{
			double tt=(double)40/sp->speed;
			auto func=CallFuncN::create(CC_CALLBACK_1(GameScene::entry,this,sp));
			sp->main->runAction(Sequence::create(MoveTo::create(tt,Point(sp->fromx+40,sp->fromy)),func,NULL));
		}
		else
		{
			for(int j=0;j<4;j++)
			{
				if(map[xx+dx[j]][yy+dy[j]]>map[xx][yy])
				{
					sp->tox=(xx+dx[j])*40+20;
					sp->toy=(yy+dy[j])*40+20;
					double tt=(double)sqrt((sp->fromx-sp->tox)*(sp->fromx-sp->tox)+(sp->fromy-sp->toy)*(sp->fromy-sp->toy))/sp->speed;
					auto func=CallFuncN::create(CC_CALLBACK_1(GameScene::mainmove,this,sp));
					sp->main->runAction(Sequence::create(MoveTo::create(tt,Point(sp->tox,sp->toy)),func,NULL));
				}
			}
		}
	}
	//not reach
	else
	{
		double tt=(double)sqrt((sp->main->getPosition().x-sp->tox)*(sp->main->getPosition().x-sp->tox)+(sp->main->getPosition().y-sp->toy)*(sp->main->getPosition().y-sp->toy))/sp->speed;
		auto func=CallFuncN::create(CC_CALLBACK_1(GameScene::mainmove,this,sp));
		sp->main->runAction(Sequence::create(MoveTo::create(tt,Point(sp->tox,sp->toy)),func,NULL));
	}
}
void GameScene::entry(Node* node,HPSprite *sp)
{
	life-=sp->damage;
	sprintf(clife,"Life:%d",life);
	llife->setString(clife);
	enemy->removeObject(sp);
	sp->main->removeFromParent();
	
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("td/blast.plist");
	auto blast1= Sprite::createWithSpriteFrameName("blast1.png");
	blast1->setPosition(Point(16*40+20,3*40+20));
	this->addChild(blast1,5);
	
	auto dic=Dictionary::createWithContentsOfFile("td/blast.plist");
	auto framedic=(__Dictionary*)dic->objectForKey("frames");
	int num=framedic->allKeys()->count();
	Vector<SpriteFrame *> allframes;
	for(int i=0;i<num;i++)
	{
		char frame[50];
		sprintf(frame,"blast%d.png",i+1);
		auto framename=SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frame);
		allframes.pushBack(framename);
	}
	auto anim=Animation::createWithSpriteFrames(allframes,.1,1);
	auto anim2=Animate::create(anim);
	blast1->runAction(Sequence::create(anim2,CallFuncN::create(this,callfuncN_selector(GameScene::rm)),NULL));
	
}
void GameScene::pause_resume(Ref* pSender,Control::EventType controlEvent)
{
	auto pSwitch = (ControlSwitch*)pSender;
    if (pSwitch->isOn())//isgame
	{
		isgame=true;
		GameScene::shownews("game is resumed",1);
		Ref* obj=NULL;
    	CCARRAY_FOREACH(enemy,obj)
		{
			auto s=static_cast<HPSprite *>(obj);
			GameScene::mainmove(this,s);
		}
    }
	else//ispause
    {
    	isgame=false;
    	GameScene::shownews("game is paused",0);
    	Ref* obj=NULL;
    	CCARRAY_FOREACH(enemy,obj)
		{
			auto s=static_cast<HPSprite *>(obj);
			s->main->stopAllActions();
		}
    }
    
}
void GameScene::accel(Ref* pSender,Control::EventType controlEvent)
{
	auto pSwitch = (ControlSwitch*)pSender;
	CCScheduler* pScheduler = CCDirector::sharedDirector()->getScheduler();
    if (pSwitch->isOn())//x1
	{
        pScheduler->setTimeScale(1.0f);
    }
	else//x2
    {
        pScheduler->setTimeScale(2.0f);
    }
    
}
void GameScene::myInit()
{
	log("init begin");
    srand((unsigned)time(0));
    anode=Node::create();
	this->addChild(anode,0);
	auto s=Director::getInstance()->getWinSize();
	x=s.width;
	y=s.height;
	
	auto ib=MenuItemImage::create("td/menu.png","td/menu.png");
	ib->setTarget(this,menu_selector(GameScene::menu));
	mb=Menu::create(ib,NULL);
	mb->alignItemsVertically();
	mb->setPosition(Point(15*40+20,11*40+20));	
	this->addChild(mb,2);
	auto is=MenuItemImage::create("td/save.png","td/save.png");
	is->setTarget(this,menu_selector(GameScene::save));
	ms=Menu::create(is,NULL);
	ms->alignItemsVertically();
	ms->setPosition(Point(14*40+20,11*40+20));
	this->addChild(ms,2);
	
	SimpleAudioEngine *engine=SimpleAudioEngine::getInstance();
	engine->preloadBackgroundMusic("music/victory.mp3");
	GameScene::musicplay();
	
	auto dispatcher=Director::getInstance()->getEventDispatcher();
	auto touchlistener=EventListenerTouchOneByOne::create();
	touchlistener->onTouchBegan=CC_CALLBACK_2(GameScene::playertouch,this);
	touchlistener->onTouchMoved=CC_CALLBACK_2(GameScene::touchmove,this);
	touchlistener->onTouchEnded=CC_CALLBACK_2(GameScene::touchend,this);
	dispatcher->addEventListenerWithSceneGraphPriority(touchlistener,this);
	
	enemy=__Array::create();
	enemy->retain();
	tower=__Array::create();
	tower->retain();
	//news
	news=LabelAtlas::create(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~","fonts/mylabel_cmd_9_18.png",10,18,' ');
	news->setPosition(Point(0,y-20));
	news->setString(" ");
	news->setScale(20/18);
	this->addChild(news,2);
	
	sprintf(aaa,"Hello,world!");
	GameScene::shownews(aaa,3);
	//label
	money=1000;life=25;wave=0;
	sprintf(cmoney,"Money:%d",money);
	sprintf(cwave,"Wave:%d",wave);
	sprintf(clife,"Life:%d",life);
	
	lmoney=LabelAtlas::create(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~","fonts/mylabel_cmd_9_18.png",10,18,' ');
	lmoney->setPosition(Point(120,y-20-20));
	lmoney->setString(cmoney);
	lmoney->setScale(20/18);
	this->addChild(lmoney,2);
	
	llife=LabelAtlas::create(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~","fonts/mylabel_cmd_9_18.png",10,18,' ');
	llife->setPosition(Point(240,y-20-20));
	llife->setString(clife);
	llife->setScale(20/18);
	this->addChild(llife,2);
	
	lwave=LabelAtlas::create(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~","fonts/mylabel_cmd_9_18.png",10,18,' ');
	lwave->setPosition(Point(0,y-20-20));
	lwave->setString(cwave);
	lwave->setScale(20/18);
	this->addChild(lwave,2);
	
	//bg 
	for(int i=0;i<17;i++)
	{
		for(int j=0;j<12;j++)
		{
			if((i+j)%2==0)
			{
				auto dg=Sprite::create("td/darkgreen.png");
				dg->setAnchorPoint(Point(0,0));
				dg->setPosition(Point(i*40,j*40));
				this->addChild(dg,0);
			}
			else
			{
				auto dg=Sprite::create("td/darkgreen2.png");
				dg->setAnchorPoint(Point(0,0));
				dg->setPosition(Point(i*40,j*40));
				this->addChild(dg,0);
			}
			if(map[i][j]==1)
			{
				auto b=Sprite::create("td/blue.png");
				b->setAnchorPoint(Point(0,0));
				b->setPosition(Point(i*40,j*40));
				this->addChild(b,1);
			}
			if(map[i][j]>900)
			{
				auto pathway=Sprite::create("td/pathway.png");
				pathway->setAnchorPoint(Point(0,0));
				pathway->setPosition(Point(i*40,j*40));
				this->addChild(pathway,1);
			}
		}
	}
	//switch control
	auto aa=Sprite::create("td/sell.png");
	auto aaaa=Sprite::create("td/x1_1.png");
	auto bb=Sprite::create("td/x2_2.png");
	auto bbb=Sprite::create("td/null.png");	
	auto switchctr=ControlSwitch::create(
	aa,
	aaaa,
	bb,
	bbb,
	Label::createWithSystemFont("","Arial",16),
	Label::createWithSystemFont("","Arial",16)
	);
	switchctr->setPosition(Point(13*40+20,11*40+20));
	switchctr->addTargetWithActionForControlEvents(this,cccontrol_selector(GameScene::accel),Control::EventType::VALUE_CHANGED);
	this->addChild(switchctr,3);
	
	auto aa2=Sprite::create("td/sell.png");
	auto aaaa2=Sprite::create("td/pause_1.png");
	auto bb2=Sprite::create("td/resume_1.png");
	auto bbb2=Sprite::create("td/null.png");
	auto switchctr2=ControlSwitch::create(
	aa2,
	aaaa2,
	bb2,
	bbb2,
	Label::createWithSystemFont("","Arial",16),
	Label::createWithSystemFont("","Arial",16)
	);
	switchctr2->setPosition(Point(12*40+20,11*40+20));
	switchctr2->addTargetWithActionForControlEvents(this,cccontrol_selector(GameScene::pause_resume),Control::EventType::VALUE_CHANGED);
	this->addChild(switchctr2,3);
	//tower
	auto s1=Sprite::create("td/tower/tower1.png");
	auto s2=Sprite::create("td/tower/tower2.png");
	auto s3=Sprite::create("td/tower/tower3.png");
	auto s4=Sprite::create("td/tower/tower4.png");
	s1->setPosition(Point(40+20,0+20));
	s2->setPosition(Point(40*3+20,0+20));
	s3->setPosition(Point(40*5+20,0+20));
	s4->setPosition(Point(40*7+20,0+20));
	this->addChild(s1,3);
	this->addChild(s2,3);
	this->addChild(s3,3);
	this->addChild(s4,3);
	auto s11=Sprite::create("td/white.png");
	auto s21=Sprite::create("td/white.png");
	auto s31=Sprite::create("td/white.png");
	auto s41=Sprite::create("td/white.png");
	s11->setPosition(Point(40+20,0+20));
	s21->setPosition(Point(40*3+20,0+20));
	s31->setPosition(Point(40*5+20,0+20));
	s41->setPosition(Point(40*7+20,0+20));
	this->addChild(s11,2);
	this->addChild(s21,2);
	this->addChild(s31,2);
	this->addChild(s41,2);
	auto l1=LabelAtlas::create(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~","fonts/mylabel_cmd_9_18.png",10,18,' ');
	l1->setPosition(Point(40*2,0));
	l1->setString("125");
	l1->setScale(1.25);
	this->addChild(l1,2);
	auto l2=LabelAtlas::create(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~","fonts/mylabel_cmd_9_18.png",10,18,' ');
	l2->setPosition(Point(40*4,0));
	l2->setString("75");
	l2->setScale(1.25);
	this->addChild(l2,2);
	auto l3=LabelAtlas::create(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~","fonts/mylabel_cmd_9_18.png",10,18,' ');
	l3->setPosition(Point(40*6,0));
	l3->setString("175");
	l3->setScale(1.25);
	this->addChild(l3,2);
	auto l4=LabelAtlas::create(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~","fonts/mylabel_cmd_9_18.png",10,18,' ');
	l4->setPosition(Point(40*8,0));
	l4->setString("300");
	l4->setScale(1.25);
	this->addChild(l4,2);
	no1=Sprite::create("td/no.png");
	no1->setPosition(Point(-40,-40));
	this->addChild(no1,4);
	no2=Sprite::create("td/no.png");
	no2->setPosition(Point(-40,-40));
	this->addChild(no2,4);
	no3=Sprite::create("td/no.png");
	no3->setPosition(Point(-40,-40));
	this->addChild(no3,4);
	no4=Sprite::create("td/no.png");
	no4->setPosition(Point(-40,-40));
	this->addChild(no4,4);
	//draw
	drawnode=DrawNode::create();
	this->addChild(drawnode,10);
	//updata
	this->schedule(schedule_selector(GameScene::updata),0.05f);
}
void GameScene::die()
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
	auto labeltitle=LabelTTF::create("YOU DEFEATED\nbetter luck next time","Arial",24);
	labeltitle->setPosition(Point(100,120));
	lwin->addChild(labeltitle,3);
	
	auto lb=LabelTTF::create("back to main menu","Arial",18);
	auto ib=MenuItemLabel::create(lb,this,menu_selector(GameScene::back));
	auto mm=Menu::create(ib,NULL);
	
	mm->alignItemsVerticallyWithPadding(15);
	mm->setPosition(Point(100,60));
	lwin->addChild(mm,3);
	log("you defeated");
	CCDirector::sharedDirector()->getScheduler()->setTimeScale(1.0f);
}
void GameScene::shownews(char a[],int t)
{
	news->setString(a);
	if(t!=0)
	{
		this->runAction(Sequence::create(DelayTime::create(t),CallFunc::create(this,callfunc_selector(GameScene::newsclear)),NULL));
	}
}
void GameScene::newsclear()
{
	news->setString(" ");
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
bool GameScene::iscollision(Sprite *s1,Sprite *s2)
{
	if(s1->boundingBox().intersectsRect(s2->boundingBox()))
    {
        return true;
    }
    return false;
}
//menu items
void GameScene::menu(Ref* pSender)
{
	auto d=Director::getInstance();
	d->pause();
	auto s=d->getWinSize();
	mb->setEnabled(false);
	lm=LayerColor::create(Color4B(0,0,255,200),200,150);
	lm->ignoreAnchorPointForPosition(false);
	lm->setPosition(Point(s.width/2,s.height/2));
	this->addChild(lm,5);
	auto labeltitle=LabelTTF::create("GAME IS PAUSED","Arial",24);
	labeltitle->setPosition(Point(100,120));
	lm->addChild(labeltitle,6);
	auto lb=LabelTTF::create("back to main menu","Arial",18);
	auto ib=MenuItemLabel::create(lb,this,menu_selector(GameScene::back));
	auto lr=LabelTTF::create("resume","Arial",18);
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
		engine->playBackgroundMusic("music/victory.mp3",true);
	}
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
	CCDirector::sharedDirector()->getScheduler()->setTimeScale(1.0f);
	auto d=Director::getInstance();
	d->resume();
	GameScene::endbegin();
}

