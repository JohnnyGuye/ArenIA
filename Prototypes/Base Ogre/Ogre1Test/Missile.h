#pragma once

#include <OgreVector3.h>
#include <OGRE\OgreSphere.h>
#include "HitboxVoid.h"
#include "Stats.h"
#include "Ability.h"
#include "GameObject.h"
#include "Robot.h"

class Missile : 
	public GameObject
{
public:

	/** @brief Create a new missile
	*
	*	@param position the position where starts the missile
	*	@param hitbox a pointer on a hitbox
	*	@param caster the caster of this missile
	*	@param stats the stats of this missile
	*	@param name the name of this missile
	**/
	Missile(Ogre::Vector3 position = Ogre::Vector3::ZERO,
		const Ogre::Real& radius = 50.f, Robot* caster = nullptr,
		Stats stats = Stats(), std::string name = "unnamed");

	/** @Create a new missile using one other as a model
	**/
	Missile( const Missile &otherMissile );

    /** @brief creates a new missile copying the current instance and returns
    a pointer to it**/
	virtual Missile* clone() const;

	/** Destroy a missile **/
    virtual ~Missile();

	/** @brief to be executed when the missile hits a robot **/
	virtual void onCollide(Robot* r);

	// Getters

    virtual Stats getStats(void) const;

    virtual Robot* getCaster(void) const;

    virtual Hitbox* getHitbox(void) const;

	//Setters

    virtual void setStats(Stats stats);

    virtual void setCaster(Robot* caster);

    virtual bool move();

    virtual void update();

protected:

    Stats stats_;
    Hitbox* hitbox_;
	Robot* caster_;

};
