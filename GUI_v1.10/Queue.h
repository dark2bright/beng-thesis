#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "Container.h"

class CQueue : public virtual CContainer
{
public:
    virtual CObjectEx& head () const = 0;
    virtual VOID enqueue (CObjectEx&) = 0;
    virtual CObjectEx& dequeue () = 0;
	virtual ~CQueue(){}
};

#endif // #define _QUEUE_H_