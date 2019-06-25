#include "crawler/world_indices.hpp"

namespace {
  using ColumnIndex                 = uint32_t;
  constexpr ColumnIndex SYMBOL      = 0;
  constexpr ColumnIndex NAME        = 1;
  constexpr ColumnIndex LAST_PRICE  = 2;
  constexpr ColumnIndex CHANGE      = 3;
  constexpr ColumnIndex CHANGE_RATE = 4;
  constexpr ColumnIndex VOLUME      = 5;

}  // namespace

namespace longlp {
  WorldIndices::FilteredData WorldIndices::ProcessImpl(Tree& dom) const {
    qInfo() << "Start filtering...";
    FilteredData result;
    int          record_count = 0;
    for (auto find_record_it = dom.begin(); find_record_it != dom.end(); ++find_record_it) {
      if (find_record_it->tagName() == "tr") {
        find_record_it->parseAttributes();

        // found record
        if (QString class_list = data(find_record_it->attribute("class").second);
            class_list.startsWith("data-row", Qt::CaseSensitivity::CaseSensitive)) {
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

          if (record.size() == 6) {
            result.symbol.push_back(record.at(SYMBOL));
            result.name.push_back(record.at(NAME));
            result.last_price.push_back(record.at(LAST_PRICE));
            result.change.push_back(record.at(CHANGE));
            result.change_rate.push_back(record.at(CHANGE_RATE));
            result.volume.push_back(record.at(VOLUME));
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
