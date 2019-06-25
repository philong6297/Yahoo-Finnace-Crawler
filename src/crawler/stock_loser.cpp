#include "crawler/stock_loser.hpp"
namespace {
  using ColumnIndex                         = uint32_t;
  constexpr ColumnIndex SYMBOL              = 0;
  constexpr ColumnIndex NAME                = 1;
  constexpr ColumnIndex PRICE_INTRADAY      = 2;
  constexpr ColumnIndex CHANGE              = 3;
  constexpr ColumnIndex CHANGE_RATE         = 4;
  constexpr ColumnIndex VOLUME              = 5;
  constexpr ColumnIndex AVG_VOLUME_3_MONTHS = 6;
  constexpr ColumnIndex MARKET_CAP          = 7;
  constexpr ColumnIndex PE_RATIO            = 8;
}  // namespace

namespace longlp {
  StockLoser::FilteredData StockLoser::ProcessImpl(Tree& dom) const {
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

          if (record.size() == 9) {
            result.symbol.push_back(record.at(SYMBOL));
            result.name.push_back(record.at(NAME));
            result.price_intraday.push_back(record.at(PRICE_INTRADAY));
            result.change.push_back(record.at(CHANGE));
            result.change_rate.push_back(record.at(CHANGE_RATE));
            result.volume.push_back(record.at(VOLUME));
            result.avg_volume_3_months.push_back(record.at(AVG_VOLUME_3_MONTHS));
            result.market_cap.push_back(record.at(MARKET_CAP));
            result.pe_ratio.push_back(record.at(PE_RATIO));
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
