#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"

#include "HelloWorldScene.h"
#include "GameScene.h"
#include "gv.h"
#include<ctime>
#include<cstdio>
#include<cstdlib>
#include <iostream>

#include "network/HttpRequest.h"
#include "network/HttpClient.h"

#include "extensions/cocos-ext.h"

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
using namespace network; 
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
	if(!Layer::init())
	{
		return false;
	}
	auto anode=Node::create();
	this->addChild(anode,0);
	ismain=true;
	/*
	SaveBooleanToXML("music",music);
	SaveBooleanToXML("sound",sound);
	SaveBooleanToXML("fps",fps);
	SaveBooleanToXML("console",console);
	*/
	music=LoadBooleanFromXML("music");
	sound=LoadBooleanFromXML("sound");
	fps=LoadBooleanFromXML("fps");
	console=LoadBooleanFromXML("console");
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    if(console)
    {
    	AllocConsole();  
		freopen("CONIN$", "r", stdin);  
		freopen("CONOUT$", "w", stdout);  
		freopen("CONOUT$", "w", stderr);
    }
    #endif
	if(!fps)
	{
		Director::getInstance()->setDisplayStats(false);
	}
	auto s=Director::getInstance()->getWinSize();
	
	auto l1=LabelAtlas::create(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~","fonts/mylabel_cmd_9_18.png",10,18,' ');
	l1->setPosition(Point(40,410));
	l1->setString("Tower Defence Game");
	l1->setScale(3.1);
	this->addChild(l1,2);
	
	auto l2=LabelAtlas::create(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~","fonts/mylabel_cmd_9_18.png",10,18,' ');
	l2->setPosition(Point(500,0));
	l2->setString("Powered By LM324");
	l2->setScale(1.0);
	this->addChild(l2,2);
	
	lmm=LayerColor::create(Color4B(0,0,255,255),150,250);
	lmm->ignoreAnchorPointForPosition(false);
	lmm->setPosition(Point(s.width/2,s.height/2));
	this->addChild(lmm,0);
	
	auto lq=LabelTTF::create("quit","Arial",22);
	auto iq=MenuItemLabel::create(lq,this,menu_selector(HelloWorld::quit));
	auto ls=LabelTTF::create("start","Arial",22);
	auto is=MenuItemLabel::create(ls,this,menu_selector(HelloWorld::start));
	auto lo=LabelTTF::create("option","Arial",22);
	auto io=MenuItemLabel::create(lo,this,menu_selector(HelloWorld::option));
	auto lh=LabelTTF::create("help","Arial",22);
	auto ih=MenuItemLabel::create(lh,this,menu_selector(HelloWorld::help));
	auto la=LabelTTF::create("about","Arial",22);
	auto ia=MenuItemLabel::create(la,this,menu_selector(HelloWorld::about));
	auto lr=LabelTTF::create("resume","Arial",22);
	auto ir=MenuItemLabel::create(lr,this,menu_selector(HelloWorld::resume));
	mainmenu=Menu::create(is,ir,io,ih,ia,iq,NULL);
	mainmenu->alignItemsVerticallyWithPadding(15);
	mainmenu->setPosition(Point(75,125));
	lmm->addChild(mainmenu,1);
	
	SimpleAudioEngine *engine=SimpleAudioEngine::getInstance();
	engine->preloadBackgroundMusic("music/mainmenubgmusic.mp3");
	
	news=LabelAtlas::create(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~","fonts/mylabel_cmd_9_18.png",10,18,' ');
	news->setPosition(Point(0,0));
	news->setString(" ");
	news->setScale(1.0);
	this->addChild(news,2);
	
	HelloWorld::musicplay();
	
	
	if(LoadBooleanFromXML("isuser")==false)
	{
		HelloWorld::configHTTP();
		SaveStringToXML("url","http://myphp-0005.44fs.preview.openshiftapps.com");
		SaveBooleanToXML("isupload",false);
		HelloWorld::edit();
	}
	if(LoadBooleanFromXML("isuser")==true)
	{
		std::string user=LoadStringFromXML("user");
		const char* cuser=user.c_str();
		char ll[100];
		if(LoadBooleanFromXML("isupload")==true)
		{
			char a[15][5]={"th","st","nd","rd","th","th","th","th","th","th"};
			sprintf(ll,"Welcome back,%s\nYou are the %d%s user!",cuser,LoadIntegerFromXML("usernum"),a[LoadIntegerFromXML("usernum")%10]);
		}
		else
		{
			sprintf(ll,"Welcome back,%s",cuser);
		}
		auto l3=LabelTTF::create(ll/*"Welcome back,"*/,"Arial",20);
		l3->setAnchorPoint(Point(0,0));
		l3->setPosition(Point(45,370));
		this->addChild(l3,2);
		/*
		auto l4=LabelTTF::create(user,"Arial",20);
		l4->setAnchorPoint(Point(0,0));
		l4->setPosition(Point(190,380));
		this->addChild(l4,2);
		*/
	}
	
	
	
	
	
	
	
	
	return true;
}
void HelloWorld::configHTTP()
{
	if(ismain)
	{
	
	std::string aaaa=LoadStringFromXML("url");
	const char* aaa=aaaa.c_str();
	char url[50];
	sprintf(url,"%s/index.php?id=config",aaa);
    HttpRequest *request = new HttpRequest();
    request->setUrl(url);
    //request->setUrl("http://localhost/index.php?name=test&number=123456");
    request->setRequestType(HttpRequest::Type::GET);
    request->setResponseCallback(CC_CALLBACK_2(HelloWorld::requestResponseFunc,this));
    request->setTag("get");
    HttpClient::getInstance()->send(request);
    request->release();
    }
}
void HelloWorld::upload()
{
	if(ismain)
	{
	std::string aaaa=LoadStringFromXML("url");
	const char* aaa=aaaa.c_str();
	std::string username=LoadStringFromXML("user");
	const char* uu=username.c_str();
	char url[100];
	sprintf(url,"%s/index.php?id=adduser&username=%s",aaa,uu);
    HttpRequest *request = new HttpRequest();
    request->setUrl(url);
    request->setRequestType(HttpRequest::Type::GET);
    //request->setRequestData(data,strlen(data));
    request->setResponseCallback(CC_CALLBACK_2(HelloWorld::requestResponseFunc,this));
    request->setTag("upload");
    HttpClient::getInstance()->send(request);
    request->release();
    }
}
void HelloWorld::requestResponseFunc(network::HttpClient *sender, network::HttpResponse *response)
{
	if(ismain)
	{
	
    if(!response)
    {
        return;
    }
    log("%s",response->getHttpRequest()->getTag());
    log("%ld",response->getResponseCode());
    std::string tt=response->getHttpRequest()->getTag();
    const char *tag=tt.c_str();
//    const char *st="get";
//    printf("%s\n%s\n",tag,st);
//    log("%d",strcmp(st,tag));
//    sprintf(tag,"%s",response->getHttpRequest()->getTag());
//    sprintf(st,"tag");
    if(response->getResponseCode()!=-1 && strcmp(tag,"get")==0)
    {
    	log("config");
    	char sss[200];int max;
    	std::vector<char> *buffer=response->getResponseData();
    	for (unsigned int i=0; i<buffer->size(); i++)
			{
        	printf("%c",(*buffer)[i]);
        	sprintf(sss+i,"%c",(*buffer)[i]);
        	max=i;
    	}
    	sprintf(sss+max+1,"\0");
    	printf("\ninfo from server:%s",sss);
    	log("\n");
    	int a;
    	sscanf(sss,"%d",&a);
    	if(a==12345)
			{
    		HelloWorld::shownews("Connected to server!",0);
    		if(LoadBooleanFromXML("isupload")==false) HelloWorld::upload();
    	}
    	return;
    }
    if(response->getResponseCode()!=-1 && strcmp(tag,"upload")==0)
    {
    	log("upload");
    	char sss[200];int max;
    	std::vector<char> *buffer=response->getResponseData();
    	for (unsigned int i=0; i<buffer->size(); i++)
		{
        	printf("%c",(*buffer)[i]);
        	sprintf(sss+i,"%c",(*buffer)[i]);
        	max=i;
    	}
    	sprintf(sss+max+1,"\0");
    	printf("\ninfo from server:%s",sss);
    	log("\n");
    	int num;
    	sscanf(sss,"%d",&num);
    	log("you are the %d user!",num);
    	SaveBooleanToXML("isupload",true);
    	SaveIntegerToXML("usernum",num);
    	return;
    }
    if(ismain) HelloWorld::shownews("Cannot connect to server",0);
	}
}
void HelloWorld::edit()
{
	pEditBox_name = EditBox::create(CCSizeMake(650,50),Scale9Sprite::create("td/white.png"));    
	pEditBox_name->setPosition(Point(680/2,480/2));
	pEditBox_name->setFontColor(Color3B(0,0,0));
	pEditBox_name->setPlaceHolder("First time login.Enter username:"); 
	pEditBox_name->setMaxLength(20);
	pEditBox_name->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);
	pEditBox_name->setInputFlag(cocos2d::ui::EditBox::InputFlag::INITIAL_CAPS_WORD);
	pEditBox_name->setReturnType(cocos2d::ui::EditBox::KeyboardReturnType::DONE);
	pEditBox_name->setDelegate(this);
	pEditBox_name->setTag(101);
	this->addChild(pEditBox_name);
}
void HelloWorld::editBoxEditingDidBegin(EditBox *editBox)    
{    
    CCLOG("start edit");
}    
void HelloWorld::editBoxEditingDidEnd(EditBox *editBox)    
{    
    CCLOG("end edit");    
}    
void HelloWorld::editBoxReturn(EditBox *editBox)    
{    
    CCLOG("editbox return");
    auto editbox = (EditBox*)editBox;
    if(editbox->getTag()==101)
    {
    	char* user = (char *)editbox->getText();
    	pEditBox_name->setPosition(Point(680*2,480*2));
    	SaveBooleanToXML("isuser",true);
    	SaveStringToXML("user",user);
    }
    if(editbox->getTag()==102)
    {
    	char* url = (char *)editbox->getText();
    	SaveStringToXML("url",url);
    }
    
}    
void HelloWorld::editBoxTextChanged(EditBox *editBox,const std::string &text)    
{
	log("editbox changed");
}
/////////////////////////////////////////in main menu
void HelloWorld::option(Ref* pSender)
{
	isoption=true;
	auto s=Director::getInstance()->getWinSize();
	mainmenu->setEnabled(false);
	layeroption=LayerColor::create(Color4B(0,50,0,255),250,200);
	lmm->ignoreAnchorPointForPosition(false);
	layeroption->setPosition(Point(s.width/2-125,s.height/2-100));
	this->addChild(layeroption,2);
	auto lb=LabelTTF::create("back","Arial",18);
	auto ib=MenuItemLabel::create(lb,this,menu_selector(HelloWorld::back));
	auto mo=Menu::create(ib,NULL);
	mo->setPosition(Point(25,10));
	layeroption->addChild(mo,3);
	
	auto lurl=LabelTTF::create("server","Arial",18);
	lurl->setPosition(Point(40,40));
	layeroption->addChild(lurl,3);
	auto lmusic=LabelTTF::create("music","Arial",18);
	lmusic->setPosition(Point(40,75));
	layeroption->addChild(lmusic,3);
	auto lsound=LabelTTF::create("effect","Arial",18);
	lsound->setPosition(Point(40,110));
	layeroption->addChild(lsound,3);
	auto lfps=LabelTTF::create("FPS","Arial",18);
	lfps->setPosition(Point(40,145));
	layeroption->addChild(lfps,3);
	auto lconsole=LabelTTF::create("console","Arial",18);
	lconsole->setPosition(Point(40,180));
	layeroption->addChild(lconsole,3);
	
	
	if(!music)
	{
		labelmusic=LabelTTF::create("false","Arial",18);
		labelmusic->setColor(Color3B(255,0,0));
	}
	else
	{
		labelmusic=LabelTTF::create("true","Arial",18);
		labelmusic->setColor(Color3B(0,255,0));
	}
	if(!sound)
	{
		labelsound=LabelTTF::create("false","Arial",18);
		labelsound->setColor(Color3B(255,0,0));
	}
	else
	{
		labelsound=LabelTTF::create("true","Arial",18);
		labelsound->setColor(Color3B(0,255,0));
	}
	if(fps)
	{
		Director::getInstance()->setDisplayStats(true);
		labelfps=LabelTTF::create("true","Arial",18);
		labelfps->setColor(Color3B(0,255,0));
	}
	else
	{
		Director::getInstance()->setDisplayStats(false);
		labelfps=LabelTTF::create("false","Arial",18);
		labelfps->setColor(Color3B(255,0,0));
	}
	if(console)
	{
		labelconsole=LabelTTF::create("true","Arial",18);
		labelconsole->setColor(Color3B(0,255,0));
	}
	else
	{
		labelconsole=LabelTTF::create("false","Arial",18);
		labelconsole->setColor(Color3B(255,0,0));
	}
	
	auto imusic=MenuItemLabel::create(labelmusic,this,menu_selector(HelloWorld::musicchange));
	auto mmusic=Menu::create(imusic,NULL);
	mmusic->setPosition(Point(155,75));
	layeroption->addChild(mmusic,3);
	
	auto isound=MenuItemLabel::create(labelsound,this,menu_selector(HelloWorld::soundchange));
	auto msound=Menu::create(isound,NULL);
	msound->setPosition(Point(155,110));
	layeroption->addChild(msound,3);
	
	auto ifps=MenuItemLabel::create(labelfps,this,menu_selector(HelloWorld::fpschange));
	auto mfps=Menu::create(ifps,NULL);
	mfps->setPosition(Point(155,145));
	layeroption->addChild(mfps,3);
	
	auto iconsole=MenuItemLabel::create(labelconsole,this,menu_selector(HelloWorld::consolechange));
	auto mconsole=Menu::create(iconsole,NULL);
	mconsole->setPosition(Point(155,180));
	layeroption->addChild(mconsole,3);
	
	
	auto  editt=EditBox::create(CCSizeMake(150,30),Scale9Sprite::create("td/white.png"));
	editt->setPosition(Point(160,40));
	editt->setFontColor(Color3B(0,0,0));
///	char aaa[50];
	std::string aaaa=LoadStringFromXML("url");
	const char* aaa=aaaa.c_str();
//	sprintf(aaa,"%s",aaaa);
	editt->setPlaceHolder(aaa);
	editt->setMaxLength(50);
	editt->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);
	editt->setInputFlag(cocos2d::ui::EditBox::InputFlag::INITIAL_CAPS_WORD);
	editt->setReturnType(cocos2d::ui::EditBox::KeyboardReturnType::DONE);
	editt->setDelegate(this);
	editt->setTag(102);
	layeroption->addChild(editt);
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
	itemabout->setScale(.8);
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
	SaveBooleanToXML("music",music);
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
	SaveBooleanToXML("sound",sound);
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
	SaveBooleanToXML("fps",fps);
}
void HelloWorld::consolechange(Ref* pSender)
{
	if(console==false)
	{
		labelconsole->setString("true");
		labelconsole->setColor(Color3B(0,255,0));
	}
	else
	{
		labelconsole->setString("false");
		labelconsole->setColor(Color3B(255,0,0));
	}
	console=!console;
	SaveBooleanToXML("console",console);
}
////////////////////news
void HelloWorld::shownews(char a[],int t)
{
	news->setString(a);
	if(t!=0)
	{
		this->runAction(Sequence::create(DelayTime::create(t),CallFunc::create(this,callfunc_selector(HelloWorld::newsclear)),NULL));
	}
}
void HelloWorld::newsclear()
{
	news->setString(" ");
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
	ismain=false;
	isresumed=false;
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    Director::getInstance()->replaceScene(GameScene::createScene());
}
void HelloWorld::resume(Ref* pSender)
{
	ismain=false;
	isresumed=true;
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

