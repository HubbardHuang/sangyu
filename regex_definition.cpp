#include "regex_definition.h"

namespace sangyu {

const RegexDefinition::unit_type RegexDefinition::kLeftBracket_ = -1,
                                 RegexDefinition::kRightBracket_ = -2,
                                 RegexDefinition::kClosureOperator_ = -3,
                                 RegexDefinition::kOrOperator_ = -4,
                                 RegexDefinition::kJoinOperator_ = -5,
                                 RegexDefinition::kStartSymbol_ = 1,
                                 RegexDefinition::kStopSymbol_ = 2;

std::map<RegexDefinition::unit_type, size_t> RegexDefinition::priority = {
    { RegexDefinition::kOrOperator_, 1 },
    { RegexDefinition::kJoinOperator_, 2 },
    { RegexDefinition::kClosureOperator_, 3 },
    { RegexDefinition::kRightBracket_, 0 },
    { RegexDefinition::kLeftBracket_, 0 }
};

bool
RegexDefinition::IsOperator(RegexDefinition::unit_type u) {
    return u < 0;
}

bool
RegexDefinition::IsValueUnit(RegexDefinition::unit_type u) {
    return u != kLeftBracket_ && u != kRightBracket_;
}

} // namespace sangyu