#include <QDateTime>
#include <crawler/crawler.hpp>
#include <string_view>
namespace {
  namespace lpl = longlp;

}  // namespace
void runCryptoCrawler(size_t limit, const QString& path);
void runCurrencies(size_t limit, const QString& path);
void runWorldIndices(size_t limit, const QString& path);
void runStockGainer(size_t limit, const QString& path);
void runStockLoser(size_t limit, const QString& path);

int main(int argc, char* argv[]) {
  QCoreApplication app(argc, argv);
  QCoreApplication::setApplicationName("Yahoo Finance Crawler");
  QCoreApplication::setApplicationVersion("1.0");

  QCommandLineParser parser;
  parser.addHelpOption();
  parser.addVersionOption();
  parser.addOptions(
      {{QStringList() << "m"
                      << "mode",
        "<1|2|3|4|5> for Crypto currencies/Currencies/World indices/Stock gainers/Stock losers",
        "mode"},
       {QStringList() << "n", "Number of records to receive", "number_of_records", "10"},
       {QStringList() << "p"
                      << "path",
        "Path to csv file to store data",
        "csv_path",
        ""}});

  // Process the actual command line arguments given by the user
  parser.process(app);

  // parse options
  if (parser.isSet("mode")) {
    const auto mode = parser.value("mode").toInt();
    const auto n    = parser.value("n").toULong();
    const auto path = parser.value("p");

    qInfo() << "Detected mode: " << mode;
    qInfo() << "Number of record: " << n << (n == 10 ? "(default)" : "");
    qInfo() << "Path: " << (path.isEmpty() ? "Not specified" : path);
    if (mode == 1) {
      runCryptoCrawler(n, path);
    }
    else if (mode == 2) {
      runCurrencies(n, path);
    }
    else if (mode == 3) {
      runWorldIndices(n, path);
    }
    else if (mode == 4) {
      runStockGainer(n, path);
    }
    else if (mode == 5) {
      runStockLoser(n, path);
    }
  }
  else {
    parser.showHelp();
  }

  return 0;
}

void runWorldIndices(size_t limit, const QString& path) {
  lpl::WorldIndices crawler;
  const auto        data = crawler.Process();
  qInfo() << "Result:";
  if (path.isEmpty()) {
    qInfo().noquote() << "Date: " << QTime::currentTime().toString("mm:hh")
                      << QDate::currentDate().toString("dd.MM.yyyy");
    qInfo().noquote() << QString(" %1 | %2 | %3 | %4 | %5 | %6 ")
                             .arg("Symbol", -10)
                             .arg("Name", -25)
                             .arg("Last Price", 10)
                             .arg("Change", 12)
                             .arg("Change (%)", 10)
                             .arg("Volume", 10)
                      << endl;
    for (auto i = 0UL; i < std::min(limit, data.symbol.size()); ++i) {
      qInfo().noquote() << QString(" %1 | %2 | %3 | %4 | %5 | %6 ")
                               .arg(data.symbol.at(i).data(), -10)
                               .arg(data.name.at(i).data(), -25)
                               .arg(data.last_price.at(i).data(), 10)
                               .arg(data.change.at(i).data(), 12)
                               .arg(data.change_rate.at(i).data(), 10)
                               .arg(data.volume.at(i).data(), 10)
                        << endl;
    }
  }
  else {
    QFile file(path);
    if (file.open(QFile::WriteOnly | QFile::Truncate)) {
      QTextStream stream(&file);
      stream << "symbol,"
             << "name,"
             << "last_price,"
             << "change,"
             << "change_rate,"
             << "volume" << endl;
      for (auto i = 0UL; i < std::min(limit, data.symbol.size()); ++i) {
        stream << QString("%1,%2,%3,%4,%5,%6")
                      .arg(data.symbol.at(i).data())
                      .arg(data.name.at(i).data())
                      .arg(data.last_price.at(i).data())
                      .arg(data.change.at(i).data())
                      .arg(data.change_rate.at(i).data())
                      .arg(data.volume.at(i).data())
               << endl;
      }
      qInfo() << "Write to " << path;
    }
    else {
      qInfo() << "Cannot open " << path;
    }
  }
}

