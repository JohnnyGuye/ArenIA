#pragma once

#include "Scene.h"
#include <OgreSceneManager.h>
#include "FightManager.h"
#include "GUIConsole.h"
#include "GUIDecompte.h"
#include "HUD.h"
#include <SdkCameraMan.h>

class FightScene :
	public Scene
{
protected:

	enum RenderState {
		CONSOLE_ON,
		GAME,
		COUNTDOWN
	};

	class Sun
	{
	public:
		/** Create a sun, be sure note te create two or more Suns, it will cause problems **/
		Sun(FightScene* fs);
		virtual~Sun();
		void update();
	protected:
		FightScene*			fs_;
		Ogre::SceneNode*	node_;
		Ogre::SceneManager* sceneMgr_;
		Ogre::Light*		light_;

		static const int ORBIT = 100 * Terrain::CELL_SIZE;
		Ogre::Vector2 offset_;
	};

	class GameEntity
	{
	public:
		GameEntity(FightScene* fs, const std::string& mesh, const Ogre::Vector3& position, const Ogre::Real& scale, GameObject * object = nullptr);
		virtual~GameEntity();
		virtual void update(const Ogre::FrameEvent& evt);
	protected:
		FightScene*				fs_;
		Ogre::Entity*			entity_;
		Ogre::Degree			orientation_;
		Ogre::SceneNode*		node_;
		GameObject*				object_;
		Ogre::AnimationState*	animState_;
	};

	class RobotEntity : 
		GameEntity
	{
	public:
		RobotEntity(FightScene* fs, const std::string& mesh, const Ogre::Vector3& position, const Ogre::Real& scale, Robot* robot);
		virtual~RobotEntity();
		virtual void update(const	Ogre::FrameEvent& evt);
		inline virtual std::string stateToString(const Robot::State& state) const;
	protected:
	};

public:
	FightScene(void);
	virtual ~FightScene(void);

	virtual bool launch(void);
	virtual bool initFightManager(const std::string& map);

	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	virtual Scenes nextScene(void) const;

	virtual void destroyScene(void);

	virtual bool keyPressed(const OIS::KeyEvent &arg);
	virtual bool keyReleased(const OIS::KeyEvent &arg);
    virtual bool mouseMoved(const OIS::MouseEvent &arg);
    virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

protected:
	virtual void _loadResources(void);

	virtual void createEntity(const std::string& mesh, const Ogre::Vector3& position, const Ogre::Real& scale = 1);
	virtual void createRobot(const std::string& name, const Robot::Type& type, const Robot::Team& team = Robot::NONE, const Ogre::Vector3& position = Ogre::Vector3::ZERO, const Ogre::Real& scale = 1);
	virtual void createRobots(void);
	virtual void createScene(void);

protected:
	FightManager*		fightManager_;	// The logic of the game 

	std::vector<Ogre::Entity*>	DecorEntities_; // The entities corresponding to the scenery 
	std::list<RobotEntity>		robotsEntities_; // The robots to carry 
	std::list<GameEntity>		objectEntities_;	// The other objects to carry
	Sun*						theSun_;// The sun

	RenderState		state_;
	bool			pause_;
	OgreBites::SdkCameraMan*		cameraMan_;

	GUIConsole*		console_;
	GUIDecompte*	decompte_;
	HUD*			hud_;
	float			displaySpeed_;
	Ogre::Real		lag_;
};

