#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "HelloWorldScene.h"

#include<ctime>
#include<cstdio>
#include<cstdlib>

USING_NS_CC;
using namespace cocos2d;
using namespace CocosDenshion;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool HelloWorld::init()
{
//	MessageBox("welcome here!\n","Alert");
	if(!Layer::init())
	{
		return false;
	}
	auto anode=Node::create();
	this->addChild(anode,0);
	
	auto s=Director::getInstance()->getWinSize();
	
	auto label=Label::createWithTTF("EXIT","fonts/Marker Felt.ttf",18);
	auto item=MenuItemLabel::create(label,this,menu_selector(HelloWorld::close));
	auto mm=Menu::create(item,NULL);
	mm->alignItemsVertically();
	mm->setPosition(Point(20,s.height-20));
	this->addChild(mm,1);
	
	auto sp=Sprite::create("bg.png");
	sp->setPosition(Point(s.width/2,s.height/2));
	this->addChild(sp,0);
	
	MenuItemFont::setFontName("fixedsys");
	MenuItemFont::setFontSize(36);
	
	auto item1=MenuItemFont::create("musicPlay  ");
	item1->setTarget(this,menu_selector(HelloWorld::musicplay));
	auto item2=MenuItemFont::create("musicStop");
	item2->setTarget(this,menu_selector(HelloWorld::musicstop));
	auto item3=MenuItemFont::create("musicPause  ");
	item3->setTarget(this,menu_selector(HelloWorld::musicpause));
	auto item4=MenuItemFont::create("musicResume");
	item4->setTarget(this,menu_selector(HelloWorld::musicresume));
	auto item5=MenuItemFont::create("effectPlay ");
	item5->setTarget(this,menu_selector(HelloWorld::effectplay));
	auto item6=MenuItemFont::create("effectStop");
	item6->setTarget(this,menu_selector(HelloWorld::effectstop));
	auto item7=MenuItemFont::create("effectPause ");
	item7->setTarget(this,menu_selector(HelloWorld::effectpause));
	auto item8=MenuItemFont::create("effectResume");
	item8->setTarget(this,menu_selector(HelloWorld::effectresume));
	
	
//	item1->setFontName("fonts/Marker Felt.ttf");
//	item1->setFontSize(32);
	
	SimpleAudioEngine *engine=SimpleAudioEngine::getInstance();
	engine->preloadBackgroundMusic("bgmusic.mp3");
	engine->preloadEffect("bomb.wav");
	auto menu=Menu::create(item1,item2,item3,item4,item5,item6,item7,item8,NULL);
	menu->setPosition(Point(s.width/2,s.height/2+30));
	menu->alignItemsInColumns(2,2,2,2,NULL);
	this->addChild(menu,1);
	
	return true;
}

void HelloWorld::musicplay(Ref *ref)
{
	auto engine=SimpleAudioEngine::getInstance();
	engine->playBackgroundMusic("bgmusic.mp3",true);
}

void HelloWorld::effectplay(Ref *ref)
{
	auto engine=SimpleAudioEngine::getInstance();
	engine->playEffect("bomb.wav");
}

void HelloWorld::musicstop(Ref *ref)
{
	auto engine=SimpleAudioEngine::getInstance();
	engine->stopBackgroundMusic();
}

void HelloWorld::effectstop(Ref *ref)
{
	auto engine=SimpleAudioEngine::getInstance();
	engine->stopAllEffects();
}

void HelloWorld::musicpause(Ref *ref)
{
	auto engine=SimpleAudioEngine::getInstance();
	engine->pauseBackgroundMusic();
}

void HelloWorld::effectpause(Ref *ref)
{
	auto engine=SimpleAudioEngine::getInstance();
	engine->pauseAllEffects();
}

void HelloWorld::musicresume(Ref *ref)
{
	auto engine=SimpleAudioEngine::getInstance();
	engine->resumeBackgroundMusic();
}

void HelloWorld::effectresume(Ref *ref)
{
	auto engine=SimpleAudioEngine::getInstance();
	engine->resumeAllEffects();
}

void HelloWorld::close(Ref* pSender)
{
	Director::getInstance()->end();
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
	#endif
}

