#pragma once

/**
 * @file Gauge.h
 * @author Samory Ka
 * @summary : This class represents a simple gauge.
 */

class Gauge
{
//----------------------------------------------------------------- PUBLIC

public:

//-------------------------------------------- Constructors - destructor
    /** @brief Copy constructor
     * @param otherGauge Gauge that we want to copy*/
    Gauge ( const Gauge & otherGauge )
		: max_(otherGauge.max_),
		min_(otherGauge.min_),
		current_(otherGauge.current_),
		modifier_(otherGauge.modifier_)
	{
	}

    /**
	* Initiates a not necessarily filled gauge.
	* gauge.
	* @param borne1 Maximum value of the gauge
	* @param borne2 Minimum value of the gauge
	* @param current Current value of the gauge
	* @param modifier Modifier of the gauge
   	*/
    Gauge ( int borne1 = 100, int borne2 = 0, float current = 100, float modifier =  0.0)
		: modifier_(modifier)
	{
		max_ = (borne1 >= borne2 ? borne1 : borne2);
		min_ = (borne1 <= borne2 ? borne1 : borne2);
		setCurrent(current);
	}

    /**
     * Destructor
     * Destroys an instance of Gauge
     */
    virtual ~Gauge ()
	{
	}

	Gauge& operator+=(Gauge const& rhs);
	Gauge& operator-=(Gauge const& rhs);
//------------------------------------------------- Public methods
	/// Tells if the Gauge is fullfilled
	/// @return true if fullfilled
	inline bool IsFull() const{		return current_ == (double)max_;	}

	/// Tells if the Gauge is empty
	/// @return true if empty
	inline bool IsEmpty() const {	return current_ == (double)min_;	}

//--------------------------------------GETTERS

    /**
   	* Max getter
   	* Returns the maximum value reachable by the gauge
   	* @return max_ of the gauge
    */
	inline int getMax() const{	return max_;	}

    /**
	* Min getter
	* Returns the minimum value reachable by the gauge
	* @return min_ of the gauge
	*/
	inline int getMin() const {	return min_;	}

    /**
	* Current getter
	* Returns the current value value the gauge
	* @return current_ of the gauge
	*/
	inline float getCurrent() const {	return current_;	}

	/** @return the the filled portion of the gauge **/
	inline float getFilledAbsolute() const {	return current_-min_;	}

	/** @return the notfilled portion of the gauge **/
	inline float getNotFilledAbsolute() const {	return max_-current_;	}

	/** @return the filled percent of the gauge **/
	inline float getRatio() const {	return current_ / (float)(max_-min_);	}

    /**
	* Modifier getter
	* Returns the modifier the gauge
	* @return modifier_ of the gauge
	*/
	inline float getModifier() const {	return modifier_;	}



//--------------------------------------SETTERS

	///Current setter
	///Sets current_ to value
	///@param value The value that you want current to become
    inline void setCurrent( float value )
	{
		if(value > max_)		current_ = (float)max_;
		else if(value < min_)	current_ = (float)min_;
		else					current_ = value;
	}

    
	///Modifier setter
	///Sets modifier_ to value
	///@param value The value that you want modifier_ to become
    inline void setModifier( float value = 0.0)
	{
		modifier_ = value;
	}

    ///Fills the gauge (sets current_ to max_)
    inline void fill()
	{
		current_ = (float)max_;
	}

    ///Empties the gauge (sets current_ to min_)
	inline void empty()
	{
		current_ = (float)min_;
	}

	///Updates the current value of the gauge.
    inline void update()
	{
		setCurrent(current_ + modifier_);
	}


//----------------------------------------------------------------- PROTECTED
protected:
//------------------------------------------------------- Protected attributes
    int max_;	///< Maximum value of the gauge
    int min_;	///< Minimum value of the gauge
    float current_;	///< Current value of the gauge
    float modifier_;	///< Modifier of the current gauge : value of the evolution
    					///< of current_ at the beginning of a round
};

Gauge operator+(Gauge const& lhs, Gauge const& rhs);
Gauge operator-(Gauge const& lhs, Gauge const& rhs);


