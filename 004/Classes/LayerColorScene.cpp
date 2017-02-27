#include"LayerColorScene.h"
#include"HelloWorldScene.h"

#include "SimpleAudioEngine.h"

Scene* LayerColorScene::createScene()
{
	auto scene=Scene::create();
	auto layer=LayerColorScene::create();
	scene->addChild(layer);
	return scene;
}
bool LayerColorScene::init()
{
	if(!LayerColor::initWithColor(Color4B(255,0,0, 255)))
    {
        return false;
    }
    auto anode=Node::create();
	this->addChild(anode,0);
    auto pcloseitem=MenuItemImage::create("closenormal.png","closeselected.png",CC_CALLBACK_1(LayerColorScene::change,this));
	pcloseitem->setPosition(Point(Director::getInstance()->getWinSize().width-20,20));
	auto pmenu=Menu::create(pcloseitem,NULL);
	pmenu->setPosition(Point::ZERO);
	anode->addChild(pmenu,1);
	
    auto s=Director::getInstance()->getWinSize();
	auto layer=LayerColor::create(Color4B(0,255,0,255),200,150);
	layer->ignoreAnchorPointForPosition(false);
	layer->setPosition(Point(s.width/2,s.height/2));
	addChild(layer,1,3);
	
	auto ss=Director::getInstance()->getWinSize();
	
	auto ll=Label::createWithTTF("This is layer color scene !","fonts/Marker Felt.ttf",32);
	ll->setPosition(Point(ss.width/2,ss.height/2));
	ll->setColor(Color3B(0,0,255));
	ll->setRotation(45);
	this->addChild(ll,4);
	return true;
}

void LayerColorScene::change(Ref* pSender)
{
    Director::getInstance()->replaceScene(HelloWorld::createScene());
}

