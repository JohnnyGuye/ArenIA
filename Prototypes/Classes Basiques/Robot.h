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
//#include "Ability.h"

enum Team{
	NO_TEAM = 0,
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
    //attributes of the class
    protected:

        /** The teams to which the Robot Belongs **/
        Team team_;

        /** The base stats of the Robot**/
        Stats stats_;

        /** modifier for the base stats **/
        Stats additionalStats_;

        /** The Robot's name **/
        std::string name_;

        /** The Robot's abilities **/
        //std::vector<Ability*> abilities_;

        /** Current actions done by the robot**/
        int action_;

        /** The IA's filename **/
        std::string iaFilename_;

    //public methods
    public:

		Robot();
		virtual ~Robot();

        /** @brief  Called to make the Robot fire his turret
            @return  **/
        bool fire();

        /** @brief Use the idxth Ability
            @param idxAbility : The index of the Ability to use
            @return
            **/
        bool useAbility(int idxAbility);

        /** **/
        void getKnownCompetences(Robot robot) const;

        /** **/
        bool addAbility();

        /** **/
        bool removeAbility(int idxAbility);

        /** **/
        //MUST RETURN A VECTOR WITH A NORM=1
        Ogre::Vector3 getWheelOrientation();

        /** **/
        //double getSpeed();

        /** **/
        Ogre::Vector3 getTurretOrientation() const;

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

    //protected methods
    protected:
        /** **/
        bool turnTurret(int angle);
        /** **/
        bool turnDirection(int angle);
        /** **/
    //constants
    public:
        /** **/
        static const int TURNING_WHEELS = 1,
                        MOVING = 2,
                        TURNING_TURRET = 4,
                        SHOOTING = 8,
                        IDLE = 0;


};

