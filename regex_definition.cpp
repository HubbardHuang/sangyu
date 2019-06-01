#include "regex_definition.h"

namespace sangyu {

const RegexDefinition::unit_type RegexDefinition::kLeftBracket_ = -1,
                                 RegexDefinition::kRightBracket_ = -2,
                                 RegexDefinition::kClosureOperator_ = -3,
                                 RegexDefinition::kOrOperator_ = -4,
                                 RegexDefinition::kJoinOperator_ = -5,
                                 RegexDefinition::kStartSymbol_ = 1,
                                 RegexDefinition::kStopSymbol_ = 2;
}