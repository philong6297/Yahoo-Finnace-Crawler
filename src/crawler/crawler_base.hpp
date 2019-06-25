#ifndef YAHOOFINANCECRAWLER_CRAWLER_BASE_HPP
#define YAHOOFINANCECRAWLER_CRAWLER_BASE_HPP
#include <cpr/cpr.h>
#include <htmlcxx/html/ParserDom.h>
#include <QtCore>
#include "base/crtp.hpp"

namespace longlp {
  template <typename Derived>
  class CrawlerBase : public longlp::base::crtp<Derived, CrawlerBase> {
   public:
    struct FilteredData;

    [[nodiscard]] CrawlerBase<Derived>::FilteredData Process() const {
      cpr::Header     header     = {{"Accept", "text/plain"},
                            {"Cache-Control", "no-cache"},
                            {"Connection", "keep-alive"},
                            {"Content-Type", "text/plain; charset=utf-8"},
                            {"cache-control", "no-cache"}};
      auto            underlying = this->underlying();
      cpr::Url        url        = underlying.GetURL();
      cpr::Parameters params     = underlying.GetParameters();
      auto            request    = cpr::GetAsync(url, params, header);

      qInfo() << "Sending request " << url.data();
      request.wait();
      const auto received = request.get();
      qInfo() << "Request received with status: " << received.status_code;

      qInfo() << "Start parsing data to DOM";
      ParserDom parser;
      Tree      dom = parser.parseTree(received.text);

      return underlying.ProcessImpl(dom);
    }

   private:
    using ParserDom = htmlcxx::HTML::ParserDom;
    using Node      = htmlcxx::HTML::Node;
    using Tree      = tree<Node>;
    friend Derived;
  };
}  // namespace longlp
#endif  // YAHOOFINANCECRAWLER_CRAWLER_BASE_HPP
