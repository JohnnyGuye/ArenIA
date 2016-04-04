#pragma once
/**
 * @file Ability.h
 * @author Alp Yücesoy
 */
 
 #include <string>
 #include "Gauge.h"
 
 
 #define DEFAULT_DAMAGE 10
 #define DEFAULT_RANGE 10
 #define DEFAULT_SPEED 20.0
 
 
 class Ability
 {
     //--------------------------------------------PUBLIC
     
     public:
     
     //--------------------------------------------Constructors / Destructors
     
     //Default constructor, mostly not used
     Ability();
     
     //Main constructor, creates an Ability
     Ability(Gauge CD, Gauge casting, int damage, int range, double speed, string name);
     
     //--
     ~Ability();
     
     //-------------------------------------------- Getters
     
     Gauge getCD();
     
     Gauge getcasting();
     
     int getdamage();
     
     int getrange();
     
     double getspeed();
     
     string getname();
     
     //-------------------------------------------- Setters
     
     void setCD(Gauge CD);
     
     void setcasting(Gauge casting);
     
     void setdamage(int damage);
     
     void setrange(int range);
     
     void setspeed(double speed);
     
     void setname(string name);
     
     //-------------------------------------------- Public Methods
     
     void Do();
     
     //------------------------------------------- PROTECTED
     
     protected:
     
     Gauge CD_;
     Gauge casting_;
     int damage_;
     int range_;
     double speed_;
     string name_;
     
 }