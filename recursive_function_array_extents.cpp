template <typename T> 
constexpr auto StringProxy()
{
  struct proxy
  {
    constexpr bool operator==(char const* s)
    {
        using R = decltype(T{}({}));

        if constexpr (sizeof(R) == 1)
            return !*s;
        else
        {
          T chr_cmp = [](auto const& a)
          {
            if (a[0] == char{sizeof(a)})
                return R{};
            else
                return R{[](auto const&)->decltype(R{}({})){return{};}};
          };
          return chr_cmp({*s})==R{} && StringProxy<R>()==s+1;
        }
    }
  };
  return proxy{};
}

static_assert(
  StringProxy
  <
    auto(*)(char const(&)['S'])->
    auto(*)(char const(&)['t'])->
    auto(*)(char const(&)['r'])->
    auto(*)(char const(&)['i'])->
    auto(*)(char const(&)['n'])->
    auto(*)(char const(&)['g'])->
    auto(*)(char const(&)['P'])->
    auto(*)(char const(&)['r'])->
    auto(*)(char const(&)['o'])->
    auto(*)(char const(&)['x'])->
    auto(*)(char const(&)['y'])->
    char(*)(char const&) // EOS
  >
   () == "StringProxy", "");

int main() { return 0; }
