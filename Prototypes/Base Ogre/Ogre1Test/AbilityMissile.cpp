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

void AbilityMissile::Cast()
 {
	 if( getCD().getFilledAbsolute() == 0){
		 caster_->getFightManager()->addMissile( sendMissile() );
		 getCD().setCurrent((float) getCD().getMax());

	 }
 }