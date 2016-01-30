#include "PlayScene.h"
#include "ScenePause.h"

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

bool PlayScene::onCollision(PhysicsContact& contact)
{
	CCLOG("Collision detected");

	//_sprBomb->setVisible(false);	
	auto body = _sprBomb -> getPhysicsBody();
	body->setVelocity(Vect());
	body->applyTorque(100900.5f);	
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
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(PlayScene::onCollision,this);
	getEventDispatcher() ->addEventListenerWithSceneGraphPriority(contactListener,this);
	
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


	auto _sprBomb = Sprite::create("bomb.png");	
	_sprBomb -> setPosition(Vec2(_visibleSize.width / 4, _visibleSize.height + _sprBomb -> getContentSize().height/2));
	this->addChild(_sprBomb,1);

	auto bg = Sprite::create("background.png");
	bg->setAnchorPoint(Vec2::ZERO);
	bg->setPosition(0, 0);
	this->addChild(bg, -1);


	auto sprPlayer = Sprite::create("player.png");	
	sprPlayer->setPosition(Vec2(_visibleSize.width / 4, _visibleSize.height * 0.23));
	setPhysicsBody(sprPlayer);
	this->addChild(sprPlayer, 0);


	//Animations
	Vector<SpriteFrame*> frames;
	Size playerSize = sprPlayer->getContentSize();
	frames.pushBack(SpriteFrame::create("player.png", Rect(0, 0, playerSize.width, playerSize.height)));
	frames.pushBack(SpriteFrame::create("player2.png", Rect(0, 0, playerSize.width, playerSize.height)));
	auto animation = Animation::createWithSpriteFrames(frames,0.2f);
	auto animate = Animate::create(animation);
	sprPlayer->runAction(RepeatForever::create(animate));
	
	
	// //actions
	// auto moveFinished = CallFuncN::create(CC_CALLBACK_1(PlayScene::moveFinished, this));
	// auto moveTo = MoveTo::create(2, Vec2(sprBomb->getPositionX(), 0 - sprBomb->getContentSize().height/2));
	// auto sequence = Sequence::create(moveTo, moveFinished, nullptr);
	// sprBomb->runAction(sequence);

	setPhysicsBody(_sprBomb);	
	initPhysics();	
	_sprBomb->getPhysicsBody()->setVelocity(Vect(0,-100));	

    return true;
}

// void PlayScene::moveFinished(Node* sender){
// 	CCLOG("Move finished");
// }

void PlayScene::callbackOnPause(cocos2d::Ref* pSender){
	_director->pushScene(TransitionFlipX::create(1.0, ScenePause::createScene()));
}
