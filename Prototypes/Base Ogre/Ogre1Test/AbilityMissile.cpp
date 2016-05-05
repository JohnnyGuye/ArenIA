#include "AbilityMissile.h"
#include "Robot.h"

 AbilityMissile::AbilityMissile(Robot* caster)
	 : Ability(caster)
 {
     missile_ = new Missile(Ogre::Vector3::ZERO, 50.f, caster);
 }

 AbilityMissile::~AbilityMissile()
 {
	 if(missile_) delete missile_;
 }

 Missile* AbilityMissile::getMissile() const
 {
     return missile_;
 }

 void AbilityMissile::setMissile(Missile missile)
 {
	 if(missile_) delete missile_;
     missile_ = new Missile(missile);
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
	 if( CD_.IsEmpty() ){
		 Missile* m = sendMissile();
		 caster_->getFightManager()->addMissile( m );
		 CD_.fill();
	 }
 }