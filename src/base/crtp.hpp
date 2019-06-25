#ifndef SRC_BASE_CRTP_HPP
#define SRC_BASE_CRTP_HPP

namespace longlp::base {
  template <typename T, template <typename> class /*CRTPType*/>
  struct crtp {
    [[nodiscard]] T&       underlying() { return static_cast<T&>(*this); }
    [[nodiscard]] const T& underlying() const { return static_cast<const T&>(*this); }
  };
}  // namespace longlp::base

#endif  // SRC_BASE_CRTP_HPP
