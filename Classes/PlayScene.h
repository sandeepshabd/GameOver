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
	void initPhysics();
	bool onCollision(cocos2d::PhysicsContact& contact);
	void setPhysicsBody(cocos2d::Sprite* sprite);
};

#endif // __SCENE_PAUSE_H__