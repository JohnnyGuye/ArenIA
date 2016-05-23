#include "Missile.h"
#include "HitboxSphere.h"

using namespace Ogre;
using namespace std;

Missile::Missile(const Missile &rhs)
	: GameObject(rhs),
	caster_(rhs.caster_),
	speed_(rhs.speed_),
	damages_(rhs.damages_)
{
	HitboxSphere* hs = (HitboxSphere*)rhs.hitbox_;
	hitbox_ = new HitboxSphere(*hs, &(this->position_));
}

Missile::Missile(Ogre::Vector3 position, const Real& rad, Robot* caster, std::string name)
	: GameObject(position, name),
	caster_(caster),
	hitbox_(new HitboxSphere(&position_, rad)),
	speed_(20.0f),
	damages_(50.0f)
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

Robot* Missile::getCaster() const
{
    return caster_;
}

Hitbox* Missile::getHitbox() const
{
    return hitbox_;
}

void Missile::setCaster(Robot* caster)
{
    caster_ = caster;
}

bool Missile::move()
{
	GameObject::move(speed_ * orientation_);
    return true;
}

void Missile::update()
{
	move();
}

void Missile::onCollide(Robot* r)
{
	if( (r->getTeam() == Robot::NONE) || ( caster_->getTeam() != r->getTeam()) ){
		r->takeDamage( damages_, caster_ );
		kill();
	}
}

std::string Missile::getMesh() const
{
	return "RobotLaveLinge_Projectile.mesh";
}

Ogre::Real Missile::getScale() const
{
	return 20;
}