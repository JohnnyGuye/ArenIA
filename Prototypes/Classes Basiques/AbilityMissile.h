#pragma once
/**
 * @file AbilityMissile.h
 * @author Alp Yücesoy
 */
 #include <Ogre.h>
 #include "Missile.h"
 #include "Ability.h"
 
 class AbilityMissile : Ability
 {
     protected:
     
     Missile missile_;
     
     public:
     
     //Default constructor, mostly not used
     AbilityMissile();
     
     //Main constructor, creates a missile object
     AbilityMissile(Missile missile);
     //
     ~AbilityMissile();
     
     //Sends a missile int the direction of the turret
     bool sendMissile(Ogre::Vector3 turretOrientation);
     
     Missile getMissile();
     
     void setMissile(Missile missile);
     
 }