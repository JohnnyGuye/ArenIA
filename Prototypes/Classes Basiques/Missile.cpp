/**
 * @file Missile.cpp
 * @author Alp Yücesoy
 */
 
 #include <Ogre.h>
 #include "Stats.h"
 #include "Ability.h"
 #include "GameObject.h"
 #include "Missile.h"
 
 
 Missile & Missile::operator = ( const Missile & otherMissile)
 {
     this->stats_ = otherMissile.stats_;
     this->caster = otherMissile.caster;
     this->missileDirection_ = otherMissile.missileDirection_;
     this->hitbox_ = otherMissile.hitbox_;
     
     return this*;
 }
 
 Missile::Missile()
 {
     
 }
 
 Missile::Missile(Stats stats, GameObject caster, Ogre::Vector3 missileDirection, Hitbox hitbox)
 {
     stats_ = stats;
     caster_ = caster;
     missileDirection_ = missileDirection;
     hitbox_ = hitbox;
 }
 
 Missile::~Missile()
 {
     
 }
 
 Stats Missile::getStats()
 {
     return stats_;
 }
 
 GameObject Missile::getCaster()
 {
     return caster_;
 }
 
 Ogre::Vector3 getDirection()
 {
     return missileDirection_;
 }
 
 Hitbox Missile::getHitbox();
 {
     return hitbox_;
 }
 
 void Missile::setStats(Stats stats)
 {
     stats_ = stats;
 }
 
 void Missile::setCaster(GameObject caster)
 {
     caster_ = caster;
 }
 
 void Missile::setHitbox(Hitbox hitbox)
 {
     hitbox_ = hitbox;
 }
 
 bool Missile::move()
 {
     double speed = stats_.getSpeed();
     GameObject::Move(speed * missileDirection_);
     return true;
 }
 
 void update()
 {
         Missile::move();
 }
 
 bool Missile::removeAbility()
 {
     //For now does nothing.
     return true;
 }