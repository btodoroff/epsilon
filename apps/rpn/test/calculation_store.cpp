#include <quiz.h>
#include <string.h>
#include <assert.h>
#include "../rpn_store.h"

using namespace Poincare;
using namespace Rpn;

void assert_store_is(RpnStore * store, const char * result[10]) {
  for (int i = 0; i < store->numberOfRpns(); i++) {
    assert(strcmp(store->rpnAtIndex(i)->inputText(), result[i]) == 0);
  }
}

QUIZ_CASE(rpn_store) {
  GlobalContext globalContext;
  RpnStore store;
  assert(RpnStore::k_maxNumberOfRpns == 10);
  for (int i = 0; i < RpnStore::k_maxNumberOfRpns; i++) {
    char text[2] = {(char)(i+'0'), 0};
    store.push(text, &globalContext);
    assert(store.numberOfRpns() == i+1);
  }
  /* Store is now {0, 1, 2, 3, 4, 5, 6, 7, 8, 9} */
  const char * result[10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
  assert_store_is(&store, result);

  store.push("10", &globalContext);
  /* Store is now {1, 2, 3, 4, 5, 6, 7, 8, 9, 10} */
  const char * result1[10] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
  assert_store_is(&store, result1);

  for (int i = 9; i > 0; i = i-2) {
   store.deleteRpnAtIndex(i);
  }
  /* Store is now {1, 3, 5, 7, 9} */
  const char * result2[10] = {"1", "3", "5", "7", "9", "", "", "", "", ""};
  assert_store_is(&store, result2);

  for (int i = 5; i < RpnStore::k_maxNumberOfRpns; i++) {
    char text[3] = {(char)(i+'0'), 0};
    store.push(text, &globalContext);
    assert(store.numberOfRpns() == i+1);
  }
  /* Store is now {0, 2, 4, 6, 8, 5, 6, 7, 8, 9} */
  const char * result3[10] = {"1", "3", "5", "7", "9", "5", "6", "7", "8", "9"};
  assert_store_is(&store, result3);
}
