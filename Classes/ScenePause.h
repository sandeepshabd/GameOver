#ifndef __SCENE_PAUSE_H__
#define __SCENE_PAUSE_H__

#include "cocos2d.h"

class ScenePause : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void closeScenePause(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(ScenePause);

private:
	cocos2d Director *_director;
	cocos2d Size _visibleSize;    
};

#endif // __SCENE_PAUSE_H__
