#pragma once

#include <string>

namespace mg {
namespace priv {

void storeError(const std::string& msg, const std::string& prefix = "[Error]", const std::string& prefix2 = std::string());

} // namespace priv

const std::string& getError();

} // namespace mg
