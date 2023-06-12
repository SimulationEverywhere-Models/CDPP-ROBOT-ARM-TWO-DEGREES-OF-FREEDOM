/*******************************************************************
*
*  DESCRIPTION: Atomic Model Motion
*
*  AUTHOR: Saeed Ahmadi
*
*  EMAIL: mailto://Sahmadi1@connect.carleton.ca
*
*  DATE: 27/12/2011
*
*******************************************************************/

/** include files **/
   // class Motion
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )
#include "stdlib.h"
#include "time.h"		// For random ans srand and time
#include "unistd.h"		// For sleep() function
#include "Motion.h"

Motion::Motion( const string &name )
: Atomic( name )
, Command(this-> addInputPort( "Command"))
, Done (this -> addOutputPort("Done"))
, J1_Position (this -> addOutputPort("J1_Position"))
, J2_Position (this -> addOutputPort("J2_Position"))
, Efficiency (this -> addOutputPort ("Efficiency"))
{

  string time( MainSimulator::Instance().getParameter(this->description(), "timeout" ) ) ;

   if( time != "" ) TimeOUT = time ;
}

int Motion::eCounter=0;
int Motion::total=0;
double Motion::eTime=100;

/*******************************************************************
* Function Name: initFunction
* Description:
* Precondition:
********************************************************************/
Model &Motion::initFunction()
{
	// initializing the common variables
	mCommand=0;
	div_t Command_Div;
	Command_Digit=9;
	degree1=500;
	degree2=500;
	command=0;
	IDLE=0;
	STOPPED=3;
	MOVING=2;
	Current_State=IDLE;
	Five_Percent=false;

	this-> passivate();
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description:
********************************************************************/
Model &Motion::externalFunction( const ExternalMessage &msg )
{

	if (msg.port()==Command) {

		mCommand= static_cast < long int > (msg.value());
		Command_Div= ldiv(mCommand,1000000);    // this will return the first digit of the number that represents the type of command.

		Command_Digit= Command_Div.quot;
		mCommand=static_cast < long int > (Command_Div.rem);
		if (Command_Digit==2)
					{
						Current_State=MOVING;
					}
		else if (Command_Digit==3)
					{
						Current_State=STOPPED;
					}

		if (Command_Digit==2)
		{
			srand ( time(NULL) );
			random_number = (rand()%100); // Generates a random number between 0 to 100
			total++;
			sleep(1); // This creates one second delay so that srand can bee initiate from seperate times and not having same number.
			if (random_number < 4)
			{
				Five_Percent=true;
				eCounter++;
				eTime = (100 * (total-eCounter))/total;
				Command_Digit=9;
				holdIn(active,TimeOUT);
			}else
				if (random_number >= 4)
				{
					Command_Div=ldiv(mCommand,1000);
					degree1= static_cast < int > (Command_Div.quot);  // the first 3 digit of angle in degrees for Joint one
					degree2= static_cast < int > (Command_Div.rem);    // the second 3 digit of angle in degrees for Joint two

					if (degree1 >= degree2)
						 MoveTime = Time (0,0,0,degree1);
					else MoveTime =  Time (0,0,0,degree2);

					holdIn(active, MoveTime); /// MoveTim is a time require for the move of the joint with longer movement.
				}
		}
		else if (Command_Digit==3)
				{
					holdIn(active,Time::Zero);
				}
	}


	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description:
********************************************************************/
Model &Motion::internalFunction( const InternalMessage & )
{
	Current_State=IDLE;
	if (Five_Percent)Five_Percent=false;
	this-> passivate();
	return *this ;
}
/*******************************************************************
* Function Name: outputFunction
* Description:
********************************************************************/
Model &Motion::outputFunction( const InternalMessage &msg )
{

	if (Command_Digit==2 && Current_State==MOVING)
	{
		sendOutput ( msg.time(), Done, this-> Command_Digit);
		//sendOutput (msg.time(), Done, this-> random_number); // only used to run as atomic model (to see the output)
		sendOutput (msg.time(), J1_Position, this-> degree1);
		sendOutput (msg.time(), J2_Position, this-> degree2);

	}

	if (Command_Digit==3 && Current_State==STOPPED)
	{
		sendOutput ( msg.time(), Done, this-> Command_Digit);
	}

	if (Five_Percent && Current_State==MOVING)
	{
		//sendOutput (msg.time(), Efficiency, this-> random_number);	// only used to run as atomic model (to see the output)
		sendOutput ( msg.time(), Efficiency, this-> eTime);
		sendOutput ( msg.time(), Done, this-> Command_Digit);
	}

	return *this ;
}

