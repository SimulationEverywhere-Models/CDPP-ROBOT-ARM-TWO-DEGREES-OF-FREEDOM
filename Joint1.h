#ifndef __JOINT1_H
#define __JOINT1_H


#include "atomic.h"     // class Atomic

class Joint1 : public Atomic {
public:
	Joint1 ( const string &name = "Joint1" );	//Default constructor
   virtual string className() const ;

protected:
   Model &initFunction();
   Model &externalFunction( const ExternalMessage & );
   Model &internalFunction( const InternalMessage & );
   Model &outputFunction( const InternalMessage & );

private:
   const Port &Homing;
   Port &Done;
   Time homingTime;

   int Current_State;

   static bool Homed;
   static int Init;
   bool Stopped;
   int Command;

}; // class Joint1

inline
string Joint1::className() const
{
	return "Joint1" ;
}

#endif   //__JOINT1_H

