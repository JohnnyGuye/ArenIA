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

 Missile* AbilityMissile::sendMissile()
 {
     //missile_->setDirection(turretOrientation);
     Missile* m = missile_.Clone();
     m->setOrientation(caster_->getTurretOrientation());
     return m;
 }
