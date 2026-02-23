#pragma once

#include "execution_context.h"

class schedular_operation
{
  typedef schedular_operation operation_type;
 public:
 
  void complete(void* owner, const )
};

class schedular : public execution_context_service_base<schedular>
{
  typedef schedular_operation operation;

  struct internal {
  };
  
  typedef schedular_task* (*get_task_func_type)(execution_context&);
  
 public:
}