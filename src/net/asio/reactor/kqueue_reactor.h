#pragma once

#include "asio/schedular.h"
#include "asio/context/execution_context.h"

class schedular;

class kqueue_reactor
  : public execution_context_service_base<kqueue_reactor>, public schedular_task
{
private:

  typedef conditionally_enabled_mutex mutex;

public:

  enum op_types {
    read_op = 0, write_op = 1, connect_op = 2, max_ops = 3
  };

  struct descriptor_state {
    descriptor_state(bool locking, int spin_count) : mutex_(locking, spin_count) {}
    descriptor_state* next_;
    descriptor_state* prev_;

    mutex mutex_;
    int descriptor_;
    int num_kevents_;
    op_queue<reactor_op> op_queue_[max_ops];
    bool shutdown_;
  };
  typedef descriptor_state* per_descriptor_data;

  inline kqueue_reactor(execution_context& ctx) {
    
  }

  inline ~kqueue_reactor() {

  }

  inline void shutdown() {

  }

  inline void notify_fork(execution_context::fork_event fork_ev) {

  }

  inline void init_task() {

  }

  inline int register_descriptor(socket_type descriptor, per_descriptor_data& descriptor_data) {

  }
  
}; // class kqueue_reactor