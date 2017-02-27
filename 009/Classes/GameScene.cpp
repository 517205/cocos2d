#include"GameScene.h"
#include"HelloWorldScene.h"

#include "SimpleAudioEngine.h"

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
	/*
    auto pcloseitem=MenuItemImage::create("closenormal.png","closeselected.png",CC_CALLBACK_1(GameScene::change,this));
	pcloseitem->setPosition(Point(Director::getInstance()->getWinSize().width-20,20));
	auto pmenu=Menu::create(pcloseitem,NULL);
	pmenu->setPosition(Point::ZERO);
	anode->addChild(pmenu,1);
	*/
	auto lb=Label::createWithTTF("back","fonts/lucida_console.ttf",22);
	auto ib=MenuItemLabel::create(lb,this,menu_selector(GameScene::back));
	auto mb=Menu::create(ib,NULL);
	mb->alignItemsVertically();
	mb->setPosition(Point(30,s.height-20));	
	this->addChild(mb,5);
	return true;
}

void GameScene::back(Ref* pSender)
{
    Director::getInstance()->replaceScene(HelloWorld::createScene());
}

