/*******************************************************************
*
*  DESCRIPTION: Atomic Model Joint1
*
*  AUTHOR: Saeed Ahmadi
*
*  EMAIL: mailto://Sahmadi1@connect.carleton.ca
*
*  DATE: 27/12/2011
*
*******************************************************************/

/** include files **/
   // class Joint1
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )
#include "stdlib.h"
#include "Joint1.h"

Joint1::Joint1( const string &name )
: Atomic( name )
, Homing(this-> addInputPort( "Homing"))
, Done (this -> addOutputPort("Done"))
{

  string time( MainSimulator::Instance().getParameter(this->description(), "homingtime" ) ) ;

   if( time != "" )
	homingTime = time ;
}
int Joint1::Init=0;
bool Joint1::Homed=false;
/*******************************************************************
* Function Name: initFunction
* Description:
* Precondition:
********************************************************************/
Model &Joint1::initFunction()
{
	Stopped = false;
	this-> passivate();
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description:
********************************************************************/
Model &Joint1::externalFunction( const ExternalMessage &msg )
{
	if (msg.port()==Homing) Command=msg.value();
	{
		if (Init==0)
		{
			if (Command==1)
			{

					Homed=true;
					holdIn(active, homingTime); /// homing time is average time of moving: 18 second

			}
			else if (Command==3 && Homed)
								{
									Stopped = true;
									Homed=false;
									holdIn(active,Time::Zero);
								}else holdIn(active,Time::Zero);
		}
		else holdIn(active,Time::Zero);
	}
	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description:
********************************************************************/
Model &Joint1::internalFunction( const InternalMessage & )
{

	if (Init==0)
	{
		if (Command == 3)
		{
			if (Homed==true && Stopped== true)
			{
				Stopped=false;
				Init=0;
			}
		}
		if (Command==1 && Homed==true)
		{
			Init=1;
			Homed=true;
		}

	} else {
			Stopped=false;
			Homed=true;
			}

	this-> passivate();
	return *this ;
}
/*******************************************************************
* Function Name: outputFunction
* Description:
********************************************************************/
Model &Joint1::outputFunction( const InternalMessage &msg )
{

	if (Init==1)
	{
		sendOutput (msg.time(), Done, this->Init);
	} else 	sendOutput (msg.time(), Done, this->Command);


	return *this ;
}

