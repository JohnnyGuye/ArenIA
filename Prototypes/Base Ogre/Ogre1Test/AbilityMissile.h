#pragma once

#include <OgreVector3.h>
#include "Missile.h"
#include "Ability.h"
#include "FightManager.h"

class AbilityMissile : 
	public Ability
{
public:

    /**
	* @brief Create a new ability able to cast missiles
	**/
    AbilityMissile(Missile* missile = nullptr);
    //
    virtual ~AbilityMissile();

    //Sends a missile int the direction of the turret
    virtual Missile* sendMissile();

    virtual Missile* getMissile() const;

    virtual void setMissile(Missile* missile);

	virtual void Cast();

protected:

    Missile* missile_;

};
