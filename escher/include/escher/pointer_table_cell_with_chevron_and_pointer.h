#ifndef ESCHER_POINTER_TABLE_CELL_WITH_CHEVRON_AND_POINTER_H
#define ESCHER_POINTER_TABLE_CELL_WITH_CHEVRON_AND_POINTER_H

#include <escher/pointer_table_cell_with_chevron.h>

class PointerTableCellWithChevronAndPointer : public PointerTableCellWithChevron {
public:
  PointerTableCellWithChevronAndPointer(KDText::FontSize labelSize = KDText::FontSize::Small, KDText::FontSize contentSize = KDText::FontSize::Small);
  View * subAccessoryView() const override;
  void setHighlighted(bool highlight) override;
  void setSubtitle(I18n::Message text);
private:
  PointerTextView m_subtitleView;
};

#endif
