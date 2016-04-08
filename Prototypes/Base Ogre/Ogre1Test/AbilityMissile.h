#pragma once

#include <OgreVector3.h>
#include "Missile.h"
#include "Ability.h"
 
class AbilityMissile : Ability
{    
public:
     
    /**
	* @brief Create a new ability able to cast missiles
	**/
    AbilityMissile(Missile* missile = nullptr);
    //
    virtual ~AbilityMissile();
     
    //Sends a missile int the direction of the turret
    virtual bool sendMissile(Ogre::Vector3 turretOrientation);
     
    virtual Missile* getMissile() const;
     
    virtual void setMissile(Missile* missile);

protected:
     
    Missile* missile_;
     
};