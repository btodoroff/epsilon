#include "history_controller.h"
#include "app.h"
#include "../apps_container.h"
#include <assert.h>

namespace Rpn {

HistoryController::HistoryController(Responder * parentResponder, RpnStore * rpnStore) :
  DynamicViewController(parentResponder),
  m_rpnHistory{},
  m_rpnStore(rpnStore)
{
}

void HistoryController::reload() {
  selectableTableView()->reloadData();
}

void HistoryController::didBecomeFirstResponder() {
  selectCellAtLocation(0, numberOfRows()-1);
  app()->setFirstResponder(selectableTableView());
}

void HistoryController::willExitResponderChain(Responder * nextFirstResponder) {
  if (nextFirstResponder == parentResponder()) {
    selectableTableView()->deselectTable();
  }
}

bool HistoryController::handleEvent(Ion::Events::Event event) {
  if (event == Ion::Events::Down) {
    selectableTableView()->deselectTable();
    app()->setFirstResponder(parentResponder());
    return true;
  }
  if (event == Ion::Events::Up) {
    return true;
  }
  if (event == Ion::Events::OK || event == Ion::Events::EXE) {
    int focusRow = selectedRow();
    StackViewCell * selectedCell = (StackViewCell *)selectableTableView()->selectedCell();
    StackViewCell::SubviewType subviewType = selectedCell->selectedSubviewType();
    EditExpressionController * editController = (EditExpressionController *)parentResponder();
    selectableTableView()->deselectTable();
    app()->setFirstResponder(editController);
    Rpn * rpn = m_rpnStore->rpnAtIndex(focusRow);
    if (subviewType == StackViewCell::SubviewType::Input) {
      editController->insertTextBody(rpn->inputText());
    } else {
      editController->insertTextBody(rpn->outputText());
    }
    return true;
  }
  if (event == Ion::Events::Backspace) {
    int focusRow = selectedRow();
    StackViewCell * selectedCell = (StackViewCell *)selectableTableView()->selectedCell();
    StackViewCell::SubviewType subviewType = selectedCell->selectedSubviewType();
    selectableTableView()->deselectTable();
    EditExpressionController * editController = (EditExpressionController *)parentResponder();
    m_rpnStore->deleteRpnAtIndex(focusRow);
    reload();
    if (numberOfRows()== 0) {
      app()->setFirstResponder(editController);
      return true;
    }
    if (focusRow > 0) {
      selectableTableView()->selectCellAtLocation(0, focusRow-1);
    } else {
      selectableTableView()->selectCellAtLocation(0, 0);
    }
    if (subviewType == StackViewCell::SubviewType::Input) {
      tableViewDidChangeSelection(selectableTableView(), 0, selectedRow());
    } else {
      tableViewDidChangeSelection(selectableTableView(), 0, -1);
    }
    selectableTableView()->scrollToCell(0, selectedRow());
    return true;
  }
  if (event == Ion::Events::Clear) {
    selectableTableView()->deselectTable();
    m_rpnStore->deleteAll();
    reload();
    app()->setFirstResponder(parentResponder());
    return true;
  }
  if (event == Ion::Events::Back) {
    EditExpressionController * editController = (EditExpressionController *)parentResponder();
    selectableTableView()->deselectTable();
    app()->setFirstResponder(editController);
    return true;
  }
  if (event == Ion::Events::Copy) {
    StackViewCell * selectedCell = (StackViewCell *)selectableTableView()->selectedCell();
    StackViewCell::SubviewType subviewType = selectedCell->selectedSubviewType();
    int focusRow = selectedRow();
    Rpn * rpn = m_rpnStore->rpnAtIndex(focusRow);
    if (subviewType == StackViewCell::SubviewType::Input) {
      Clipboard::sharedClipboard()->store(rpn->inputText());
    } else {
      Clipboard::sharedClipboard()->store(rpn->outputText());
    }
    return true;
  }
  return false;
}

void HistoryController::tableViewDidChangeSelection(SelectableTableView * t, int previousSelectedCellX, int previousSelectedCellY) {
  StackViewCell * selectedCell = (StackViewCell *)(t->selectedCell());
  if (selectedCell == nullptr) {
    return;
  }
  // if (selectedRow() < previousSelectedCellY) {
    // selectedCell->setSelectedSubviewType(StackViewCell::SubviewType::Output);
  // }
  // if (selectedRow() >= previousSelectedCellY) {
    // selectedCell->setSelectedSubviewType(StackViewCell::SubviewType::Input);
  // }
  //if (previousSelectedCellY == -1) {
  //  selectedCell->setSelectedSubviewType(StackViewCell::SubviewType::Output);
  //}
  app()->setFirstResponder(selectedCell);
  selectedCell->reloadCell();
}

int HistoryController::numberOfRows() {
  return m_rpnStore->numberOfRpns();
};

HighlightCell * HistoryController::reusableCell(int index, int type) {
  assert(type == 0);
  assert(index >= 0);
  assert(index < k_maxNumberOfDisplayedRows);
  return m_rpnHistory[index];
}

int HistoryController::reusableCellCount(int type) {
  assert(type == 0);
  return k_maxNumberOfDisplayedRows;
}

void HistoryController::willDisplayCellForIndex(HighlightCell * cell, int index) {
  StackViewCell * myCell = (StackViewCell *)cell;
  myCell->setRpn(m_rpnStore->rpnAtIndex(index));
  myCell->setEven(index%2 == 0);
}

KDCoordinate HistoryController::rowHeight(int j) {
  if (j >= m_rpnStore->numberOfRpns()) {
    return 0;
  }
  Rpn * rpn = m_rpnStore->rpnAtIndex(j);
  KDCoordinate inputHeight = rpn->inputLayout()->size().height();
  App * rpnApp = (App *)app();
  KDCoordinate outputHeight = rpn->outputLayout(rpnApp->localContext())->size().height();
  return inputHeight + outputHeight + 3*StackViewCell::k_digitVerticalMargin;
}

KDCoordinate HistoryController::cumulatedHeightFromIndex(int j) {
  int result = 0;
  for (int k = 0; k < j; k++) {
    result += rowHeight(k);
  }
  return result;
}

int HistoryController::indexFromCumulatedHeight(KDCoordinate offsetY) {
  int result = 0;
  int j = 0;
  while (result < offsetY && j < numberOfRows()) {
    result += rowHeight(j++);
  }
  return (result < offsetY || offsetY == 0) ? j : j - 1;
}

int HistoryController::typeAtLocation(int i, int j) {
  return 0;
}

void HistoryController::scrollToCell(int i, int j) {
  selectableTableView()->scrollToCell(i, j);
}

RpnSelectableTableView * HistoryController::selectableTableView() {
  return (RpnSelectableTableView *)view();
}

View * HistoryController::loadView() {
  RpnSelectableTableView * tableView = new RpnSelectableTableView(this, this, this, this);
for (int i = 0; i < k_maxNumberOfDisplayedRows; i++) {
    m_rpnHistory[i] = new StackViewCell(tableView);
  }
  return tableView;
}

void HistoryController::unloadView(View * view) {
  for (int i = 0; i < k_maxNumberOfDisplayedRows; i++) {
    delete m_rpnHistory[i];
    m_rpnHistory[i] = nullptr;
  }
  delete view;
}

}
