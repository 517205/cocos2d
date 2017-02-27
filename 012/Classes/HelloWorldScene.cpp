#include "SimpleAudioEngine.h"
//#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "HelloWorldScene.h"
#include "GameScene.h"
#include "gv.h"
#include<ctime>
#include<cstdio>
#include<cstdlib>
USING_NS_CC;
using namespace cocos2d;
using namespace CocosDenshion;
bool isabout=false;
bool isoption=false;
bool ishelp=false; 
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
	
	lmm=LayerColor::create(Color4B(0,0,255,255),150,250);
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
	mainmenu->alignItemsVerticallyWithPadding(25);
	mainmenu->setPosition(Point(75,125));
	lmm->addChild(mainmenu,1);
	
	SimpleAudioEngine *engine=SimpleAudioEngine::getInstance();
	engine->preloadBackgroundMusic("music/mainmenubgmusic.mp3");
	
	HelloWorld::musicplay();
	
	
	return true;
}

/////////////////////////////////////////in main menu
void HelloWorld::option(Ref* pSender)
{
	isoption=true;
	auto s=Director::getInstance()->getWinSize();
	mainmenu->setEnabled(false);
	layeroption=LayerColor::create(Color4B(0,50,0,255),250,150);
	lmm->ignoreAnchorPointForPosition(false);
	layeroption->setPosition(Point(s.width/2-125,s.height/2-75));
	this->addChild(layeroption,2);
	auto lb=Label::createWithTTF("back","fonts/lucida_console.ttf",18);
	auto ib=MenuItemLabel::create(lb,this,menu_selector(HelloWorld::back));
	auto mo=Menu::create(ib,NULL);
	mo->setPosition(Point(25,10));
	layeroption->addChild(mo,3);
	
		
	auto lmusic=Label::createWithTTF("music","fonts/lucida_console.ttf",18);
	lmusic->setPosition(Point(35,60));
	layeroption->addChild(lmusic,3);
	auto lsound=Label::createWithTTF("effect","fonts/lucida_console.ttf",18);
	lsound->setPosition(Point(35,90));
	layeroption->addChild(lsound,3);
	auto lfps=Label::createWithTTF("FPS","fonts/lucida_console.ttf",18);
	lfps->setPosition(Point(35,120));
	layeroption->addChild(lfps,3);
	
	if(!music)
	{
		labelmusic=Label::createWithTTF("false","fonts/lucida_console.ttf",18);
		labelmusic->setColor(Color3B(255,0,0));
	}
	else
	{
		labelmusic=Label::createWithTTF("true","fonts/lucida_console.ttf",18);
		labelmusic->setColor(Color3B(0,255,0));
	}
	if(!sound)
	{
		labelsound=Label::createWithTTF("false","fonts/lucida_console.ttf",18);
		labelsound->setColor(Color3B(255,0,0));
	}
	else
	{
		labelsound=Label::createWithTTF("true","fonts/lucida_console.ttf",18);
		labelsound->setColor(Color3B(0,255,0));
	}
	if(fps)
	{
		labelfps=Label::createWithTTF("true","fonts/lucida_console.ttf",18);
		labelfps->setColor(Color3B(0,255,0));
	}
	else
	{
		labelfps=Label::createWithTTF("false","fonts/lucida_console.ttf",18);
		labelfps->setColor(Color3B(255,0,0));
	}
	
	
//	MessageBox("hello","message");
	auto imusic=MenuItemLabel::create(labelmusic,this,menu_selector(HelloWorld::musicchange));
	auto mmusic=Menu::create(imusic,NULL);
	mmusic->setPosition(Point(140,60));
	layeroption->addChild(mmusic,3);
	

	auto isound=MenuItemLabel::create(labelsound,this,menu_selector(HelloWorld::soundchange));
	auto msound=Menu::create(isound,NULL);
	msound->setPosition(Point(140,90));
	layeroption->addChild(msound,3);
	
	auto ifps=MenuItemLabel::create(labelfps,this,menu_selector(HelloWorld::fpschange));
	auto mfps=Menu::create(ifps,NULL);
	mfps->setPosition(Point(140,120));
	layeroption->addChild(mfps,3);
	
	
}
void HelloWorld::help(Ref* pSender)
{
	ishelp=true;
	auto s=Director::getInstance()->getWinSize();
	mainmenu->setEnabled(false);
	layerhelp=LayerColor::create(Color4B(0,0,0,255),10,10);
	layerhelp->setPosition(Point(s.width/2,s.height/2));
	this->addChild(layerhelp,2);
	auto itemhelp=MenuItemImage::create("help/help.png","help/help.png");
	itemhelp->setTarget(this,menu_selector(HelloWorld::back));
	auto mm=Menu::create(itemhelp,NULL);
	mm->setPosition(Point(0,0));
	layerhelp->addChild(mm,1);
	
//	MessageBox("Help is not ready!!!","warning");
	//mainmenu->setEnabled(false);
}
void HelloWorld::about(Ref* pSender)
{
	isabout=true;
	auto s=Director::getInstance()->getWinSize();
	mainmenu->setEnabled(false);
	layerabout=LayerColor::create(Color4B(0,0,0,255),10,10);
	layerabout->setPosition(Point(s.width/2,s.height/2));
	this->addChild(layerabout,2);
	auto itemabout=MenuItemImage::create("about/about.png","about/about.png");
	itemabout->setTarget(this,menu_selector(HelloWorld::back));
	auto mm=Menu::create(itemabout,NULL);
	mm->setPosition(Point(0,0));
	layerabout->addChild(mm,1);
	
}
////////////////////////////////////////option change
void HelloWorld::musicchange(Ref* pSender)
{
	if(music==false)
	{
		labelmusic->setString("true");
		labelmusic->setColor(Color3B(0,255,0));
	}
	else
	{
		labelmusic->setString("false");
		labelmusic->setColor(Color3B(255,0,0));
	}
	music=!music;
	HelloWorld::musicplay();
}
void HelloWorld::soundchange(Ref* pSender)
{
	if(sound==false)
	{
		labelsound->setString("true");
		labelsound->setColor(Color3B(0,255,0));
	}
	else
	{
		labelsound->setString("false");
		labelsound->setColor(Color3B(255,0,0));
	}
	sound=!sound;
}
void HelloWorld::fpschange(Ref* pSender)
{
	if(fps==false)
	{
		Director::getInstance()->setDisplayStats(true);
		labelfps->setString("true");
		labelfps->setColor(Color3B(0,255,0));
	}
	else
	{
		Director::getInstance()->setDisplayStats(false);
		labelfps->setString("false");
		labelfps->setColor(Color3B(255,0,0));
	}
	fps=!fps;
}
/////////////////////////////////////////music
void HelloWorld::musicplay()
{
	auto engine=SimpleAudioEngine::getInstance();
	engine->stopBackgroundMusic(); 
	if(music)
	{
	//	MessageBox("play","music");
		engine->playBackgroundMusic("music/mainmenubgmusic.mp3",true);
	}
	
}
//////////////////////////////////////////////change scene
void HelloWorld::start(Ref* pSender)
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    Director::getInstance()->replaceScene(GameScene::createScene());
}
void HelloWorld::back(Ref* pSender)
{
	if(isoption)
		layeroption->removeFromParentAndCleanup(true);
	if(isabout)
		layerabout->removeFromParentAndCleanup(true);
	if(ishelp)
		layerhelp->removeFromParentAndCleanup(true);	
	isabout=false;
	isoption=false;
	ishelp=false;
	mainmenu->setEnabled(true);
}
void HelloWorld::quit(Ref* pSender)
{
	Director::getInstance()->end();
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
	#endif
}

