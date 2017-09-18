#ifndef RPN_STACK_VIEW_CELL_H
#define RPN_STACK_VIEW_CELL_H

#include <escher.h>
#include "rpn.h"
#include "scrollable_expression_view.h"

namespace Rpn {

class StackViewCell : public ::EvenOddCell, public Responder {
public:
  enum class SubviewType {
    Input,
    Output
  };
  StackViewCell(Responder * parentResponder);
  void reloadCell() override;
  KDColor backgroundColor() const override;
  void setRpn(Rpn * rpn);
  int numberOfSubviews() const override;
  View * subviewAtIndex(int index) override;
  void layoutSubviews() override;
  void didBecomeFirstResponder() override;
  bool handleEvent(Ion::Events::Event event) override;
  constexpr static KDCoordinate k_digitHorizontalMargin = 10;
  constexpr static KDCoordinate k_digitVerticalMargin = 5;
  SubviewType selectedSubviewType();
  //void setSelectedSubviewType(HistoryViewCell::SubviewType subviewType);
private:
  constexpr static KDCoordinate k_resultWidth = 80;
  ScrollableExpressionView m_inputView;
  ScrollableExpressionView m_outputView;
  SubviewType m_selectedSubviewType;
};

}

#endif
