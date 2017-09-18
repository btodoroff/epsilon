#ifndef RPN_LOCAL_CONTEXT_H
#define RPN_LOCAL_CONTEXT_H

#include <poincare.h>
#include "rpn_store.h"

namespace Rpn {

class LocalContext : public Poincare::Context {
public:
  LocalContext(Poincare::GlobalContext * parentContext, RpnStore * rpnStore);
  void setExpressionForSymbolName(Poincare::Expression * expression, const Poincare::Symbol * symbol) override;
  const Poincare::Expression * expressionForSymbol(const Poincare::Symbol * symbol) override;
private:
  Poincare::Evaluation<double> * ansValue();
  RpnStore * m_rpnStore;
  Poincare::GlobalContext * m_parentContext;
};

}

#endif
