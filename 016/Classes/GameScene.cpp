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
extern bool isresumed;
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
int map_remain[17][12]={
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
int map_save[17][12]={0};
int wave_save;
int money_save;
int life_save;
int time_0_05=0;
int enemynum[5][10]={

{0},
{0,8,0,0,15,0,0,8,8,0},
{0,0,8,0,0,15,0,8,0,5},
{0,0,0,8,0,0,15,0,8,8},
{1,0,0,0,0,0, 0,0,0,0}
};
/*
{0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{1,2,3,0,0,0, 0,0,0,0}
};
*/
int towerlist[5][10]={
{0},
{125,110,120,50,150,70,100,150,350,6},
{75,160,75,50,150,70,100,150,350,5},
{175,85,90,50,150,70,100,150,350,10},
{300,250,250,50,150,70,100,150,350,20}
};//[id][] cost,range,damage_per_sec,up2lv2need_rate,up2lv3need_rate,sell_rate,lv1damage_rate,lv2damage_rate,lv3damage_rate,firerate(0.05s)
int enemylist[5][10]={
{0},
{125,60,1,7},
{275,45,2,9},
{75,100,1,4},
{1800,35,5,150}
};//[id][] health,speed,damage,cost
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
	anode=Node::create();
	this->addChild(anode,0);
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    if(console)
    {
    	AllocConsole();
		freopen("CONIN$", "r", stdin);  
		freopen("CONOUT$", "w", stdout);  
		freopen("CONOUT$", "w", stderr);
    }
    #endif
	enemy=__Array::create();
	enemy->retain();
	tower=__Array::create();
	tower->retain();
	if(GameScene::myInit())
	{
	if(isresumed==false)
	{
		money=300;life=25;wave=0;
		sprintf(cmoney,"Money:%d",money);
		sprintf(cwave,"Wave:%d",wave);
		sprintf(clife,"Life:%d",life);
	}
	else
	{
		money=LoadIntegerFromXML("money");
		life=LoadIntegerFromXML("life");
		wave=LoadIntegerFromXML("wave");
		sprintf(cmoney,"Money:%d",money);
		sprintf(cwave,"Wave:%d",wave);
		sprintf(clife,"Life:%d",life);
		for(int i=0;i<17;i++)
		{
			for(int j=0;j<12;j++)
			{
				char mm[20];
				sprintf(mm,"map%02d%02d",i,j);
				map[i][j]=LoadIntegerFromXML(mm);
			}
		}
		for(int i=0;i<17;i++)
		{
			for(int j=0;j<12;j++)
			{
				if(map[i][j]>100 && map[i][j]<200)
				{
					int id=(map[i][j]%100)/10;
					auto tt=new HPSprite();
					char ch[50];
					sprintf(ch,"td/tower/tower%d.png",id);
					tt->main=Sprite::create(ch);
					tt->xx=i;tt->yy=j;
					tt->id=id;
					tt->range=towerlist[id][1];
					tt->damage=towerlist[id][2];
					tt->lv=(map[i][j]%100)%10;
					tt->main->setPosition(Point(i*40+20,j*40+20));
					tt->worth=towerlist[id][0];
					tt->firerate=towerlist[id][9];
					tt->lvlabel=LabelAtlas::create(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~","fonts/mylabel_cmd_9_18.png",10,18,' ');
					if(tt->lv==1)
						{
							tt->lvlabel->setString("lv1");
						}
					if(tt->lv==2)
						{
							tt->lvlabel->setString("lv2");
							tt->damage=(int)towerlist[tt->id][2]*towerlist[tt->id][5+tt->lv]/(double)100;
							tt->worth+=(int)towerlist[tt->id][0]*towerlist[tt->id][1+tt->lv]/(double)100;
						}
					if(tt->lv==3)
						{
							tt->lvlabel->setString("lv3");
							tt->damage=(int)towerlist[tt->id][2]*towerlist[tt->id][5+tt->lv]/(double)100;
							tt->worth+=(int)towerlist[tt->id][0]*towerlist[tt->id][1+tt->lv]/(double)100;
							
							tt->damage=(int)towerlist[tt->id][2]*towerlist[tt->id][5+tt->lv]/(double)100;
							tt->worth+=(int)towerlist[tt->id][0]*towerlist[tt->id][1+tt->lv]/(double)100;
						}
					tt->lvlabel->setPosition(Point(i*40,j*40));
					tt->lvlabel->setScale(0.6);
					this->addChild(tt->main,3);
					this->addChild(tt->lvlabel,4);
					tower->addObject(tt);
				}
			}
		}
	}	
	//label money life wave
	lmoney=LabelAtlas::create(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~","fonts/mylabel_cmd_9_18.png",10,18,' ');
	lmoney->setPosition(Point(120,y-20-20));
	lmoney->setString(cmoney);
	lmoney->setScale(20/18);
	this->addChild(lmoney,2);
	
	llife=LabelAtlas::create(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~","fonts/mylabel_cmd_9_18.png",10,18,' ');
	llife->setPosition(Point(240,y-20-20));
	llife->setString(clife);
	llife->setScale(20/18);
	this->addChild(llife,2);
	
	lwave=LabelAtlas::create(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~","fonts/mylabel_cmd_9_18.png",10,18,' ');
	lwave->setPosition(Point(0,y-20-20));
	lwave->setString(cwave);
	lwave->setScale(20/18);
	this->addChild(lwave,2);
	
	//updata
	this->schedule(schedule_selector(GameScene::updata),0.05);
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	return true;
}
double GameScene::enemyhpfunc(int wav)
{
	double rate1=0.25+(double)wav/4;//0.5->5.25
//	double rate2=(double)wav/5+.2;//
	double rate3=(double)(wav-15)*sqrt(wav-15)*0.1+4;
//	if(wav<=10)return rate1;
	if(wav<=20) return rate1;
	return rate3;
}
bool GameScene::myInit()
{
	log("init begin");
    srand((unsigned)time(0));
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
	
	//news
	news=LabelAtlas::create(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~","fonts/mylabel_cmd_9_18.png",10,18,' ');
	news->setPosition(Point(0,y-20));
	news->setString(" ");
	news->setScale(20/18);
	this->addChild(news,2);
	
	sprintf(aaa,"Hello,world!");
	GameScene::shownews(aaa,3);

	
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
	auto l1=LabelAtlas::create(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~","fonts/mylabel_cmd_9_18.png",10,18,' ');
	l1->setPosition(Point(40*2,0));
	l1->setString("125");
	l1->setScale(1.25);
	this->addChild(l1,2);
	auto l2=LabelAtlas::create(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~","fonts/mylabel_cmd_9_18.png",10,18,' ');
	l2->setPosition(Point(40*4,0));
	l2->setString("75");
	l2->setScale(1.25);
	this->addChild(l2,2);
	auto l3=LabelAtlas::create(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~","fonts/mylabel_cmd_9_18.png",10,18,' ');
	l3->setPosition(Point(40*6,0));
	l3->setString("175");
	l3->setScale(1.25);
	this->addChild(l3,2);
	auto l4=LabelAtlas::create(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~","fonts/mylabel_cmd_9_18.png",10,18,' ');
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
	drawbullet=DrawNode::create();
	this->addChild(drawbullet,10);
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
	tmoneyup=LabelAtlas::create(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~","fonts/mylabel_cmd_9_18.png",10,18,' ');
	tmoneyup->setPosition(Point(0,20));
	tmoneyup->setString("0");
	tmoneyup->setScale(20/18);
	lselect->addChild(tmoneyup,2);
	tmoneysell=LabelAtlas::create(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~","fonts/mylabel_cmd_9_18.png",10,18,' ');
	tmoneysell->setPosition(Point(80,20));
	tmoneysell->setString("0");
	tmoneysell->setScale(20/18);
	lselect->addChild(tmoneysell,2);
	tinfo=LabelAtlas::create(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~","fonts/mylabel_cmd_9_18.png",10,18,' ');
	tinfo->setPosition(Point(0,80));
	tinfo->setString("0");
	tinfo->setScale(20/18);
	lselect->addChild(tinfo,2);
	log("init end");
	return true;
}
void GameScene::updata(float delta)
{
//	log("updata");
	time_0_05++;
	if(time_0_05>2100000000) time_0_05=0;
	
	drawbullet->clear();
	
	Ref* obj=NULL;
	//tower shoot
	if(isgame)
//	for(int i=1;i<=4;i++)
	{
		CCARRAY_FOREACH(tower,obj)
		{
			auto twr=static_cast<HPSprite *>(obj);
			if(time_0_05%towerlist[twr->id][9]==0)//shoot
			{
				double mmax=-40.1;
				log("\n");
				CCARRAY_FOREACH(enemy,obj)
				{
					auto s=static_cast<HPSprite *>(obj);
					if(s->hasgone>=-40)
					{
						s->hasgonetmp=(double)s->hasgone+sqrt((s->fromx-s->main->getPosition().x)*(s->fromx-s->main->getPosition().x)+(s->fromy-s->main->getPosition().y)*(s->fromy-s->main->getPosition().y));
						double distance=sqrt((twr->xx*40+20-s->main->getPosition().x)*(twr->xx*40+20-s->main->getPosition().x)+(twr->yy*40+20-s->main->getPosition().y)*(twr->yy*40+20-s->main->getPosition().y));
						log("%d,%f,%f",s->hasgone,s->hasgonetmp,distance);
						if(distance<=twr->range)
						{
							if(s->hasgonetmp>mmax) mmax=s->hasgonetmp;
							s->isinrange=true;
						}
						
					}
					
				}
				bool isshoot=false;
			//	int shootonce=0;
				CCARRAY_FOREACH(enemy,obj)
				{
					auto s=static_cast<HPSprite *>(obj);
					if(twr->id==3)
					{
						if(s->isinrange==true)
						{
							s->hp-=(double)twr->damage/20*twr->firerate;
							isshoot=true;
							drawbullet->drawSegment(twr->main->getPosition(),s->main->getPosition(),1.0,Color4F(1-(double)1/(rand()%6+1),1-(double)1/(rand()%6+1),1-(double)1/(rand()%6+1),.5));
						}
					}
					else if(abs(s->hasgonetmp-mmax)<=1e-8)
					{
					//	if(shootonce==0)
						{
							s->hp-=(double)twr->damage/20*twr->firerate;//20*0.05s=1s
							isshoot=true;
							drawbullet->drawSegment(twr->main->getPosition(),s->main->getPosition(),1.0,Color4F(1-(double)1/(rand()%6+1),1-(double)1/(rand()%6+1),1-(double)1/(rand()%6+1),.5));
						//	shootonce=1;
						}
					}
				}
				if(isshoot) twr->main->runAction(RotateBy::create(.2,360));
				CCARRAY_FOREACH(enemy,obj)
				{
					auto s=static_cast<HPSprite *>(obj);
					s->isinrange=false;
				}
			}
		}
		
	}
	//enemy die or hurt
	auto tmp1=__Array::create();
	CCARRAY_FOREACH(enemy,obj)
	{
		auto s=static_cast<HPSprite *>(obj);
		if(s->hp<=0)
		{
			money+=s->cost;
			sprintf(cmoney,"Money:%d",money);
			lmoney->setString(cmoney);
			tmp1->addObject(s);
			s->main->stopAllActions();
			s->main->removeFromParent();
		}
		else
		{
			double ang;
			ang=(1-(double)s->hp/s->hpfull)*180;
			s->main->setRotation(ang);
		}
	}
	CCARRAY_FOREACH(tmp1,obj)
	{
		auto s=static_cast<HPSprite *>(obj);
		enemy->removeObject(s);
	}
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
			for(int jj=1;jj<=enemynum[k][wave%10];jj++)
			{
				GameScene::newenemy(k);
			}
			
			
		}
		GameScene::save_init();
	}
}
void GameScene::shoot(float delta)
{
}
void GameScene::save(Ref* pSender)
{
	log("save!");
	GameScene::shownews("Saved at end of wave",1);
	SaveIntegerToXML("money",money_save);
	SaveIntegerToXML("life",life_save);
	SaveIntegerToXML("wave",wave_save);
	for(int i=0;i<17;i++)
		for(int j=0;j<12;j++)
		{
			char buf[20];
			sprintf(buf,"map%02d%02d",i,j);
			SaveIntegerToXML(buf,map_save[i][j]);
		}
}
void GameScene::save_init()
{
	money_save=money;
	life_save=life;
	wave_save=wave;
	for(int i=0;i<17;i++)
		for(int j=0;j<12;j++)
		{
			map_save[i][j]=map[i][j];
		}
}
void GameScene::towerup(Ref* pSender)
{
	if(towersel->lv!=3)
	{
		if(money-(int)(towerlist[towersel->id][0]*towerlist[towersel->id][2+towersel->lv]/(double)100)<0)
		{
			GameScene::shownews("No enough money!",1);
			return;
		}
		map[towersel->xx][towersel->yy]++;//lv++
		GameScene::shownews("Tower up!",1);
		drawnode->clear();
		lselect->setPosition(Point(-120,-120));
		towersel->lv++;
		towersel->damage=(int)towerlist[towersel->id][2]*towerlist[towersel->id][5+towersel->lv]/(double)100;
		towersel->worth+=(int)towerlist[towersel->id][0]*towerlist[towersel->id][1+towersel->lv]/(double)100;
		if(towersel->lv==2)towersel->lvlabel->setString("lv2");
		if(towersel->lv==3)towersel->lvlabel->setString("lv3");
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
	towersel->lvlabel->removeFromParent();
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
	if(map[tx][ty]>100 && map[tx][ty]<200)
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
		sprintf(ttt,"twr%d,dmg=%d",towersel->id,towersel->damage);
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
	if(map[tx][ty]>20 && map[tx][ty]<30)
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
void GameScene::newenemy(int id)
{
	moveid++;
	char t[50];
	sprintf(t,"td/enemy/enemy%d.png",id);
	auto sp=new HPSprite();
	sp->main=Sprite::create(t);
	sp->id=id;
	sp->hp=enemylist[id][0]*GameScene::enemyhpfunc(wave);
	sp->hpfull=enemylist[id][0]*GameScene::enemyhpfunc(wave);
	sp->damage=enemylist[id][2];
	sp->speed=enemylist[id][1];
	sp->fromx=0+20-40*moveid;sp->fromy=200+20;
	sp->tox=20;sp->toy=200+20;
	sp->hasgone=-40*moveid;
	sp->main->setPosition(Point(0+20-40*moveid,200+20));
	sp->cost=enemylist[id][3];
	sp->isinrange=false;
	this->addChild(sp->main,3);
	enemy->addObject(sp);
	if(isgame) GameScene::mainmove(this,sp);
}
void GameScene::newtower(int xx,int yy,int id)
{
	map[xx][yy]=101+id*10;//123 i=label,2=id,3=lv
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
	tt->firerate=towerlist[id][9];
	tt->lvlabel=LabelAtlas::create(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~","fonts/mylabel_cmd_9_18.png",10,18,' ');
	tt->lvlabel->setString("lv1");
	tt->lvlabel->setPosition(Point(xx*40,yy*40));
	tt->lvlabel->setScale(0.6);
	this->addChild(tt->main,3);
	this->addChild(tt->lvlabel,4);
	tower->addObject(tt);
}
void GameScene::mainmove(Node* node,HPSprite* sp)
{
	//reach
	if(abs(sp->main->getPosition().x-sp->tox)<1e-2 && abs(sp->main->getPosition().y-sp->toy)<1e-2)
	{
		if(sp->main->getPosition().x-(20)<1e-2)
		{
			sp->hasgone=0;
			log("get into screen");
			
			
		}
			
		else
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
	
	if(life<=0)
	{
		isgame=false;
		if(LoadIntegerFromXML("maxwave")<wave)
		{
			SaveIntegerToXML("maxwave",wave);
		}
		GameScene::die();
	}
	
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
void GameScene::die()
{
	isgame=false;
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	auto d=Director::getInstance();
	d->pause();
	auto s=d->getWinSize();
	mb->setEnabled(false);
	lwin=LayerColor::create(Color4B(0,0,255,200),300,250);
	lwin->ignoreAnchorPointForPosition(false);
	lwin->setPosition(Point(s.width/2,s.height/2));
	this->addChild(lwin,6);
	auto labeltitle=LabelTTF::create("YOU DEFEATED\nbetter luck next time","Arial",24);
	labeltitle->setPosition(Point(150,220));
	lwin->addChild(labeltitle,3);
	
	char aaa[100];
	sprintf(aaa,"You wave:%d\nBest wave:%d",wave,LoadIntegerFromXML("maxwave"));
	auto labelscore=LabelTTF::create(aaa,"Arial",24);
	labelscore->setPosition(Point(150,150));
	lwin->addChild(labelscore,3);
	
	
	
	auto lb=LabelTTF::create("back to main menu","Arial",18);
	auto ib=MenuItemLabel::create(lb,this,menu_selector(GameScene::back));
	auto mm=Menu::create(ib,NULL);
	
	mm->alignItemsVerticallyWithPadding(15);
	mm->setPosition(Point(150,60));
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
	isgame=false;
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
	isgame=true;
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}
void GameScene::resume(Ref* pSender)
{
	isgame=true;
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
	Ref* obj=NULL;
	CCARRAY_FOREACH(enemy,obj)
	{
		auto s=static_cast<HPSprite *>(obj);
		enemy->removeObject(s);
	}
	CCARRAY_FOREACH(tower,obj)
	{
		auto s=static_cast<HPSprite *>(obj);
		tower->removeObject(s);
	}
	for(int i=0;i<17;i++)
	{
		for(int j=0;j<12;j++)
		{
			map[i][j]=map_remain[i][j];
		}
	}
	GameScene::endbegin();
}

