#include "HelloWorldScene.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::node();
	
	// 'layer' is an autorelease object
	HelloWorld *layer = HelloWorld::node();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !CCColorLayer::initWithColor( ccc4(255,255,255,255) ) )	{
		return false;
	}

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	CCMenuItemImage *pCloseItem = CCMenuItemImage::itemFromNormalImage(
										"CloseNormal.png",
										"CloseSelected.png",
										this,
										menu_selector(HelloWorld::menuCloseCallback) );
	pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::menuWithItems(pCloseItem, NULL);
	pMenu->setPosition( CCPointZero );
	this->addChild(pMenu, 1);

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCSprite* player = CCSprite::spriteWithFile("Player.png", CCRectMake(0, 0, 27, 40));

	// position the sprite on the center of the screen
	player->setPosition( ccp(player->getContentSize().width/2, size.height/2) );

	// add the sprite as a child to this layer
	this->addChild(player, 0);
	
    this->schedule( schedule_selector(HelloWorld::gameLogic), 1.0 );
   
	return true;
}

void HelloWorld::gameLogic(cocos2d::ccTime dt)
{
    this->addTarget();
}

void HelloWorld::addTarget()
{
	CCSprite *target = CCSprite::spriteWithFile("Target.png", CCRectMake(0, 0, 27, 40));
	
    // Determine where to spawn the target along the Y axis
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	int minY = target->getContentSize().height/2;
	int maxY = winSize.height - target->getContentSize().height/2;
	int rangeY = maxY - minY;
	int actualY = (arc4random() % rangeY) + minY;
	
    // Create the target slightly off-screen along the right edge,
    // and along a random position along the Y axis as calculated above
	target->setPosition(ccp(winSize.width + target->getContentSize().width/2, actualY));
	this->addChild(target);
	
	// Determine speed of the target
	int minDuration = 2.0;
	int maxDuration = 4.0;
	int rangeDuration = maxDuration - minDuration;
	int actualDuration = (arc4random() % rangeDuration) + minDuration;

    // Create the actions
	CCFiniteTimeAction *actionMove = CCMoveTo::actionWithDuration(actualDuration, ccp(-target->getContentSize().width/2, actualY));
	CCFiniteTimeAction *actionMoveDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(HelloWorld::spriteMoveFinished));
    
    target->runAction(CCSequence::actions(actionMove, actionMoveDone));
}

void HelloWorld::spriteMoveFinished(CCNode* sender)
{
    CCSprite *sprite = (CCSprite *)sender;
    this->removeChild(sprite, true);
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
