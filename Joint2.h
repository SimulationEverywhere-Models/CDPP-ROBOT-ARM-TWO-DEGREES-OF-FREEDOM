#ifndef __JOINT2_H
#define __JOINT2_H


#include "atomic.h"     // class Atomic

class Joint2 : public Atomic {
public:
	Joint2 ( const string &name = "Joint2" );	//Default constructor
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

   static bool Homed;
   static int Init;
   bool Stopped;
   int Command;

}; // class Joint2

inline
string Joint2::className() const
{
	return "Joint2" ;
}

#endif   //__JOINT2_H

