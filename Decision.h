#ifndef __DECISION_H
#define __DECISION_H


#include "atomic.h"     // class Atomic

class Decision : public Atomic {
public:
	Decision ( const string &name = "Decision" );	//Default constructor
   virtual string className() const ;

protected:
   Model &initFunction();
   Model &externalFunction( const ExternalMessage & );
   Model &internalFunction( const InternalMessage & );
   Model &outputFunction( const InternalMessage & );

private:
   const Port &UserCommand;
   const Port &Done_Motion;
   const Port &Done_Homing;
   Port &Motion_Command;
   Port &Home_Command;
   Time preparationTime;

   int IDLE;
   int INIT;
   int MOVING;
   int Current_State;

   bool Init_Command;
   bool Move_Command;
   bool Stop_Command;
   bool STOPPING;
   static bool Homed;

   int Command_Digit;
   double Command;
   ldiv_t Command_Div;

   int Homing_Value;
}; // class Decision

inline
string Decision::className() const
{
	return "Decision" ;
}

#endif   //__DECISION_H

