#include "local_context.h"
#include <string.h>
using namespace Poincare;

namespace Rpn {

LocalContext::LocalContext(GlobalContext * parentContext, RpnStore * rpnStore) :
  m_rpnStore(rpnStore),
  m_parentContext(parentContext)
{
}

Evaluation<double> * LocalContext::ansValue() {
  if (m_rpnStore->numberOfRpns() == 0) {
    return m_parentContext->defaultExpression();
  }
  Rpn * lastRpn = m_rpnStore->rpnAtIndex(m_rpnStore->numberOfRpns()-1);
  return lastRpn->output(m_parentContext);
}

void LocalContext::setExpressionForSymbolName(Expression * expression, const Symbol * symbol) {
  if (symbol->name() != Symbol::SpecialSymbols::Ans) {
    m_parentContext->setExpressionForSymbolName(expression, symbol);
  }
}

const Expression * LocalContext::expressionForSymbol(const Symbol * symbol) {
  if (symbol->name() == Symbol::SpecialSymbols::Ans) {
    return ansValue();
  } else {
    return m_parentContext->expressionForSymbol(symbol);
  }
}

}
