#include "app.h"
#include "../apps_container.h"
#include "rpn_icon.h"
#include "../i18n.h"

using namespace Poincare;

using namespace Shared;

namespace Rpn {

I18n::Message App::Descriptor::name() {
  return I18n::Message::RPNApp;
}

I18n::Message App::Descriptor::upperName() {
  return I18n::Message::RPNAppCapital;
}

const Image * App::Descriptor::icon() {
  return ImageStore::RpnIcon;
}

App * App::Snapshot::unpack(Container * container) {
  return new App(container, this);
}

void App::Snapshot::reset() {
  m_rpnStore.deleteAll();
}

App::Descriptor * App::Snapshot::descriptor() {
  static Descriptor descriptor;
  return &descriptor;
}

RpnStore * App::Snapshot::rpnStore() {
  return &m_rpnStore;
}

void App::Snapshot::tidy() {
  m_rpnStore.tidy();
}

App::App(Container * container, Snapshot * snapshot) :
  TextFieldDelegateApp(container, snapshot, &m_editExpressionController),
  m_localContext((GlobalContext *)((AppsContainer *)container)->globalContext(), snapshot->rpnStore()),
  m_historyController(&m_editExpressionController, snapshot->rpnStore()),
  m_editExpressionController(&m_modalViewController, &m_historyController, snapshot->rpnStore())
{
}

Context * App::localContext() {
  return &m_localContext;
}

}
