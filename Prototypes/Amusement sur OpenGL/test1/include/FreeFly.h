#ifndef FREEFLY_H
#define FREEFLY_H

#include <map>
#include <cmath>
#include <SFML/System.hpp>
#include "Vector3.h"
#include <SFML/Window.hpp>

class FreeFly
{
	public:
		FreeFly(const Vector3 & position = Vector3(0, 0, 0));

		/**
		* @brief Called when the mouse is in motion
		*/
		virtual void OnMouseMotion(const sf::Event::MouseMoveEvent &event);

		/**
		* @brief Called when a Mouse Button is clicked
		**/
		virtual void OnMouseBoutton(const sf::Event::MouseButtonEvent &event);

		/**
		* @brief Called when you press a key
		**/
		virtual void OnKeyBoard(const sf::Event::KeyEvent &event);

		virtual void Animate(int timestep);

		virtual void SetSpeed(float speed);

		virtual void SetSensitivity(float sensitivity);

		/**
		* Change the position of the camera
		**/
		virtual void SetPosition (const Vector3 &position);

		/**
		* Actualize the camera
		**/
		virtual void look();

		virtual ~FreeFly();

	protected:
		void VectorsFromAngles();

	protected:
		float  m_speed,	/// The translation speed of the camera
			m_sensitivity;	///The rotation speed of the camera

		bool m_vMotionActive,	/// True if the camera is moving up or down
			m_hMotionActive;	/// True if the camera is moving left or right

		typedef std::map<sf::Keyboard::Key, bool> KeyStates;
		KeyStates m_keyStates///Maping the KeysStates

		Vector3 m_position, ///The position of the camera
			m_target,	///The point the camera is looking at
			m_forward,	///The direction of forward movement
			m_left;	///The direction of left movement

		float m_theta,	///The angle between the x axis of the camera an the modelview
			m_phi;	///The angle between the z axis of the camera


};

#endif // FREEFLY_H
