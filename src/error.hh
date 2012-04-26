#ifndef ERROR_HH_
#define ERROR_HH_

#include <stdexcept>
#include <string>

namespace sws {
struct invalid_token : std::runtime_error {
    invalid_token(std::string const& m) : std::runtime_error(m) { }
};
}  // namespace sws

#endif  // ERROR_HH_
