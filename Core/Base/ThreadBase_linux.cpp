#include "ThreadBase.h"

#ifdef linux
#include <sys/prctl.h>
void ThreadBase::setName(const StringPiece& name)
{
	prctl(PR_SET_NAME, name.c_str());
}
#endif