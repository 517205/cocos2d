#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "network/HttpRequest.h"
#include "network/HttpClient.h"
#include "extensions/cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class HelloWorld : public cocos2d::Layer,public EditBoxDelegate
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    virtual void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox);  
	virtual void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox);  
	virtual void editBoxTextChanged(cocos2d::extension::EditBox* editBox,const std::string &text);  
	virtual void editBoxReturn(cocos2d::extension::EditBox *editBox);
	
	void edit();

    void configHTTP(void);
    void requestResponseFunc(network::HttpClient *sender, network::HttpResponse *response);
    
    void start(cocos2d::Ref* pSender);
	void back(cocos2d::Ref* pSender);
	void quit(cocos2d::Ref* pSender);
	
    void option(cocos2d::Ref* pSender);
    void help(cocos2d::Ref* pSender);
    void about(cocos2d::Ref* pSender);
    
    void musicchange(cocos2d::Ref* pSender);
    void soundchange(cocos2d::Ref* pSender);
    void fpschange(cocos2d::Ref* pSender);
    void consolechange(cocos2d::Ref* pSender);
    
    void musicplay(void);
    
    
private:
	Menu *mainmenu;
	Layer *lmm;
	Layer *layeroption;
	Layer *layerabout;
	Layer *layerhelp;
	LabelTTF *labelsound;
	LabelTTF *labelmusic;
	LabelTTF *labelfps;
	LabelTTF *labelconsole;
	EditBox *pEditBox_name;
	
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
