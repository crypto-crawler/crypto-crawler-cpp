#include "include/crypto_crawler.h"

#include <array>
#include <cstring>
#include <iostream>

static inline bool is_null_terminated_view(std::string_view sv) noexcept {
  return !sv.empty() && sv.data()[sv.length()] == '\0';
}

static std::vector<const char *> convert_symbols(
    const std::vector<std::string> &symbols) {
  std::vector<const char *> result;
  std::transform(
      symbols.begin(), symbols.end(), std::back_inserter(result),
      [](const std::string &symbol) -> const char * { return symbol.c_str(); });
  return result;
}

void crawl_template(std::string_view exchange, MarketType market_type,
                    const std::vector<std::string> &symbols,
                    void (*on_msg)(const Message *), uint64_t duration,
                    void (*crawl_ffi_func)(const char *, MarketType,
                                           const char *const *, unsigned int,
                                           void (*)(const Message *),
                                           uint64_t)) {
  const char *exchange_c_str = nullptr;
  std::string exchange_string;
  if (is_null_terminated_view(exchange)) {
    exchange_c_str = exchange.data();
  } else {
    exchange_string = std::move(std::string(exchange));
    exchange_c_str = exchange_string.c_str();
  }
  std::vector<const char *> symbols_c_str = convert_symbols(symbols);
  crawl_ffi_func(exchange_c_str, market_type, symbols_c_str.data(),
                 symbols_c_str.size(), on_msg, duration);
}

void crawl_trade(std::string_view exchange, MarketType market_type,
                 const std::vector<std::string> &symbols,
                 void (*on_msg)(const Message *), uint64_t duration) {
  crawl_template(exchange, market_type, symbols, on_msg, duration, crawl_trade);
}

void crawl_l2_event(std::string_view exchange, MarketType market_type,
                    const std::vector<std::string> &symbols,
                    void (*on_msg)(const Message *), uint64_t duration) {
  crawl_template(exchange, market_type, symbols, on_msg, duration,
                 crawl_l2_event);
}

void crawl_l3_event(std::string_view exchange, MarketType market_type,
                    const std::vector<std::string> &symbols,
                    void (*on_msg)(const Message *), uint64_t duration) {
  crawl_template(exchange, market_type, symbols, on_msg, duration,
                 crawl_l3_event);
}

void crawl_l2_snapshot(std::string_view exchange, MarketType market_type,
                       const std::vector<std::string> &symbols,
                       void (*on_msg)(const Message *), uint64_t duration) {
  crawl_template(exchange, market_type, symbols, on_msg, duration,
                 crawl_l2_snapshot);
}

void crawl_bbo(std::string_view exchange, MarketType market_type,
               const std::vector<std::string> &symbols,
               void (*on_msg)(const Message *), uint64_t duration) {
  crawl_template(exchange, market_type, symbols, on_msg, duration, crawl_bbo);
}

void crawl_l2_topk(std::string_view exchange, MarketType market_type,
                   const std::vector<std::string> &symbols,
                   void (*on_msg)(const Message *), uint64_t duration) {
  crawl_template(exchange, market_type, symbols, on_msg, duration,
                 crawl_l2_topk);
}

void crawl_l3_snapshot(std::string_view exchange, MarketType market_type,
                       const std::vector<std::string> &symbols,
                       void (*on_msg)(const Message *), uint64_t duration) {
  crawl_template(exchange, market_type, symbols, on_msg, duration,
                 crawl_l3_snapshot);
}

void crawl_ticker(std::string_view exchange, MarketType market_type,
                  const std::vector<std::string> &symbols,
                  void (*on_msg)(const Message *), uint64_t duration) {
  crawl_template(exchange, market_type, symbols, on_msg, duration,
                 crawl_ticker);
}

void crawl_funding_rate(std::string_view exchange, MarketType market_type,
                        const std::vector<std::string> &symbols,
                        void (*on_msg)(const Message *), uint64_t duration) {
  crawl_template(exchange, market_type, symbols, on_msg, duration,
                 crawl_funding_rate);
}

void crawl_candlestick(
    std::string_view exchange, MarketType market_type,
    const std::vector<std::pair<std::string, int>> &symbol_interval_list,
    void (*on_msg)(const Message *), uint64_t duration) {
  const char *exchange_c_str = nullptr;
  std::string exchange_string;
  if (is_null_terminated_view(exchange)) {
    exchange_c_str = exchange.data();
  } else {
    exchange_string = std::move(std::string(exchange));
    exchange_c_str = exchange_string.c_str();
  }

  std::vector<const char *> symbols_c_str;
  std::vector<unsigned int> intervals;
  std::transform(
      symbol_interval_list.begin(), symbol_interval_list.end(),
      std::back_inserter(symbols_c_str),
      [](const std::pair<std::string, int> &symbol_interval) -> const char * {
        return symbol_interval.first.c_str();
      });
  std::transform(
      symbol_interval_list.begin(), symbol_interval_list.end(),
      std::back_inserter(intervals),
      [](const std::pair<std::string, int> &symbol_interval) -> unsigned int {
        return static_cast<unsigned int>(symbol_interval.second);
      });
  crawl_candlestick(exchange_c_str, market_type, symbols_c_str.data(),
                    intervals.data(), symbols_c_str.size(), on_msg, duration);
}

void crawl_open_interest(std::string_view exchange, MarketType market_type,
                         void (*on_msg)(const Message *), uint64_t duration) {
  const char *exchange_c_str = nullptr;
  std::string exchange_string;
  if (is_null_terminated_view(exchange)) {
    exchange_c_str = exchange.data();
  } else {
    exchange_string = std::move(std::string(exchange));
    exchange_c_str = exchange_string.c_str();
  }

  crawl_open_interest(exchange_c_str, market_type, on_msg, duration);
}

void subscribe_symbol(std::string_view exchange, MarketType market_type,
                      std::string_view symbol,
                      const std::vector<MessageType> &msg_types,
                      void (*on_msg)(const char *), uint64_t duration) {
  const char *exchange_c_str = nullptr;
  std::string exchange_string;
  if (is_null_terminated_view(exchange)) {
    exchange_c_str = exchange.data();
  } else {
    exchange_string = std::move(std::string(exchange));
    exchange_c_str = exchange_string.c_str();
  }

  const char *symbol_c_str = nullptr;
  std::string symbol_string;
  if (is_null_terminated_view(exchange)) {
    symbol_c_str = exchange.data();
  } else {
    symbol_string = std::move(std::string(exchange));
    symbol_c_str = symbol_string.c_str();
  }

  subscribe_symbol(exchange_c_str, market_type, symbol_c_str, msg_types.data(),
                   msg_types.size(), on_msg, duration);
}
