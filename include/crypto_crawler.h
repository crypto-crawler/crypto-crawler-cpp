#ifndef CRYPTO_CRAWLER_H_
#define CRYPTO_CRAWLER_H_

#include <string>
#include <string_view>
#include <vector>

#include "crypto_crawler_ffi.h"

/**
 * Crawl realtime trades.
 *
 * ## Arguments
 *
 * - `exchange` The exchange name, can not be null
 * - `market_type` The market type
 * - `symbols` Symbols to crawl
 * - `on_msg` The callback function to process messages
 * - `duration` How many seconds to run, only useful in testing, 0 means run
 * forever
 */
void crawl_trade(std::string_view exchange, MarketType market_type,
                 const std::vector<std::string> &symbols,
                 void (*on_msg)(const Message *), uint64_t duration = 0);

/**
 * Crawl level2 orderbook update events.
 */
void crawl_l2_event(std::string_view exchange, MarketType market_type,
                    const std::vector<std::string> &symbols,
                    void (*on_msg)(const Message *), uint64_t duration = 0);

/**
 * Crawl level3 orderbook update events.
 */
void crawl_l3_event(std::string_view exchange, MarketType market_type,
                    const std::vector<std::string> &symbols,
                    void (*on_msg)(const Message *), uint64_t duration = 0);

/**
 * Crawl level2 orderbook snapshots through RESTful APIs.
 */
void crawl_l2_snapshot(std::string_view exchange, MarketType market_type,
                       const std::vector<std::string> &symbols,
                       void (*on_msg)(const Message *), uint64_t duration = 0);

/**
 * Crawl best bid and ask.
 */
void crawl_bbo(std::string_view exchange, MarketType market_type,
               const std::vector<std::string> &symbols,
               void (*on_msg)(const Message *), uint64_t duration = 0);

/**
 * Crawl level2 orderbook top-k snapshots through websocket.
 */
void crawl_l2_topk(std::string_view exchange, MarketType market_type,
                   const std::vector<std::string> &symbols,
                   void (*on_msg)(const Message *), uint64_t duration = 0);

/**
 * Crawl level3 orderbook snapshots through RESTful APIs.
 */
void crawl_l3_snapshot(std::string_view exchange, MarketType market_type,
                       const std::vector<std::string> &symbols,
                       void (*on_msg)(const Message *), uint64_t duration = 0);

/**
 * Crawl 24hr rolling window ticker.
 *
 * If `symbols` is None, it means all trading symbols in the `market_type`,
 * and updates the latest symbols every hour.
 */
void crawl_ticker(std::string_view exchange, MarketType market_type,
                  const std::vector<std::string> &symbols,
                  void (*on_msg)(const Message *), uint64_t duration = 0);

/**
 * Crawl perpetual swap funding rates.
 */
void crawl_funding_rate(std::string_view exchange, MarketType market_type,
                        const std::vector<std::string> &symbols,
                        void (*on_msg)(const Message *), uint64_t duration = 0);

/**
 * Crawl candlestick(i.e., OHLCV) data.
 *
 * If `symbol_interval_list` is None or empty, this API will crawl candlesticks
 * from 10 seconds to 3 minutes(if available) for all symbols.
 */
void crawl_candlestick(
    std::string_view exchange, MarketType market_type,
    const std::vector<std::pair<std::string, int>> &symbol_interval_list,
    void (*on_msg)(const Message *), uint64_t duration = 0);

/**
 * Crawl all open interest.
 */
void crawl_open_interest(std::string_view exchange, MarketType market_type,
                         void (*on_msg)(const Message *),
                         uint64_t duration = 0);

/**
 * Subscribe to multiple message types of one symbol.
 *
 * This API is suitable for client applications such as APP, website, etc.
 *
 * String messages in `tx` are already parsed by `crypto-msg-parser`.
 */
void subscribe_symbol(std::string_view exchange, MarketType market_type,
                      std::string_view symbol,
                      const std::vector<MessageType> &msg_types,
                      void (*on_msg)(const char *), uint64_t duration = 0);

#endif /* CRYPTO_CRAWLER_H_ */
