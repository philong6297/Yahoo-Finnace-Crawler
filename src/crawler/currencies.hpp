#ifndef YAHOOFINANCECRAWLER_CURRENCIES_HPP
#define YAHOOFINANCECRAWLER_CURRENCIES_HPP

#include <string>
#include <vector>
#include "crawler/crawler_base.hpp"
namespace longlp {

  class Currencies;

  template <>
  struct CrawlerBase<Currencies>::FilteredData {
    std::vector<std::string> symbol;
    std::vector<std::string> name;
    std::vector<std::string> last_price;
    std::vector<std::string> change;
    std::vector<std::string> change_rate;
  };

  class Currencies final : public CrawlerBase<Currencies> {
   public:
    using FilteredData = CrawlerBase<Currencies>::FilteredData;

   private:
    friend CrawlerBase<Currencies>;
    [[nodiscard]] FilteredData ProcessImpl(Tree& dom) const;

    [[nodiscard]] cpr::Url GetURL() const { return "https://finance.yahoo.com/currencies"; }

    [[nodiscard]] cpr::Parameters GetParameters() const {
      return {{"offset", "0"}, {"count", "100"}};
    }
  };

}  // namespace longlp

#endif  // YAHOOFINANCECRAWLER_CURRENCIES_HPP
