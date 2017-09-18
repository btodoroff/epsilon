#ifndef RPN_APP_H
#define RPN_APP_H

#include "rpn_store.h"
#include "edit_expression_controller.h"
#include "history_controller.h"
#include "local_context.h"
#include "../shared/text_field_delegate_app.h"
#include <escher.h>

namespace Rpn {

class App : public Shared::TextFieldDelegateApp {
public:
  class Descriptor : public ::App::Descriptor {
  public:
    I18n::Message name() override;
    I18n::Message upperName() override;
    const Image * icon() override;
  };
  class Snapshot : public ::App::Snapshot {
  public:
    App * unpack(Container * container) override;
    void reset() override;
    Descriptor * descriptor() override;
    RpnStore * rpnStore();
  private:
    void tidy() override;
    RpnStore m_rpnStore;
  };
  Poincare::Context * localContext() override;
private:
  App(Container * container, Snapshot * snapshot);
  LocalContext m_localContext;
  HistoryController m_historyController;
  EditExpressionController m_editExpressionController;
};

}

#endif
