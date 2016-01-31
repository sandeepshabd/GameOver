#include "PlayScene.h"
#include "ScenePause.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../cocos2d/cocos/platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#endif

#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>

USING_NS_CC;

Scene* PlayScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vect(0,0));
    
    // 'layer' is an autorelease object
    auto layer = PlayScene::create();

    //enable debug draw
	#if COCOS2D_DEBUG
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	#endif

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool PlayScene::onCollision(cocos2d::PhysicsContact& contact)
{
	CCLOG("Collision detected");

	//_sprBomb->setVisible(false);	
	try{
		//_sprBomb->setVisible(false);	
		 auto body = _sprBomb -> getPhysicsBody();
		//_sprBomb->getPhysicsBody()->setVelocity(Vect(0,10));
		//_sprBomb->getPhysicsBody()->setVelocity(Vect(0,10));	
		body->setVelocity(Vect());
		//body->applyImpulse(Vect(10000,0));
		//body->applyForce(Vect(1000,0));
		body->applyTorque(100900.5f);	
		body->setVelocity(Vect(-40,50));
	}catch(const std::exception& e) {
        std::cout << "Caught exception \"" << e.what() << "\"\n";
    }catch (...)
	{
    // well ok, still unknown what to do now, 
    // but a std::exception_ptr doesn't help the situation either.
    	std::cerr << "unknown exception\n";
	}
	

	return false;
}

void PlayScene::setPhysicsBody(cocos2d::Sprite* sprite)
{
	auto body = PhysicsBody::createCircle(sprite->getContentSize().width/2);
	body->setContactTestBitmask(true);
	body->setDynamic(true);	
	sprite -> setPhysicsBody(body);
}

void PlayScene::initPhysics()
{
	try{
		auto contactListener = EventListenerPhysicsContact::create();
		contactListener->onContactBegin = CC_CALLBACK_1(PlayScene::onCollision,this);
		getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener,this);
	}catch(const std::exception& e) {
        std::cout << "Caught exception \"" << e.what() << "\"\n";
    }catch (...)
	{
    // well ok, still unknown what to do now, 
    // but a std::exception_ptr doesn't help the situation either.
    	std::cerr << "unknown exception\n";
	}

	
}

void PlayScene::movePlayerByTouch(Touch* touch, Event* event)
{
	Vec2 touchLocation = touch->getLocation();
	if(_sprPlayer->getBoundingBox().containsPoint(touchLocation)){
		movePlayerIfPossible(touchLocation.x);
	}
}

void PlayScene::movePlayerIfPossible(float newX){
	float sprHalfWidth = _sprPlayer->getBoundingBox().size.width /2 ;
	if(newX >= sprHalfWidth && newX < (_visibleSize.width - sprHalfWidth)){
		_sprPlayer->setPositionX(newX);
	}
}


void PlayScene::initTouch()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch* touch, Event* event){return true;};
	listener->onTouchMoved = CC_CALLBACK_2(PlayScene::movePlayerByTouch,this);
	listener->onTouchEnded = [=](Touch* touch, Event* event){};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}


void PlayScene::movePlayerByAccelerometer(cocos2d::Acceleration* acceleration, cocos2d::Event* event)
{
	movePlayerIfPossible(_sprPlayer->getPositionX() + (acceleration->x * 10));
}



void PlayScene::initAccelerometer()
{
	Device::setAccelerometerEnabled(true);
	auto listener = EventListenerAcceleration::create(CC_CALLBACK_2(PlayScene::movePlayerByAccelerometer, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

// on "init" you need to initialize your instance
bool PlayScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	_director = Director::getInstance();
    _visibleSize = _director->getVisibleSize();
	auto origin = _director->getVisibleOrigin();

    

    auto pauseItem = MenuItemImage::create(
                                           "pause.png",
                                           "pause_pressed.png",
                                           CC_CALLBACK_1(PlayScene::callbackOnPause, this));
 	pauseItem->setPosition(Vec2(_visibleSize.width - pauseItem->getContentSize().width/2 ,
                                pauseItem->getContentSize().height/2));
    auto menu = Menu::create(pauseItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);


	 _sprBomb = Sprite::create("bomb.png");	
	_sprBomb -> setPosition(Vec2(_visibleSize.width / 4, _visibleSize.height + _sprBomb -> getContentSize().height/2));
	this->addChild(_sprBomb,1);

	auto bg = Sprite::create("background.png");
	bg->setAnchorPoint(Vec2::ZERO);
	bg->setPosition(0, 0);
	this->addChild(bg, -1);


	_sprPlayer = Sprite::create("player.png");	
	_sprPlayer->setPosition(Vec2(_visibleSize.width / 4, _visibleSize.height * 0.23));
	setPhysicsBody(_sprPlayer);
	this->addChild(_sprPlayer, 0);


	//Animations
	Vector<SpriteFrame*> frames;
	Size playerSize = _sprPlayer->getContentSize();
	frames.pushBack(SpriteFrame::create("player.png", Rect(0, 0, playerSize.width, playerSize.height)));
	frames.pushBack(SpriteFrame::create("player2.png", Rect(0, 0, playerSize.width, playerSize.height)));
	auto animation = Animation::createWithSpriteFrames(frames,0.2f);
	auto animate = Animate::create(animation);
	_sprPlayer->runAction(RepeatForever::create(animate));
	
	
	// //actions
	// auto moveFinished = CallFuncN::create(CC_CALLBACK_1(PlayScene::moveFinished, this));
	// auto moveTo = MoveTo::create(2, Vec2(sprBomb->getPositionX(), 0 - sprBomb->getContentSize().height/2));
	// auto sequence = Sequence::create(moveTo, moveFinished, nullptr);
	// sprBomb->runAction(sequence);

	setPhysicsBody(_sprBomb);	
	initPhysics();	
	_sprBomb->getPhysicsBody()->setVelocity(Vect(0,-100));	
	initTouch();
	initAccelerometer();
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		setKeepScreenOnJni(true);
	#endif
	initBackButtonListener();
	//_sprBomb->getPhysicsBody()->setLinearDamping(0.1f);

    return true;
}

// void PlayScene::moveFinished(Node* sender){
// 	CCLOG("Move finished");
// }

void PlayScene::callbackOnPause(cocos2d::Ref* pSender){
	_director->pushScene(TransitionFlipX::create(1.0, ScenePause::createScene()));
}


void PlayScene::initBackButtonListener(){
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event){};
    listener->onKeyReleased = CC_CALLBACK_2(PlayScene::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void PlayScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event){
	if(keyCode == EventKeyboard::KeyCode::KEY_BACK){
		Director::getInstance()->end();
	}
}
