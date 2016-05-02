#include "AbilityMissile.h"
#include "Robot.h"

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
     Missile* m = missile_->clone();
     m->setOrientation(caster_->getTurretOrientation());
	 m->setPosition(caster_->getPosition());
     return m;
 }

void AbilityMissile::cast()
 {
	 if( CD_.getFilledAbsolute() == 0 ){
		 Missile* m = sendMissile();
		 caster_->getFightManager()->addMissile( m );
		 CD_.fill();
	 }
 }