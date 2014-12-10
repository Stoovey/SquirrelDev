#ifndef _SERVICEBASE_H_
#define _SERVICEBASE_H_

/* this is only here so that we have a common
 * base class for anything that needs to be a
 * 'service' to inherit from */
class ServiceBase {

public:

	//must be here for inheriting class destructors to call correctly
	virtual ~ServiceBase(){}
};

#endif