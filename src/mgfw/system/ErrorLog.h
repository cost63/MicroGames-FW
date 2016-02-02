#pragma once

#include <string>

namespace mg {
namespace priv {

// Store error message in internal value so it can be received on request
// This function also handles error printing/logging
void storeError(const std::string& msg,
                const std::string& prefix = "[Error]",
                const std::string& prefix2 = std::string());

} // namespace priv

// Returns stored error message. Empty string if no message was stored yet
const std::string& getError() const;

} // namespace mg
