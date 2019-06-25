#ifndef YAHOOFINANCECRAWLER_WORLD_INDICES_HPP
#define YAHOOFINANCECRAWLER_WORLD_INDICES_HPP

#include <string>
#include <vector>
#include "crawler/crawler_base.hpp"

namespace longlp {

  class WorldIndices;

  template <>
  struct CrawlerBase<WorldIndices>::FilteredData {
    std::vector<std::string> symbol;
    std::vector<std::string> name;
    std::vector<std::string> last_price;
    std::vector<std::string> change;
    std::vector<std::string> change_rate;
    std::vector<std::string> volume;
  };

  class WorldIndices final : public CrawlerBase<WorldIndices> {
   public:
    using FilteredData = CrawlerBase<WorldIndices>::FilteredData;

   private:
    friend CrawlerBase<WorldIndices>;
    [[nodiscard]] FilteredData ProcessImpl(Tree& dom) const;

    [[nodiscard]] cpr::Url GetURL() const { return "https://finance.yahoo.com/world-indices"; }

    [[nodiscard]] cpr::Parameters GetParameters() const {
      return {{"offset", "0"}, {"count", "100"}};
    }
  };
}  // namespace longlp
#endif  // YAHOOFINANCECRAWLER_WORLD_INDICES_HPP