void runCryptoCrawler(size_t limit, const QString& path) {
  lpl::Crypto crawler;
  const auto  data = crawler.Process();
  qInfo() << "Result:";
  if (path.isEmpty()) {
    qInfo().noquote() << "Date: " << QTime::currentTime().toString("mm:hh")
                      << QDate::currentDate().toString("dd.MM.yyyy");
    qInfo().noquote() << QString(" %1 | %2 | %3 | %4 | %5 | %6 | %7 | %8 | %9 | %10 ")
                             .arg("Symbol", -10)
                             .arg("Name", -25)
                             .arg("Price (intraday)", 16)
                             .arg("Change", 12)
                             .arg("Change (%)", 10)
                             .arg("Market Cap", 10)
                             .arg("Volume (0:00 UTC)", 17)
                             .arg("Volume (24h)", 12)
                             .arg("Total Volume (24h)", 18)
                             .arg("Circulating Supply", 18)
                      << endl;
    for (auto i = 0UL; i < std::min(limit, data.symbol.size()); ++i) {
      qInfo().noquote() << QString(" %1 | %2 | %3 | %4 | %5 | %6 | %7 | %8 | %9 | %10 ")
                               .arg(data.symbol.at(i).data(), -10)
                               .arg(data.name.at(i).data(), -25)
                               .arg(data.price_intraday.at(i).data(), 16)
                               .arg(data.change.at(i).data(), 12)
                               .arg(data.change_rate.at(i).data(), 10)
                               .arg(data.market_cap.at(i).data(), 10)
                               .arg(data.volume_in_currency_since_0_utc.at(i).data(), 17)
                               .arg(data.volume_in_currency_24h.at(i).data(), 12)
                               .arg(data.volume_in_currency_total_24h.at(i).data(), 18)
                               .arg(data.circulating_supply.at(i).data(), 18)
                        << endl;
    }
  }
  else {
    QFile file(path);
    if (file.open(QFile::WriteOnly | QFile::Truncate)) {
      QTextStream stream(&file);
      stream << "symbol,"
             << "name,"
             << "price_intraday,"
             << "change,"
             << "change_rate,"
             << "market_cap,"
             << "volume_in_currency_since_0_utc,"
             << "volume_in_currency_24h,"
             << "volume_in_currency_total_24h,"
             << "circulating_supply" << endl;
      for (auto i = 0UL; i < std::min(limit, data.symbol.size()); ++i) {
        stream << QString("%1,%2,%3,%4,%5,%6,%7,%8,%9,%10")
                      .arg(data.symbol.at(i).data())
                      .arg(data.name.at(i).data())
                      .arg(data.price_intraday.at(i).data())
                      .arg(data.change.at(i).data())
                      .arg(data.change_rate.at(i).data())
                      .arg(data.market_cap.at(i).data())
                      .arg(data.volume_in_currency_since_0_utc.at(i).data())
                      .arg(data.volume_in_currency_24h.at(i).data())
                      .arg(data.volume_in_currency_total_24h.at(i).data())
                      .arg(data.circulating_supply.at(i).data())
               << endl;
      }
      qInfo() << "Write to " << path;
    }
    else {
      qInfo() << "Cannot open " << path;
    }
  }
}

void runCurrencies(size_t limit, const QString& path) {
  lpl::Currencies crawler;
  const auto      data = crawler.Process();
  qInfo() << "Result:";
  if (path.isEmpty()) {
    qInfo().noquote() << "Date: " << QTime::currentTime().toString("mm:hh")
                      << QDate::currentDate().toString("dd.MM.yyyy");
    qInfo().noquote() << QString(" %1 | %2 | %3 | %4 | %5 ")
                             .arg("Symbol", -10)
                             .arg("Name", -25)
                             .arg("Last Price", 10)
                             .arg("Change", 12)
                             .arg("Change (%)", 10)
                      << endl;
    for (auto i = 0UL; i < std::min(limit, data.symbol.size()); ++i) {
      qInfo().noquote() << QString(" %1 | %2 | %3 | %4 | %5 ")
                               .arg(data.symbol.at(i).data(), -10)
                               .arg(data.name.at(i).data(), -25)
                               .arg(data.last_price.at(i).data(), 10)
                               .arg(data.change.at(i).data(), 12)
                               .arg(data.change_rate.at(i).data(), 10)
                        << endl;
    }
  }
  else {
    QFile file(path);
    if (file.open(QFile::WriteOnly | QFile::Truncate)) {
      QTextStream stream(&file);
      stream << "symbol,"
             << "name,"
             << "last_price,"
             << "change,"
             << "change_rate" << endl;
      for (auto i = 0UL; i < std::min(limit, data.symbol.size()); ++i) {
        stream << QString("%1,%2,%3,%4,%5")
                      .arg(data.symbol.at(i).data())
                      .arg(data.name.at(i).data())
                      .arg(data.last_price.at(i).data())
                      .arg(data.change.at(i).data())
                      .arg(data.change_rate.at(i).data())
               << endl;
      }
      qInfo() << "Write to " << path;
    }
    else {
      qInfo() << "Cannot open " << path;
    }
  }
}

