#ifndef YAHOOFINANCECRAWLER_STOCK_GAINER_HPP
#define YAHOOFINANCECRAWLER_STOCK_GAINER_HPP

#include <string>
#include <vector>
#include "crawler/crawler_base.hpp"
namespace longlp {

  class StockGainer;

  template <>
  struct CrawlerBase<StockGainer>::FilteredData {
    std::vector<std::string> symbol;
    std::vector<std::string> name;
    std::vector<std::string> price_intraday;
    std::vector<std::string> change;
    std::vector<std::string> change_rate;
    std::vector<std::string> volume;
    std::vector<std::string> avg_volume_3_months;
    std::vector<std::string> market_cap;
    std::vector<std::string> pe_ratio;
  };

  class StockGainer final : public CrawlerBase<StockGainer> {
   public:
    using FilteredData = CrawlerBase<StockGainer>::FilteredData;

   private:
    friend CrawlerBase<StockGainer>;
    [[nodiscard]] FilteredData ProcessImpl(Tree& dom) const;

    [[nodiscard]] cpr::Url GetURL() const { return "https://finance.yahoo.com/gainers"; }

    [[nodiscard]] cpr::Parameters GetParameters() const {
      return {{"offset", "0"}, {"count", "100"}};
    }
  };

}  // namespace longlp

#endif  // YAHOOFINANCECRAWLER_STOCK_GAINER_HPP
