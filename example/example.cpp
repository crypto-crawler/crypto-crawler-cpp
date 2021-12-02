#include <iostream>

#include "crypto_crawler.h"

void on_msg(const Message *msg) {
  std::cout << msg->exchange << ", " << msg->json << std::endl;
}

int main() {
  MessageType msg_types[2] = {MessageType::Trade, MessageType::L2Event};
  std::vector<std::string> symbols{"BTCUSDT", "ETHUSDT"};
  crawl_trade(std::string_view("binance"), MarketType::LinearSwap, symbols,
              on_msg);
}
