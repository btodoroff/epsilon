#ifndef HOME_CONTROLLER_H
#define HOME_CONTROLLER_H

#include <escher.h>
#include "app_cell.h"

class AppsContainer;

namespace Home {

class Controller : public ViewController, public SimpleTableViewDataSource, public SelectableTableViewDelegate {
public:
  Controller(Responder * parentResponder, ::AppsContainer * container);

  View * view() override;

  bool handleEvent(Ion::Events::Event event) override;
  void didBecomeFirstResponder() override;
  void viewWillAppear() override;

  virtual int numberOfRows() override;
  virtual int numberOfColumns() override;
  virtual KDCoordinate cellHeight() override;
  virtual KDCoordinate cellWidth() override;
  virtual HighlightCell * reusableCell(int index) override;
  virtual int reusableCellCount() override;
  void willDisplayCellAtLocation(HighlightCell * cell, int i, int j) override;
  void tableViewDidChangeSelection(SelectableTableView * t, int previousSelectedCellX, int previousSelectedCellY) override;
private:
  int numberOfIcons();
  AppsContainer * m_container;
  SelectableTableView m_selectableTableView;
  static constexpr KDCoordinate k_sideMargin = 4;
  static constexpr KDCoordinate k_indicatorThickness = 28;
  static constexpr KDCoordinate k_indicatorMargin = 116;
  static constexpr int k_numberOfColumns = 4;
  static constexpr int k_numberOfApps = 10;
  static constexpr int k_maxNumberOfCells = 16;
  static constexpr int k_cellHeight = 98;
  static constexpr int k_cellWidth = 104;
  AppCell m_cells[k_maxNumberOfCells];
};

}

#endif
