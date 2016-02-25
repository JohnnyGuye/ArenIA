#pragma once
/**
 * @file Gauge.h
 * @author Samory Ka
 * @summary : This class represents a simple gauge.
 */


#define DEFAULT_MAX 100
#define DEFAULT_MIN 0
#define DEFAULT_MODIFIER 1

class Gauge
{
//----------------------------------------------------------------- PUBLIC

public:

//------------------------------------------------- Operators overload
    Gauge & operator = ( const Gauge & otherGauge );





//-------------------------------------------- Constructors - destructor
    /**
     * Copy constructor
     * @param otherGauge Gauge that we want to copy
	*/
    Gauge ( const Gauge & otherGauge );


    /**
     *
     * Default constructor
     * Creates a filled gauge with default values (DEFAULT_MAX and DEFAULT_MIN)
	*/
    Gauge ();

    /**
     * Main constructor
     * This is the constructor you should use the most : it initiates a filled
     * gauge.
     * @param max Maximum value of the gauge
     * @param min Minimum value of the gauge
     * @param modifier Modifier of the gauge
	*/
    Gauge ( int max, int min, double modifier );

    /**
	* Secondary constructor
	* Initiates a not necessarily filled gauge.
	* gauge.
	* @param max Maximum value of the gauge
	* @param min Minimum value of the gauge
	* @param current Current value of the gauge
	* @param modifier Modifier of the gauge
   	*/
    Gauge ( int max, int min, double current, double modifier );

    /**
     * Destructor
     * Destroys an instance of Gauge
     */
    virtual ~Gauge ();

//------------------------------------------------- Public methods

//--------------------------------------GETTERS

    /**
   	* Max getter
   	* Returns the maximum value reachable by the gauge
   	* @return max_ of the gauge
    */
    int getMax();

    /**
	* Min getter
	* Returns the minimum value reachable by the gauge
	* @return min_ of the gauge
	*/
    int getMin();

    /**
	* Current getter
	* Returns the current value value the gauge
	* @return current_ of the gauge
	*/
    double getCurrent();

    /**
	* Modifier getter
	* Returns the modifier the gauge
	* @return modifier_ of the gauge
	*/
    double getModifier();



//--------------------------------------SETTERS

    /**
	* Current setter
	* Sets current_ to value
	* @param value The value that you want current to become
	*/
    void setCurrent( double value );

    /**
	* Modifier setter
	* Sets modifier_ to value
	* @param value The value that you want modifier_ to become
	*/
    void setModifier( double value );

    /**
	* Fills the gauge (sets current_ to max_)
	*/
    void fill();

    /**
	* Empties the gauge (sets current_ to min_)
	*/
	void empty();


	/**
	 * Updates the current value of the gauge.
	 */
    void update();


//----------------------------------------------------------------- PROTECTED
protected:
//------------------------------------------------------- Protected attributes
    int max_;	///< Maximum value of the gauge
    int min_;	///< Minimum value of the gauge
    double current_;	///< Current value of the gauge
    double modifier_;	///< Modifier of the current gauge : value of the evolution
    					///< of current_ at the beginning of a round


};


