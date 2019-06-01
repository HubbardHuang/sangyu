#ifndef REGEX_DEFINITION_H
#define REGEX_DEFINITION_H

#include <string>

namespace sangyu {

class RegexDefinition {
protected:
    using unit_type = std::string::value_type;
    static const unit_type kLeftBracket_;
    static const unit_type kRightBracket_;
    static const unit_type kClosureOperator_;
    static const unit_type kOrOperator_;
    static const unit_type kJoinOperator_;
    static const unit_type kStartSymbol_;
    static const unit_type kStopSymbol_;
};

} // namespace sangyu

#endif