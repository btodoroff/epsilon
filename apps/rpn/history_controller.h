#ifndef RPN_HISTORY_CONTROLLER_H
#define RPN_HISTORY_CONTROLLER_H

#include <escher.h>
#include <poincare.h>
#include "stack_view_cell.h"
#include "rpn_store.h"
#include "selectable_table_view.h"

namespace Rpn {

class App;

class HistoryController : public DynamicViewController, public ListViewDataSource, public SelectableTableViewDataSource, public SelectableTableViewDelegate {
public:
  HistoryController(Responder * parentResponder, RpnStore * rpnStore);

  bool handleEvent(Ion::Events::Event event) override;
  void didBecomeFirstResponder() override;
  void willExitResponderChain(Responder * nextFirstResponder) override;
  void reload();
  int numberOfRows() override;
  HighlightCell * reusableCell(int index, int type) override;
  int reusableCellCount(int type) override;
  void willDisplayCellForIndex(HighlightCell * cell, int index) override;
  KDCoordinate rowHeight(int j) override;
  KDCoordinate cumulatedHeightFromIndex(int j) override;
  int indexFromCumulatedHeight(KDCoordinate offsetY) override;
  int typeAtLocation(int i, int j) override;
  void tableViewDidChangeSelection(SelectableTableView * t, int previousSelectedCellX, int previousSelectedCellY) override;
  void scrollToCell(int i, int j);
  View * loadView() override;
  void unloadView(View * view) override;
private:
  RpnSelectableTableView * selectableTableView();
  constexpr static int k_maxNumberOfDisplayedRows = 5;
  StackViewCell * m_rpnHistory[k_maxNumberOfDisplayedRows];
  RpnStore * m_rpnStore;
};

}

#endif
