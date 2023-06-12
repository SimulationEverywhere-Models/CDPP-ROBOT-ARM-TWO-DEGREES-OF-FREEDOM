/*******************************************************************
*
*  DESCRIPTION: Atomic Model Joint2
*
*  AUTHOR: Saeed Ahmadi
*
*  EMAIL: mailto://Sahmadi1@connect.carleton.ca
*
*  DATE: 27/12/2011
*
*******************************************************************/

/** include files **/
   // class Joint2
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )
#include "stdlib.h"
#include "Joint2.h"

Joint2::Joint2( const string &name )
: Atomic( name )
, Homing(this-> addInputPort( "Homing"))
, Done (this -> addOutputPort("Done"))
{

  string time( MainSimulator::Instance().getParameter(this->description(), "homingtime" ) ) ;

   if( time != "" )
   homingTime = time ;
}
int Joint2::Init=0;
bool Joint2::Homed=false;
/*******************************************************************
* Function Name: initFunction
* Description:
* Precondition:
********************************************************************/
Model &Joint2::initFunction()
{
	Stopped = false;
	this-> passivate();
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description:
********************************************************************/
Model &Joint2::externalFunction( const ExternalMessage &msg )
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
										} else holdIn(active,Time::Zero);
				}
				else holdIn(active,Time::Zero);
		}
		return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description:
********************************************************************/
Model &Joint2::internalFunction( const InternalMessage & )
{
	if (Init==0)
		{
			if (Command == 3)
				{
					if (Homed==false && Stopped== true)
					{
						Stopped=false;
						Init=0;
					}
				}
				if (Command==1 && Homed==true)
				{
					Init=1;
					Homed=true;
				}else if (Command==1 && Homed==false)
				{
					Init=0;
				}
		}else
			{
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
Model &Joint2::outputFunction( const InternalMessage &msg )
{

	if (Init==1)
		{
			sendOutput (msg.time(), Done, this->Init);
		} else 	sendOutput (msg.time(), Done, this->Command);



	return *this ;
}

