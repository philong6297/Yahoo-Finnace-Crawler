#ifndef YAHOOFINANCECRAWLER_CRYPTO_HPP
#define YAHOOFINANCECRAWLER_CRYPTO_HPP

#include <string>
#include <vector>
#include "crawler/crawler_base.hpp"
namespace longlp {

  class Crypto;

  template <>
  struct CrawlerBase<Crypto>::FilteredData {
    std::vector<std::string> symbol;
    std::vector<std::string> name;
    std::vector<std::string> price_intraday;
    std::vector<std::string> change;
    std::vector<std::string> change_rate;
    std::vector<std::string> market_cap;
    std::vector<std::string> volume_in_currency_since_0_utc;
    std::vector<std::string> volume_in_currency_24h;
    std::vector<std::string> volume_in_currency_total_24h;
    std::vector<std::string> circulating_supply;
  };

  class Crypto final : public CrawlerBase<Crypto> {
   public:
    using FilteredData = CrawlerBase<Crypto>::FilteredData;

   private:
    friend CrawlerBase<Crypto>;
    [[nodiscard]] FilteredData ProcessImpl(Tree& dom) const;

    [[nodiscard]] cpr::Url GetURL() const { return "https://finance.yahoo.com/cryptocurrencies"; }

    [[nodiscard]] cpr::Parameters GetParameters() const {
      return {{"offset", "0"}, {"count", "100"}};
    }
  };

}  // namespace longlp

#endif  // YAHOOFINANCECRAWLER_CRYPTO_HPP
