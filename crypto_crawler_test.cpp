#include "crypto_crawler.h"

#include <gtest/gtest.h>

std::vector<Message> messages;

void on_msg(const Message* msg) { messages.push_back(*msg); }

// NOLINTNEXTLINE
TEST(CryptoCrawlerTest, Trade) {
  messages.clear();
  std::vector<std::string> symbols{"BTCUSDT", "ETHUSDT"};
  crawl_trade(std::string_view("binance"), MarketType::LinearSwap, symbols,
              on_msg, 5);
  ASSERT_FALSE(messages.empty());
}

TEST(CryptoCrawlerTest, L2Event) {
  messages.clear();
  std::vector<std::string> symbols{"BTCUSDT", "ETHUSDT"};
  crawl_l2_event(std::string_view("binance"), MarketType::LinearSwap, symbols,
                 on_msg, 5);
  ASSERT_FALSE(messages.empty());
}
