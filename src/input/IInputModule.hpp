#ifndef INPUT_MODULE_H
#define INPUT_MODULE_H

#include "InputRouter.hpp"

namespace dankreek {
  class IInputModule {
  public:
    IInputModule(){};

    // Scan all inputs for updates and make calls to the input router
    virtual void update(InputRouter &inputRouter) = 0;
  };
}

#endif
