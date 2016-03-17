/*
* ARENIA project
* Robot.h
*
* @author Simon Belletier
* @summary :  Header file of the Robot Class, a Robot is the main fighting entity.
*/


#pragma once


#include <Ogre.h>
#include <string>
#include <vector>
#include "GameObject.h"
#include "Stats.h"
#include "Ability.h"

//for the rotations
#define FORWARD_DEFAULT Ogre::Vector3::NEGATIVE_UNIT_Z


enum Team{
	none=0,
    red=1,
    yellow=2,
    green=4,
    blue=8,
    black=16,
    white=32,
    orange=64,
    };


class Robot: public GameObject
{
    //attributes of the class
    protected:
        /** The teams to which the Robot Belongs **/
        Team team_;
        /** The base stats of the Robot**/
        Stats stats_;
        /** modifier for the base stats **/
        Stats additionalStats_;
        /** The Robot's abilities **/
        vector<Ability*> abilities_;
        /** Current actions done by the robot**/
        int action_;
        /** The IA's filename **/
        string iaFilename_;
        /**Turret Orientation**/
        Ogre::Vector3 turretOrientation_;
        /**Wheel Orientation **/
        Ogre::Vector3 orientation_;

    //public methods
    public:
        /** @brief  Reset the action state of the Robot to IDLE**/
        bool Robot::resetAction();
        /** @brief  Called to make the Robot fire his turret
            @return True after a complete execution**/
        bool fire();
        /** @brief  Called to make the Robot move**/
        bool move();
        /** **/
        bool turnTurret(Ogre::Degree angle);
        /** /!\ doesn't change the turret's orientation as of now **/
        bool turnDirection(Ogre::Degree angle);

        /** @brief Use the idxth Ability
            @param idxAbility : The index of the Ability to use
            @return
            **/
        bool useAbility(int idxAbility);
        /** **/
        vector<Ability*> getKnownCompetences(Robot robot);
        /** **/
        bool addAbility(& Ability);
        /** **/
        bool removeAbility(int idxAbility);

        /** **/
        //MUST RETURN A VECTOR WITH A NORM=1
        Ogre::Vector3 getWheelOrientation();
        /** **/
        double getSpeed();
        /** **/
        Ogre::Vector3 getTurretOrientation();
        /** **/
        Team getTeam() const;
        /** **/
        int getAction() const;
        /** **/
        bool isMoving() const;
        /** **/
        bool isShooting() const;
        /** **/
        bool isIDLE() const;

        /** **/
        Robot();
        /** **/
        ~Robot();

    //constants
    public:
        /** **/
        static const int TURNING_WHEELS = 1,
                        MOVING = 2,
                        TURNING_TURRET = 4,
                        SHOOTING = 8,
                        IDLE = 0;


};

