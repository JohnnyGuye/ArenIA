#pragma once

/*
* ARENIA project
* Robot.h
*
* @author Simon Belletier
* @summary :  Header file of the Robot Class, a Robot is the main fighting entity.
*/

#include <Ogre.h>
#include <string>
#include <vector>
#include <string>
#include "GameObject.h"
#include "Stats.h"
//#include "Ability.h"

//for the rotations
#define FORWARD_DEFAULT Ogre::Vector3::NEGATIVE_UNIT_Z

enum Team	{
	NONE = 0,
    RED = 1,
    YELLOW = 2,
    GREEN = 4,
    BLUE = 8,
    BLACK = 16,
    WHITE = 32,
    ORANGE = 64,
    };


class Robot: public GameObject
{
    //public methods
    public:

		/** **/
        Robot();

        /** **/
        virtual ~Robot();

        /** @brief  Reset the action state of the Robot to IDLE**/
        virtual bool Robot::resetAction();

		virtual void update();

        /** @brief  Called to make the Robot fire his turret
            @return True after a complete execution**/
        virtual bool fire();

        /** @brief  Called to make the Robot move**/
        virtual bool move();

        /** **/
        virtual bool turnTurret(Ogre::Degree angle);

        /** /!\ doesn't change the turret's orientation as of now **/
        virtual bool turnDirection(Ogre::Degree angle);
		
        /** @brief Use the idxth Ability
            @param idxAbility : The index of the Ability to use
            @return
            
        bool useAbility(int idxAbility);
        /** 
        vector<Ability*> getKnownCompetences(Robot robot);
        /**
        bool addAbility(& Ability);
        /** 
        bool removeAbility(int idxAbility);
		**/
        /** **/
        //MUST RETURN A VECTOR WITH A NORM=1
        virtual Ogre::Vector3 getWheelOrientation() const;
        /** **/
        virtual double getSpeed() const;
        /** **/
        virtual Ogre::Vector3 getTurretOrientation() const;
        /** **/
        virtual Team getTeam() const;
        /** **/
        virtual int getAction() const;
        /** **/
        virtual bool isMoving() const;
        /** **/
        virtual bool isShooting() const;
        /** **/
        virtual bool isIDLE() const;

     

	//attributes
    protected:

        /** The teams to which the Robot Belongs **/
        Team team_;

        /** The base stats of the Robot**/
        Stats stats_;

        /** modifier for the base stats **/
        Stats additionalStats_;

        /** The Robot's abilities **/
        //vector<Ability*> abilities_;

        /** Current actions done by the robot**/
        int action_;

        /** The IA's filename **/
        std::string iaFilename_;

        /**Turret Orientation**/
        Ogre::Vector3 turretOrientation_;

        /**Wheel Orientation **/
        Ogre::Vector3 orientation_;

    //constants
    public:
        /** **/
        static const int TURNING_WHEELS = 1,
                        MOVING = 2,
                        TURNING_TURRET = 4,
                        SHOOTING = 8,
                        IDLE = 0;


};

