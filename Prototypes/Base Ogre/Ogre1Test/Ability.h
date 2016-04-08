#pragma once
 
#include <string> 
#include "Gauge.h"
 
#define DEFAULT_DAMAGE 10
#define DEFAULT_RANGE 10
#define DEFAULT_SPEED 20.0
 
 
class Ability
{
     
public:
     
    //Main constructor, creates an Ability
    Ability(std::string name = "Dummy", Gauge CD = Gauge(120), Gauge casting = Gauge(30), int damage = 0, int range = 0, double speed = 0);
     
    virtual ~Ability();
     
    //-------------------------------------------- Getters
    /**
	*	@return The CoolDown
	**/
    virtual Gauge getCD() const;
     
	/**
	*	@return the casting time
	**/
    virtual Gauge getCasting() const;
     
    virtual int getDamage() const;
     
    virtual int getRange() const;
     
    virtual double getSpeed() const;
     
    virtual std::string getName() const;
     
    //-------------------------------------------- Setters
     
    virtual void setCD(Gauge CD);
     
    virtual void setCasting(Gauge casting);
     
    virtual void setDamage(int damage);
     
    virtual void setRange(int range);
     
    virtual void setSpeed(double speed);
     
    virtual void setName(std::string name);
     
    //-------------------------------------------- Public Methods
     
    virtual void Cast() = 0;
     
    //------------------------------------------- PROTECTED
     
protected:
     
    Gauge CD_;
    Gauge casting_;
    int damage_;
    int range_;
    double speed_;
    std::string name_;
    
};