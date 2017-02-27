#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
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
	if(!Layer::init())
	{
		return false;
	}
	auto anode=Node::create();
	this->addChild(anode,0);
	
	auto pcloseitem=MenuItemImage::create("closenormal.png","closeselected.png",CC_CALLBACK_1(HelloWorld::menuCloseCallback,this));
	pcloseitem->setPosition(Point(Director::getInstance()->getWinSize().width-20,20));
	auto pmenu=Menu::create(pcloseitem,NULL);
	pmenu->setPosition(Point::ZERO);
	anode->addChild(pmenu,1);
	
	auto size=Director::getInstance()->getWinSize();
	log("%f,%f\n",size.width,size.height);
	srand((unsigned)time(0));
	for(int i=1;i<=100;i++)
	{
		int x=rand()%(int)size.width;//480.000000
		int y=rand()%(int)size.height;//320.000000
		log("%d %d",x,y);
		auto sp=Sprite::create("helloworld.png");
		sp->setPosition(Point(x,y));
		sp->setScale(.2);
		sp->setRotation(rand());
		anode->addChild(sp,0);
	}
	
	/*
	glLineWidth(5.0f);
	DrawPrimitives::setDrawColor4B(255,0,0,255);
	DrawPrimitives::setDrawLine(Point(0,size.height),Point(size.width,0));
	*/
	/*
	auto plabel=LabelTTF::create("hello,world!","arial",34);
	plabel->setPosition(Point(size.width/2+100,size.height/2+100));
	anode->addChild(plabel,1);
	
	auto plabel2=LabelTTF::create("hello,world!","fonts/Marker Felt.ttf",34);
	plabel2->setPosition(Point(size.width/2,size.height/2));
	plabel2->setColor(Color3B(255,255,0));
	anode->addChild(plabel2,1);
	
	auto plabel3=LabelTTF::create("hello,world!","fixedsys",34);
	plabel3->setPosition(Point(size.width/2-100,size.height/2+100));
	plabel3->setColor(Color3B(0,255,0));
	anode->addChild(plabel3,1);
	
	auto psprite=Sprite::create("helloworld.png");
	psprite->setPosition(Point(size.width/2,size.height/2));
	anode->addChild(psprite,0);
	
	auto psprite2=Sprite::create("helloworld.png");
	psprite2->setPosition(Point(50,50));
	anode->addChild(psprite2,0);
	
	auto psprite3=Sprite::create("helloworld.png");
	psprite3->setPosition(Point(100,100));
	psprite3->setRotation(60);
	psprite3->setScale(0.5);
	anode->addChild(psprite3,0);
	*/
	return true;
}
// on "init" you need to initialize your instance



void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}
