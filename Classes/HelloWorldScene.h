#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::CCColorLayer
{
public:
	
	~HelloWorld();
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();
	
	void addTarget();
    
    void spriteMoveFinished(CCNode* sender);

	void gameLogic(cocos2d::ccTime dt);
	
	void update(cocos2d::ccTime dt);
	
	// a selector callback
	virtual void menuCloseCallback(CCObject* pSender);

	// implement the "static node()" method manually
	LAYER_NODE_FUNC(HelloWorld);
	
private:
	void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	
	cocos2d::CCMutableArray<cocos2d::CCSprite*> *_targets;
	cocos2d::CCMutableArray<cocos2d::CCSprite*> *_projectiles;
};

#endif // __HELLOWORLD_SCENE_H__
