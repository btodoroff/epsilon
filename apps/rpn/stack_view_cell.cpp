#include "stack_view_cell.h"
#include "app.h"
#include "../constant.h"
#include "selectable_table_view.h"
#include <assert.h>
#include <string.h>

namespace Rpn {

StackViewCell::StackViewCell(Responder * parentResponder) :
  Responder(parentResponder),
  m_inputView(this),
  m_outputView(this),
  m_selectedSubviewType(StackViewCell::SubviewType::Output)
{
}

KDColor StackViewCell::backgroundColor() const {
  KDColor background = m_even ? Palette::WallScreen : KDColorWhite;
  return background;
}


int StackViewCell::numberOfSubviews() const {
  return 2;
}

View * StackViewCell::subviewAtIndex(int index) {
  View * views[2] = {&m_inputView, &m_outputView};
  return views[index];
}

void StackViewCell::layoutSubviews() {
  KDCoordinate width = bounds().width();
  KDCoordinate height = bounds().height();
  KDSize inputSize = m_inputView.minimalSizeForOptimalDisplay();
  if (inputSize.width() + k_digitHorizontalMargin > width) {
    m_inputView.setFrame(KDRect(k_digitHorizontalMargin, k_digitVerticalMargin, width - k_digitHorizontalMargin, inputSize.height()));
  } else {
    m_inputView.setFrame(KDRect(width - inputSize.width() - k_digitHorizontalMargin, k_digitVerticalMargin, inputSize.width(), inputSize.height()));
  }
  KDSize outputSize = m_outputView.minimalSizeForOptimalDisplay();
  if (outputSize.width() + k_digitHorizontalMargin > width) {
    m_outputView.setFrame(KDRect(k_digitHorizontalMargin, inputSize.height() + 2*k_digitVerticalMargin, width - k_digitHorizontalMargin, height - inputSize.height() - 3*k_digitVerticalMargin));
  } else {
    m_outputView.setFrame(KDRect(width - outputSize.width() - k_digitHorizontalMargin, inputSize.height() + 2*k_digitVerticalMargin, outputSize.width(), height - inputSize.height() - 3*k_digitVerticalMargin));
  }
}

void StackViewCell::setRpn(Rpn * rpn) {
  m_inputView.setExpression(rpn->inputLayout());
  App * rpnApp = (App *)app();
  m_outputView.setExpression(rpn->outputLayout(rpnApp->localContext()));
}

void StackViewCell::reloadCell() {
  m_outputView.setBackgroundColor(backgroundColor());
  m_inputView.setBackgroundColor(backgroundColor());
  if (isHighlighted()) {
    if (m_selectedSubviewType == SubviewType::Output) {
      m_outputView.setBackgroundColor(Palette::Select);
    } else {
      m_inputView.setBackgroundColor(Palette::Select);
    }
  }
  layoutSubviews();
  EvenOddCell::reloadCell();
  m_inputView.reloadScroll();
  m_outputView.reloadScroll();
}

void StackViewCell::didBecomeFirstResponder() {
  //if (m_selectedSubviewType == SubviewType::Input) {
  //  app()->setFirstResponder(&m_inputView);
  //} else {
    app()->setFirstResponder(&m_outputView);
  //}
}

StackViewCell::SubviewType StackViewCell::selectedSubviewType() {
  return m_selectedSubviewType;
}

//void StackViewCell::setSelectedSubviewType(StackViewCell::SubviewType subviewType) {
//  m_selectedSubviewType = subviewType;
//}

bool StackViewCell::handleEvent(Ion::Events::Event event) {
  // if ((event == Ion::Events::Down && m_selectedSubviewType == SubviewType::Input) ||
    // (event == Ion::Events::Up && m_selectedSubviewType == SubviewType::Output)) {
    // SubviewType otherSubviewType = m_selectedSubviewType == SubviewType::Input ? SubviewType::Output : SubviewType::Input;
    // RpnSelectableTableView * tableView = (RpnSelectableTableView *)parentResponder();
    // tableView->scrollToSubviewOfTypeOfCellAtLocation(otherSubviewType, tableView->selectedColumn(), tableView->selectedRow());
    // StackViewCell * selectedCell = (StackViewCell *)(tableView->selectedCell());
    // selectedCell->setSelectedSubviewType(otherSubviewType);
    // app()->setFirstResponder(selectedCell);
    // selectedCell->reloadCell();
    // return true;
  // }
  return false;
}

}
