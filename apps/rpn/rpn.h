#ifndef RPN_RPN_H
#define RPN_RPN_H

#include <escher.h>
#include <poincare.h>

namespace Rpn {

class Rpn {
public:
  Rpn();
  ~Rpn(); // Delete expression and layout, if needed
  Rpn& operator=(const Rpn& other);
  Rpn(const Rpn& other) = delete;
  Rpn(Rpn&& other) = delete;
  Rpn& operator=(Rpn&& other) = delete;
  /* c.reset() is the equivalent of c = Rpn() without copy assingment. */
  void reset();
  const char * inputText();
  const char * outputText();
  Poincare::Expression * input();
  Poincare::ExpressionLayout * inputLayout();
  Poincare::Evaluation<double> * output(Poincare::Context * context);
  Poincare::ExpressionLayout * outputLayout(Poincare::Context * context);
  void setContent(const char * c, Poincare::Context * context);
  bool isEmpty();
  void tidy();
private:
  char m_inputText[::TextField::maxBufferSize()];
  char m_outputText[2*::TextField::maxBufferSize()];
  Poincare::Expression * m_input;
  Poincare::ExpressionLayout * m_inputLayout;
  Poincare::Evaluation<double> * m_output;
  Poincare::ExpressionLayout * m_outputLayout;
};

}

#endif
