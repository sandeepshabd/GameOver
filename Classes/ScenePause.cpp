#include "ScenePause.h"


USING_NS_CC;


Scene* ScenePause::createScene()
{
	auto scene = Scene::create();
	auto pauseScreenLayer = ScenePause::create();
	scene->addChild(pauseScreenLayer);
	return scene;
}

bool ScenePause::init()
{
	if(!Layer::init()){
		return false;
	}

	_director = Director::getInstance();
	_visibleSize = _director->getVisibleSize();
	Vec2 visibleOrigin = _director->getVisibleOrigin();


	auto label = Label::createWithTTF("PAUSE", "fonts/Marker Felt.ttf", 40);
	label->setPosition(Vec2(visibleOrigin.x+_visibleSize.width/2,
		visibleOrigin.y + _visibleSize.height /2));
	this->addChild(label,1);


	auto playItem =  MenuItemImage::create("play.png","play_pressed.png",CC_CALLBACK_1(ScenePause::closeScenePause,this));
	playItem->setPosition(Vec2(visibleOrigin.x+_visibleSize.width-playItem->getContentSize().width/2,
		visibleOrigin.y+_visibleSize.height-playItem->getContentSize().height/2));

	auto menu = Menu::create(playItem,nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu,1);





}

void ScenePause::closeScenePause(Ref* pSender){

	_director->popScene();

}

