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
    Gauge ( int borne1 = 100, int borne2 = 0, double current = 100, double modifier =  0.0)
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

//------------------------------------------------- Public methods

	inline bool IsFull() const{	return (int)current_ == max_;	}

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
	inline double getCurrent() const {	return current_;	}

	/** @return the the filled portion of the gauge **/
	inline double getFilledAbsolute() const {	return current_-min_;	}

	/** @return the notfilled portion of the gauge **/
	inline double getNotFilledAbsolute() const {	return max_-current_;	}

	/** @return the filled percent of the gauge **/
	inline double getPercent() const {	return current_ / (double)(max_-min_);	}

    /**
	* Modifier getter
	* Returns the modifier the gauge
	* @return modifier_ of the gauge
	*/
	inline double getModifier() const {	return modifier_;	}



//--------------------------------------SETTERS

    /**
	* Current setter
	* Sets current_ to value
	* @param value The value that you want current to become
	*/
    inline void setCurrent( double value )
	{
		if(value > max_)		current_ = max_;
		else if(value < min_)	current_ = min_;
		else					current_ = value;
	}

    /**
	* Modifier setter
	* Sets modifier_ to value
	* @param value The value that you want modifier_ to become
	*/
    inline void setModifier( double value = 0.0)
	{
		modifier_ = value;
	}

    /**
	* Fills the gauge (sets current_ to max_)
	*/
    inline void fill()
	{
		current_ = max_;
	}

    /**
	* Empties the gauge (sets current_ to min_)
	*/
	inline void empty()
	{
		current_ = min_;
	}

	/**
	 * Updates the current value of the gauge.
	 */
    inline void update()
	{
		setCurrent(current_ + modifier_);
	}


//----------------------------------------------------------------- PROTECTED
protected:
//------------------------------------------------------- Protected attributes
    int max_;	///< Maximum value of the gauge
    int min_;	///< Minimum value of the gauge
    double current_;	///< Current value of the gauge
    double modifier_;	///< Modifier of the current gauge : value of the evolution
    					///< of current_ at the beginning of a round


};