void runStockGainer(size_t limit, const QString& path) {
  lpl::StockGainer crawler;
  const auto       data = crawler.Process();
  qInfo() << "Result:";
  if (path.isEmpty()) {
    qInfo().noquote() << "Date: " << QTime::currentTime().toString("mm:hh")
                      << QDate::currentDate().toString("dd.MM.yyyy");
    qInfo().noquote() << QString(" %1 | %2 | %3 | %4 | %5 | %6 | %7 | %8 | %9 ")
                             .arg("Symbol", -10)
                             .arg("Name", -35)
                             .arg("Price (intraday)", 16)
                             .arg("Change", 12)
                             .arg("Change (%)", 10)
                             .arg("Volume", 10)
                             .arg("Avg Volume (3 Months)", 21)
                             .arg("Market Cap", 10)
                             .arg("PE Ratio", 8)
                      << endl;
    for (auto i = 0UL; i < std::min(limit, data.symbol.size()); ++i) {
      qInfo().noquote() << QString(" %1 | %2 | %3 | %4 | %5 | %6 | %7 | %8 | %9 ")
                               .arg(data.symbol.at(i).data(), -10)
                               .arg(data.name.at(i).data(), -35)
                               .arg(data.price_intraday.at(i).data(), 16)
                               .arg(data.change.at(i).data(), 12)
                               .arg(data.change_rate.at(i).data(), 10)
                               .arg(data.volume.at(i).data(), 10)
                               .arg(data.avg_volume_3_months.at(i).data(), 21)
                               .arg(data.market_cap.at(i).data(), 10)
                               .arg(data.pe_ratio.at(i).data(), 8)
                        << endl;
    }
  }
  else {
    QFile file(path);
    if (file.open(QFile::WriteOnly | QFile::Truncate)) {
      QTextStream stream(&file);
      stream << "symbol,"
             << "name,"
             << "price_intraday,"
             << "change,"
             << "change_rate,"
             << "volume,"
             << "avg_volume_3_months,"
             << "market_cap,"
             << "pe_ratio" << endl;
      for (auto i = 0UL; i < std::min(limit, data.symbol.size()); ++i) {
        stream << QString("%1,%2,%3,%4,%5,%6,%7,%8,%9")
                      .arg(data.symbol.at(i).data())
                      .arg(data.name.at(i).data())
                      .arg(data.price_intraday.at(i).data())
                      .arg(data.change.at(i).data())
                      .arg(data.change_rate.at(i).data())
                      .arg(data.volume.at(i).data())
                      .arg(data.avg_volume_3_months.at(i).data())
                      .arg(data.market_cap.at(i).data())
                      .arg(data.pe_ratio.at(i).data())
               << endl;
      }
      qInfo() << "Write to " << path;
    }
    else {
      qInfo() << "Cannot open " << path;
    }
  }
}

void runStockLoser(size_t limit, const QString& path) {
  lpl::StockLoser crawler;
  const auto      data = crawler.Process();
  qInfo() << "Result:";
  if (path.isEmpty()) {
    qInfo().noquote() << "Date: " << QTime::currentTime().toString("mm:hh")
                      << QDate::currentDate().toString("dd.MM.yyyy");
    qInfo().noquote() << QString(" %1 | %2 | %3 | %4 | %5 | %6 | %7 | %8 | %9 ")
                             .arg("Symbol", -10)
                             .arg("Name", -35)
                             .arg("Price (intraday)", 16)
                             .arg("Change", 12)
                             .arg("Change (%)", 10)
                             .arg("Volume", 10)
                             .arg("Avg Volume (3 Months)", 21)
                             .arg("Market Cap", 10)
                             .arg("PE Ratio", 8)
                      << endl;
    for (auto i = 0UL; i < std::min(limit, data.symbol.size()); ++i) {
      qInfo().noquote() << QString(" %1 | %2 | %3 | %4 | %5 | %6 | %7 | %8 | %9 ")
                               .arg(data.symbol.at(i).data(), -10)
                               .arg(data.name.at(i).data(), -35)
                               .arg(data.price_intraday.at(i).data(), 16)
                               .arg(data.change.at(i).data(), 12)
                               .arg(data.change_rate.at(i).data(), 10)
                               .arg(data.volume.at(i).data(), 10)
                               .arg(data.avg_volume_3_months.at(i).data(), 21)
                               .arg(data.market_cap.at(i).data(), 10)
                               .arg(data.pe_ratio.at(i).data(), 8)
                        << endl;
    }
  }
  else {
    QFile file(path);
    if (file.open(QFile::WriteOnly | QFile::Truncate)) {
      QTextStream stream(&file);
      stream << "symbol,"
             << "name,"
             << "price_intraday,"
             << "change,"
             << "change_rate,"
             << "volume,"
             << "avg_volume_3_months,"
             << "market_cap,"
             << "pe_ratio" << endl;
      for (auto i = 0UL; i < std::min(limit, data.symbol.size()); ++i) {
        stream << QString("%1,%2,%3,%4,%5,%6,%7,%8,%9")
                      .arg(data.symbol.at(i).data())
                      .arg(data.name.at(i).data())
                      .arg(data.price_intraday.at(i).data())
                      .arg(data.change.at(i).data())
                      .arg(data.change_rate.at(i).data())
                      .arg(data.volume.at(i).data())
                      .arg(data.avg_volume_3_months.at(i).data())
                      .arg(data.market_cap.at(i).data())
                      .arg(data.pe_ratio.at(i).data())
               << endl;
      }
      qInfo() << "Write to " << path;
    }
    else {
      qInfo() << "Cannot open " << path;
    }
  }
}
