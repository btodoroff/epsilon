#include "rpn_store.h"
#include <assert.h>
using namespace Poincare;

namespace Rpn {

RpnStore::RpnStore() :
  m_startIndex(0)
{
}

Rpn * RpnStore::push(const char * text, Context * context) {
  Rpn * result = &m_rpns[m_startIndex];
  result->setContent(text, context);
  m_startIndex++;
  if (m_startIndex >= k_maxNumberOfRpns) {
    m_startIndex = 0;
  }
  return result;
}

Rpn * RpnStore::rpnAtIndex(int i) {
  int j = 0;
  Rpn * currentCalc = &m_rpns[m_startIndex];
  Rpn * previousCalc = nullptr;
  while (j <= i) {
    if (!currentCalc++->isEmpty()) {
      previousCalc = currentCalc - 1;
      j++;
    }
    if (currentCalc >= m_rpns + k_maxNumberOfRpns) {
      currentCalc = m_rpns;
    }
  }
  return previousCalc;
}

int RpnStore::numberOfRpns() {
  Rpn * currentCalc= m_rpns;
  int numberOfRpns = 0;
  while (currentCalc < m_rpns + k_maxNumberOfRpns) {
    if (!currentCalc++->isEmpty()) {
      numberOfRpns++;
    }
  }
  return numberOfRpns;
}

void RpnStore::deleteRpnAtIndex(int i) {
  int numberOfCalc = numberOfRpns();
  assert(i >= 0 && i < numberOfCalc);
  int indexFirstCalc = m_startIndex;
  while (m_rpns[indexFirstCalc].isEmpty()) {
    indexFirstCalc++;
    if (indexFirstCalc == k_maxNumberOfRpns) {
      indexFirstCalc = 0;
    }
    assert(indexFirstCalc != m_startIndex);
  }
  int absoluteIndexRpnI = indexFirstCalc+i;
  absoluteIndexRpnI = absoluteIndexRpnI >= k_maxNumberOfRpns ? absoluteIndexRpnI - k_maxNumberOfRpns : absoluteIndexRpnI;

  int index = absoluteIndexRpnI;
  for (int k = i; k < numberOfCalc-1; k++) {
    int nextIndex = index+1 >= k_maxNumberOfRpns ? 0 : index+1;
    m_rpns[index] = m_rpns[nextIndex];
    index++;
    if (index == k_maxNumberOfRpns) {
      index = 0;
    }
  }
  m_rpns[index].reset();
  m_startIndex--;
  if (m_startIndex == -1) {
    m_startIndex = k_maxNumberOfRpns-1;
  }
}

void RpnStore::deleteAll() {
  m_startIndex = 0;
  for (int i = 0; i < k_maxNumberOfRpns; i++) {
    m_rpns[i].reset();
  }
}

void RpnStore::tidy() {
  for (int i = 0; i < k_maxNumberOfRpns; i++) {
    m_rpns[i].tidy();
  }
}

}
