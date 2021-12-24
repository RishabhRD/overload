#include <string>
#include <boost/ut.hpp>
#include <overload.hpp>

using namespace boost::ext::ut;
using std::literals::string_view_literals::operator""sv;

int main() {
  "lambda overloading"_test = [] {
    rd::overload identity{
      [](int x) { return x; },
      [](std::string_view str) { return str; },
      [](double d) { return d; },
    };
    expect(identity(2) == 2_i);
    expect(identity(2.5) == 2.5_d);
    expect(eq(identity("Hello World!"sv), "Hello World!"sv));
  };

  "function object overloading"_test = [] {
    struct integral_identity_t {// NOLINT
      auto operator()(int x) const noexcept { return x; }

      auto operator()(double x) const noexcept { return x; }
    };

    struct string_identity_t {// NOLINT
      auto operator()(std::string_view x) const noexcept { return x; }
    };

    rd::overload identity{
      integral_identity_t{},
      string_identity_t{},
    };
    expect(identity(2) == 2_i);
    expect(identity(2.5) == 2.5_d);
    expect(eq(identity("Hello World!"sv), "Hello World!"sv));
  };

  "function object and lambda overloading"_test = [] {
    struct integral_identity_t {// NOLINT
      auto operator()(int x) const noexcept { return x; }

      auto operator()(double x) const noexcept { return x; }
    };

    rd::overload identity{
      integral_identity_t{},
      [](std::string_view x) { return x; },
    };
    expect(identity(2) == 2_i);
    expect(identity(2.5) == 2.5_d);
    expect(eq(identity("Hello World!"sv), "Hello World!"sv));
  };
}
