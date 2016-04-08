 #include "AbilityMissile.h"
 
 AbilityMissile::AbilityMissile(Missile* missile)
 {
     missile_ = missile;
 }

 AbilityMissile::~AbilityMissile()
 {
	 if(missile_) delete missile_;
 }
 
 Missile* AbilityMissile::getMissile() const
 {
     return missile_;
 }
 
 void AbilityMissile::setMissile(Missile* missile)
 {
     missile_ = missile;
 }
 
 bool AbilityMissile::sendMissile(Ogre::Vector3 turretOrientation)
 {
     //missile_->setDirection(turretOrientation);
     missile_->move();
     return true;
 }