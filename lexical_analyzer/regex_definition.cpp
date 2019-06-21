#include "regex_definition.h"

namespace sangyu {

const RegexDefinition::unit_type RegexDefinition::kLeftRoundBracket_ = -1,
                                 RegexDefinition::kRightRoundBracket_ = -2,
                                 RegexDefinition::kClosureOperator_ = -3,
                                 RegexDefinition::kOrOperator_ = -4,
                                 RegexDefinition::kJoinOperator_ = -5,
                                 RegexDefinition::kStartSymbol_ = 1,
                                 RegexDefinition::kStopSymbol_ = 2,
                                 RegexDefinition::kEpsilon = kContentTypes - 1;

std::map<RegexDefinition::unit_type, size_t> RegexDefinition::priority = {
    { RegexDefinition::kOrOperator_, 1 },
    { RegexDefinition::kJoinOperator_, 2 },
    { RegexDefinition::kClosureOperator_, 3 },
    { RegexDefinition::kRightRoundBracket_, 0 },
    { RegexDefinition::kLeftRoundBracket_, 0 }
};

bool
RegexDefinition::IsOperator(RegexDefinition::unit_type u) {
    return u < 0;
}

bool
RegexDefinition::IsValidOperator(RegexDefinition::unit_type u) {
    return u == kClosureOperator_ || u == kOrOperator_ || u == kJoinOperator_;
}

bool
RegexDefinition::IsValueUnit(RegexDefinition::unit_type u) {
    return u != kLeftRoundBracket_ && u != kRightRoundBracket_;
}

} // namespace sangyu