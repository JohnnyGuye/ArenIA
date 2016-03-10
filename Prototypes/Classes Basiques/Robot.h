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

#include "Stats.h"
#include "Ability.h"

enum Team{
    red=1,
    yellow=2,
    green=4,
    blue=8,
    black=16,
    white=32,
    orange=64,
    };


class Robot: public Object
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
        string name_;
        /** The Robot's abilities **/
        vector<Ability*> abilities_;
        /** Current actions done by the robot**/
        int action_;
        /** The IA's filename **/
        string iaFilename_;

    //public methods
    public:
        /** @brief  Called to make the Robot fire his turret
            @return  **/
        bool fire();
        /** @brief Use the idxth Ability
            @param idxAbility : The index of the Ability to use
            @return
            **/
        bool useAbility(int idxAbility);
        /** **/
        void getKnownCompetence(Robot robot);
        /** **/
        bool addAbility();
        /** **/
        bool removeAbility();
        /** **/
        //MUST RETURN A VECTOR WITH A NORM=1
        Ogre::Vector3 getWheelOrientation();
        /** **/
        int getSpeed();
        /** **/
        Ogre::Vector3 getTurretOrientation();
        /** **/
        Team getTeam();

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

