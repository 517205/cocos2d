#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
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
	
	return true;
}
// on "init" you need to initialize your instance

/*
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    return true;
}
*/

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
