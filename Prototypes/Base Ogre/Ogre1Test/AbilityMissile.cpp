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
	 //Ogre's addition caps to 360 without cycling and we need it to cycle
	 Ogre::Real valueAngle = caster_->getOrientation().valueDegrees();
	 valueAngle += caster_->getTurretOrientation().valueDegrees() ;
	 if ( valueAngle >= 360 ){ valueAngle-=360; }
	 Ogre::Degree angle( valueAngle );
	 std::cout << angle << std::endl;
	 //std::cout << m->getOrientationVect() << std::endl;
	 m->setOrientation( angle );
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