#ifndef _PLAYSCENE_H
#define _PLAYSCENE_H

#include "cocos2d.h"

class PlayScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void pauseCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(PlayScene);
	void moveFinished(cocos2d::Node* sender);
private:
	cocos2d::Director *_director;
	cocos2d::Size _visibleSize;	
};

#endif // __SCENE_PAUSE_H__