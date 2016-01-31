#ifndef _PLAYSCENE_H
#define _PLAYSCENE_H

#include "cocos2d.h"

class PlayScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void callbackOnPause(cocos2d::Ref* pSender);
 	//void moveFinished(cocos2d::Node* sender);

	CREATE_FUNC(PlayScene);
private:
	cocos2d::Director *_director;
	cocos2d::Size _visibleSize;	
	cocos2d::Sprite* _sprBomb;
	cocos2d::Sprite* _sprPlayer;
	void initPhysics();
	bool onCollision(cocos2d::PhysicsContact& contact);
	void setPhysicsBody(cocos2d::Sprite* sprite);

	void initTouch();
	void movePlayerByTouch(cocos2d::Touch* touch, cocos2d::Event* event);
	void movePlayerIfPossible(float newX);

	void movePlayerByAccelerometer(cocos2d::Acceleration* acceleration, cocos2d::Event* event);
	void initAccelerometer();

	void initBackButtonListener();
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
};

#endif // __SCENE_PAUSE_H__