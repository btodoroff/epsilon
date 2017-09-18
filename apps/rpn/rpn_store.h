#ifndef RPN_RPN_STORE_H
#define RPN_RPN_STORE_H

#include "rpn.h"

namespace Rpn {

class RpnStore {
public:
  RpnStore();
  Rpn * rpnAtIndex(int i);
  Rpn * push(const char * text, Poincare::Context * context);
  void deleteRpnAtIndex(int i);
  void deleteAll();
  int numberOfRpns();
  void tidy();
  static constexpr int k_maxNumberOfRpns = 10;
private:
  int m_startIndex;
  Rpn m_rpns[k_maxNumberOfRpns];
};

}

#endif
