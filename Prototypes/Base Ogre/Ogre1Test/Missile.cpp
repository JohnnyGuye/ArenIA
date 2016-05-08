#include "Missile.h"
#include "HitboxSphere.h"

using namespace Ogre;
using namespace std;

Missile::Missile(const Missile &rhs)
	: GameObject(rhs),
	stats_(rhs.stats_),
	caster_(rhs.caster_),
	hitbox_(rhs.hitbox_->clone())
{
}

Missile::Missile(Ogre::Vector3 position, const Real& rad, GameObject* caster, Stats stats, std::string name)
	: GameObject(position, name),
	stats_(stats),
	caster_(caster),
	hitbox_(new HitboxSphere(&position_, rad))
{
	position_.y += 20;
}

Missile* Missile::clone() const
{
    return new Missile(*this);
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

bool Missile::move()
{
	std::cout<< "missile moves " <<orientation_<<std::endl;
	GameObject::move(stats_.speed * orientation_);
    return true;
}

void Missile::update()
{
	move();
}
