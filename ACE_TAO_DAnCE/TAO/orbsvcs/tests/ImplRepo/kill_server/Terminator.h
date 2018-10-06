/* -*- C++ -*- $Id: Terminator.h 97448 2013-12-04 17:15:34Z mesnier_p $ */

#include "ace/Task_T.h"

class Terminator : public ACE_Task<ACE_MT_SYNCH>
{
 public:

  virtual int open(void*);

  virtual int svc();
};

