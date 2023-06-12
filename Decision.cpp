/*******************************************************************
*
*  DESCRIPTION: Atomic Model Decision
*
*  AUTHOR: Saeed Ahmadi
*
*  EMAIL: mailto://Sahmadi1@connect.carleton.ca
*
*  DATE: 27/12/2011
*
*******************************************************************/

/** include files **/
   // class Decision
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )
#include "stdlib.h"
#include "Decision.h"

Decision::Decision( const string &name )
: Atomic( name )
, UserCommand(this-> addInputPort( "UserCommand"))
, Done_Motion(this -> addInputPort( "Done_Motion"))
, Done_Homing (this -> addInputPort( "Done_Homing"))
, Motion_Command (this -> addOutputPort("Motion_Command"))
, Home_Command (this -> addOutputPort("Home_Command"))
{

}
bool Decision::Homed=false;
/*******************************************************************
* Function Name: initFunction
* Description:
* Precondition:
********************************************************************/
Model &Decision::initFunction()
{

	IDLE=0;
	INIT=1;
	MOVING=2;
	STOPPING=false;
	Current_State = IDLE;
	Init_Command = false;
	Move_Command = false;
	Stop_Command = false;

	this-> passivate();
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description:
********************************************************************/
Model &Decision::externalFunction( const ExternalMessage &msg )
{

	if (msg.port()==UserCommand)
	{

		if (msg.value()!=0 )
		{

			Command= msg.value();
			Command_Div= ldiv(Command,1000000);    // this will return the first digit of the number that represents the type of command.

			Command_Digit= Command_Div.quot;
			if (Command_Digit==2)
			{
				Move_Command=true;
			}
			else if (Command_Digit==1)
			{
				Init_Command=true;
			}
			else if (Command_Digit==3)
			{
				Stop_Command=true;
			}

		}


	if (Homed == false)
	{
		if (Init_Command==true && Current_State == IDLE)
		{
			Current_State = INIT;
			holdIn(active, Time::Zero);
		} else	if (Stop_Command==true && Current_State == INIT)
				{
					STOPPING=true;
					holdIn(active, Time::Zero);
				}	else
					{
						Init_Command=false;
						Move_Command=false;
						Stop_Command=false;
						Current_State=IDLE;
						this-> passivate();
					}
	} else
		if ( Homed == true)
		{
			if (Move_Command==true && Current_State == IDLE)
			{
				Current_State = MOVING;

				holdIn(active, Time::Zero);
			} else
				if (Move_Command==true && Current_State != IDLE)
				{
					Move_Command=false;
					this -> passivate();
				}
			if (Stop_Command==true && Current_State != IDLE)
				{
					STOPPING=true;
					holdIn(active, Time::Zero);
				} else if (Stop_Command==true && Current_State == IDLE)
						{
							Stop_Command=false;
							this-> passivate();
						}
		}
	}

	if ( msg.port () == Done_Motion)
	{
		Current_State = IDLE;
		if (msg.value()==2)
		{
			Move_Command=false;
			this-> passivate ();
		}else if (msg.value ()==3)
				{
					STOPPING=false;
					Stop_Command=false;
					Move_Command=false;
					this-> passivate();
				}
	}
	if ( msg.port () == Done_Homing )
	{
		Homing_Value=msg.value();
		Current_State = IDLE;
		if (Homing_Value==1)
		{
			Init_Command=false;
			Homed=true;
			this-> passivate();
		}
		else if (Homing_Value==3)
				{
					STOPPING=false;
					Stop_Command=false;
					Init_Command=false;
					this-> passivate();
				}

	}

	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description:
********************************************************************/
Model &Decision::internalFunction( const InternalMessage & )
{

	Init_Command=false;
	Move_Command=false;
	Stop_Command=false;

	this-> passivate();
	return *this ;
}
/*******************************************************************
* Function Name: outputFunction
* Description:
********************************************************************/
Model &Decision::outputFunction( const InternalMessage &msg )
{

	if (Init_Command)
	{
		sendOutput (msg.time(), Home_Command, this->Command_Digit);
	}

	if (Move_Command)
	{
		sendOutput ( msg.time(), Motion_Command, this-> Command);
	}

	if (Stop_Command)
	{
		if (Current_State==INIT && Homed==false) sendOutput ( msg.time(), Home_Command, this-> Command_Digit);
		if (Current_State==MOVING) sendOutput ( msg.time(), Motion_Command, this-> Command);

	}

	return *this ;
}

