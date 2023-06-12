#ifndef __MOTION_H
#define __MOTION_H


#include "atomic.h"     // class Atomic

class Motion : public Atomic {
public:
	Motion ( const string &name = "Motion" );	//Default constructor
   virtual string className() const ;

protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &Command;
	Port &Done;
	Port &J1_Position;
	Port &J2_Position;
	Port &Efficiency;
	Time TimeOUT, MoveTime;

	int IDLE;
	int STOPPED;
	int MOVING;
	int Current_State;

	long int mCommand;
	ldiv_t Command_Div;
	short int Command_Digit;

	int degree1;
	int degree2;
	int command;
	int random_number;
	static int eCounter;
	static int total;
	static double eTime;
	bool Five_Percent;

}; // class Motion

inline
string Motion::className() const
{
	return "Motion" ;
}

#endif   //__MOTION_H

