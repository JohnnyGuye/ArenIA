/**
 * @file AbilityMissile.cpp
 * @author Alp Yücesoy
 */
 #include <Ogre.h>
 #include "AbilityMissile.h"
 #include "Missile.h"
 
 AbilityMissile::AbilityMissile()
 {
     
 }
 
 AbilityMissile::AbilityMissile(Missile missile)
 {
     missile_ = missile;
 }
 
 Missile AbilityMissile::getMissile()
 {
     return missile_;
 }
 
 void AbilityMissile::setMissile(Missile missile)
 {
     missile_ = missile;
 }
 
 bool AbilityMissile:sendMissile(Ogre::Vector3 turretOrientation);
 {
     missile_.setDierction(turretOrientation);
     missile_.move();
     return true;
 }