#pragma once
/**
 * @file Missile.h
 * @author Alp Yücesoy
 */
 
 #include <Ogre.h>
 #include "Stats.h"
 #include "Ability.h"
 #include "GameObject.h"
 
 class Missile : GameObject
 {
     protected:
     
     Stats stats_;
     GameObject caster_;
     Ogre::Vector3 missileDirection_;
     Hitbox hitbox_;
     
     public:
     
     Missile & operator = ( const Missile & otherMissile );
     
     Missile();
     
     Missile(Stats stats, GameObject caster, Ogre::Vector3 missileDirection, Hitbox hitbox);
     
     ~Missile();
     
     Stats getStats();
     
     GameObject getCaster();
     
     Ogre::Vector3 getDirection();
     
     Hitbox getHitbox();
     
     void setStats(Stats stats);
     
     void setCaster(GameObject caster);
     
     void setDirection(Ogre::Vector3 direction);
     
     void setHitbox(Hitbox hitbox);
     
     bool move();
     
     void update();
     
     bool removeAbility();
     
 }