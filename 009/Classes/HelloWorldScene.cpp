#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "HelloWorldScene.h"
#include "GameScene.h"

#include<ctime>
#include<cstdio>
#include<cstdlib>
USING_NS_CC;

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
	
	lmm=LayerColor::create(Color4B(0,0,255,255),100,150);
	lmm->ignoreAnchorPointForPosition(false);
	lmm->setPosition(Point(s.width/2,s.height/2));
	this->addChild(lmm,0);
	
	auto lq=Label::createWithTTF("quit","fonts/lucida_console.ttf",22);
	auto iq=MenuItemLabel::create(lq,this,menu_selector(HelloWorld::quit));
	auto ls=Label::createWithTTF("start","fonts/lucida_console.ttf",22);
	auto is=MenuItemLabel::create(ls,this,menu_selector(HelloWorld::start));
	auto lo=Label::createWithTTF("option","fonts/lucida_console.ttf",22);
	auto io=MenuItemLabel::create(lo,this,menu_selector(HelloWorld::option));
	auto lh=Label::createWithTTF("help","fonts/lucida_console.ttf",22);
	auto ih=MenuItemLabel::create(lh,this,menu_selector(HelloWorld::help));
	auto la=Label::createWithTTF("about","fonts/lucida_console.ttf",22);
	auto ia=MenuItemLabel::create(la,this,menu_selector(HelloWorld::about));
	mainmenu=Menu::create(is,io,ih,ia,iq,NULL);
	mainmenu->alignItemsVertically();
	mainmenu->setPosition(Point(50,75));
	lmm->addChild(mainmenu,1);
	
	
	
	return true;
}

void HelloWorld::start(Ref* pSender)
{
    Director::getInstance()->replaceScene(GameScene::createScene());
}
void HelloWorld::option(Ref* pSender)
{
	auto s=Director::getInstance()->getWinSize();
	mainmenu->setEnabled(false);
	layeroption=LayerColor::create(Color4B(0,255,0,255),150,100);
	lmm->ignoreAnchorPointForPosition(false);
	layeroption->setPosition(Point(s.width/2-75,s.height/2-50));
	this->addChild(layeroption,2);
	auto lb=Label::createWithTTF("back","fonts/lucida_console.ttf",18);
	auto ib=MenuItemLabel::create(lb,this,menu_selector(HelloWorld::back));
	auto mo=Menu::create(ib,NULL);
	mo->setPosition(Point(50,50));
	layeroption->addChild(mo,3);
	
}
void HelloWorld::help(Ref* pSender)
{
	mainmenu->setEnabled(false);
}
void HelloWorld::about(Ref* pSender)
{
	mainmenu->setEnabled(false);
}
void HelloWorld::back(Ref* pSender)
{
	mainmenu->setEnabled(true);
	
}
void HelloWorld::quit(Ref* pSender)
{
	Director::getInstance()->end();
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
	#endif
}

