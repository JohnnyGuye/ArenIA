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
	 //for some reason, here specifying the class from which the method is taken seems to stop the segfault
	 //It apparently comes from the fact the GameObject Class is virtual
     Missile* m = missile_->clone();
	 std::cout << caster_->GameObject::getOrientation() << std::endl;
	 Ogre::Degree an = caster_->GameObject::getOrientation();
	 an += caster_->Robot::getTurretOrientation();
     m->setOrientation(an);
	 m->setPosition( caster_->GameObject::getPosition() );
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