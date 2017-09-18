#ifndef RPN_TEXT_FIELD_H
#define RPN_TEXT_FIELD_H

#include <escher.h>

namespace Rpn {

class TextField : public ::TextField {
public:
  TextField(Responder * parentResponder, char * textBuffer, size_t textBufferSize, TextFieldDelegate * delegate);
  bool handleEvent(Ion::Events::Event event) override;
};

}

#endif
