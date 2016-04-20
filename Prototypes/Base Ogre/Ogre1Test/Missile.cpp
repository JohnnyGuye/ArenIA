#include "Missile.h"
 
using namespace Ogre;
using namespace std;
 
Missile::Missile(const Missile &rhs)
	: GameObject(rhs),
	stats_(rhs.stats_),
	caster_(rhs.caster_),
	hitbox_(hitbox_)
{   
}
 
Missile::Missile(Ogre::Vector3 position, Hitbox* hitbox, GameObject* caster, Stats stats, std::string name)
	: GameObject(position, name),
	stats_(stats),
	caster_(caster),
	hitbox_(hitbox)
{
}
 
Missile::~Missile()
{
     if(hitbox_) delete hitbox_;
}
 
Stats Missile::getStats() const
{
    return stats_;
}
 
GameObject* Missile::getCaster() const
{
    return caster_;
}
 
Hitbox* Missile::getHitbox() const
{
    return hitbox_;
}
 
void Missile::setStats(Stats stats)
{
    stats_ = stats;
}
 
void Missile::setCaster(GameObject* caster)
{
    caster_ = caster;
}
 
void Missile::setHitbox(Hitbox* hitbox)
{
    hitbox_ = hitbox;
}
 
bool Missile::move()
{
    double speed = stats_.speed;
    //GameObject::move(speed * missileDirection_);
    return true;
}
 
void Missile::update()
{
        move();
}