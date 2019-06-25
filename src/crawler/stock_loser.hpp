#ifndef YAHOOFINANCECRAWLER_STOCK_LOSER_HPP
#define YAHOOFINANCECRAWLER_STOCK_LOSER_HPP

#include <string>
#include <vector>
#include "crawler/crawler_base.hpp"
namespace longlp {

  class StockLoser;

  template <>
  struct CrawlerBase<StockLoser>::FilteredData {
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

  class StockLoser final : public CrawlerBase<StockLoser> {
   public:
    using FilteredData = CrawlerBase<StockLoser>::FilteredData;

   private:
    friend CrawlerBase<StockLoser>;
    [[nodiscard]] FilteredData ProcessImpl(Tree& dom) const;

    [[nodiscard]] cpr::Url GetURL() const { return "https://finance.yahoo.com/losers"; }

    [[nodiscard]] cpr::Parameters GetParameters() const {
      return {{"offset", "0"}, {"count", "100"}};
    }
  };

}  // namespace longlp

#endif  // YAHOOFINANCECRAWLER_STOCK_LOSER_HPP
