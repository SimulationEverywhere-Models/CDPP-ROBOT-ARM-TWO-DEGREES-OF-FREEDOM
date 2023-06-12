#include "modeladm.h"
#include "mainsimu.h"
#include "Decision.h"
#include "Motion.h"
#include "Joint1.h"
#include "Joint2.h"

void MainSimulator::registerNewAtomics()
{

	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Decision>(), "Decision" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Motion>(), "Motion" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Joint1>(), "Joint1" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Joint2>(), "Joint2" ) ;
}

