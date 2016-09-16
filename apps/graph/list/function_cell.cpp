#include "function_cell.h"
#include <poincare.h>

FunctionCell::FunctionCell() :
  ChildlessView(),
  Responder(nullptr),
  m_function(nullptr),
  m_focused(false),
  m_even(false)
{
}

void FunctionCell::drawRect(KDContext * ctx, KDRect rect) const {
  KDColor background = m_even ? KDColor(0xEEEEEE) : KDColor(0x777777);
  ctx->fillRect(rect, background);
  KDColor text = m_focused ? KDColorBlack : KDColorWhite;
  KDColor textBackground = m_focused ? KDColorWhite : KDColorBlack;

  ctx->drawString(m_function->text(), KDPointZero, text, textBackground);
  // m_function->layout()->draw(ctx, KDPointZero);
}

void FunctionCell::setFunction(Graph::Function * f) {
  m_function = f;
}

void FunctionCell::didBecomeFirstResponder() {
  m_focused = true;
  markRectAsDirty(bounds());
}

void FunctionCell::didResignFirstResponder() {
  m_focused = false;
  markRectAsDirty(bounds());
}

void FunctionCell::setEven(bool even) {
  m_even = even;
}