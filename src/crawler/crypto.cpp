#include "crawler/crypto.hpp"
namespace {
  using ColumnIndex                                    = uint32_t;
  constexpr ColumnIndex SYMBOL                         = 0;
  constexpr ColumnIndex NAME                           = 1;
  constexpr ColumnIndex PRICE_INTRADAY                 = 2;
  constexpr ColumnIndex CHANGE                         = 3;
  constexpr ColumnIndex CHANGE_RATE                    = 4;
  constexpr ColumnIndex MARKET_CAP                     = 5;
  constexpr ColumnIndex VOLUME_IN_CURRENCY_SINCE_0_UTC = 6;
  constexpr ColumnIndex VOLUME_IN_CURRENCY_24H         = 7;
  constexpr ColumnIndex VOLUME_IN_CURRENCY_TOTAL_24H   = 8;
  constexpr ColumnIndex CIRCULATING_SUPPLY             = 9;
}  // namespace

namespace longlp {
  Crypto::FilteredData Crypto::ProcessImpl(Tree& dom) const {
    qInfo() << "Start filtering...";
    FilteredData result;
    int          record_count = 0;
    for (auto find_record_it = dom.begin(); find_record_it != dom.end(); ++find_record_it) {
      if (find_record_it->tagName() == "tr") {
        find_record_it->parseAttributes();

        // found record
        if (QString class_list = data(find_record_it->attribute("class").second);
            class_list.startsWith("simpTblRow", Qt::CaseSensitivity::CaseSensitive)) {
          ++record_count;

          std::vector<std::string> record;

          for (auto column_idx = 0U; column_idx < dom.number_of_children(find_record_it);
               ++column_idx) {
            const Tree column_subtree = dom.child(find_record_it, column_idx);
            for (auto& node : column_subtree) {
              if ((not node.isTag()) and (not node.isComment())) {
                record.push_back(node.text());
              }
            }
          }

          if (record.size() == 10) {
            result.symbol.push_back(record.at(SYMBOL));
            result.name.push_back(record.at(NAME));
            result.price_intraday.push_back(record.at(PRICE_INTRADAY));
            result.change.push_back(record.at(CHANGE));
            result.change_rate.push_back(record.at(CHANGE_RATE));
            result.market_cap.push_back(record.at(MARKET_CAP));
            result.volume_in_currency_since_0_utc.push_back(
                record.at(VOLUME_IN_CURRENCY_SINCE_0_UTC));
            result.volume_in_currency_24h.push_back(record.at(VOLUME_IN_CURRENCY_24H));
            result.volume_in_currency_total_24h.push_back(record.at(VOLUME_IN_CURRENCY_TOTAL_24H));
            result.circulating_supply.push_back(record.at(CIRCULATING_SUPPLY));
          }
        }
      }
    }

    qInfo() << "Records found: " << record_count;
    qInfo() << "Valid Records: " << result.symbol.size();
    qInfo() << "Finish.";
    return result;
  }
}  // namespace longlp
