#include "AppDelegate.h"
#include "PlayScene.h"

USING_NS_CC;

//static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size designResolutionSize = cocos2d::Size(1920,1080);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1920,1080 );
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {

        //glview->setFrameSize(1080, 1920);
        glview = GLViewImpl::create("GameOver");
        glview->setFrameSize(1920, 1080);
        director->setOpenGLView(glview);
    }

  Size screenSize = glview->getFrameSize();
    Size designSize(1920, 1080);
    std::vector<std::string> searchPaths;   

    if (screenSize.height > 800){
        //High Resolution
        searchPaths.push_back("images/high");
        director->setContentScaleFactor(1280.0f / designSize.height);
    }
    else if (screenSize.height > 600){
        //Mid resolution
        searchPaths.push_back("images/mid");
        director->setContentScaleFactor(800.0f / designSize.height);
    }
    else{
        //Low resolution
        searchPaths.push_back("images/low");
        director->setContentScaleFactor(320.0f / designSize.height);
    }
    FileUtils::getInstance()->setSearchPaths(searchPaths);
    glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::NO_BORDER);

    // create a scene. it's an autorelease object
    auto scene = PlayScene::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
