#ifndef REGEX_DEFINITION_H
#define REGEX_DEFINITION_H

#include <map>
#include <string>

namespace sangyu {

class RegexDefinition {
protected:
    using unit_type = std::string::value_type;

protected:
    static const unit_type kLeftBracket_;
    static const unit_type kRightBracket_;
    static const unit_type kClosureOperator_;
    static const unit_type kOrOperator_;
    static const unit_type kJoinOperator_;
    static const unit_type kStartSymbol_;
    static const unit_type kStopSymbol_;

protected:
    static std::map<unit_type, size_t> priority;

protected:
    static bool IsOperator(unit_type u);
    static bool IsValueUnit(unit_type u);
};

} // namespace sangyu

#endif