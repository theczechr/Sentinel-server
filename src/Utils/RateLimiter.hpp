#pragma once
#include <chrono>
#include <deque>
#include <string>
#include <unordered_map>

namespace sentinel {
namespace utils {

    class RateLimiter {
      public:
        // allow up to max_events within window_seconds for each key
        RateLimiter(unsigned int max_events, unsigned int window_seconds)
            : max_events_(max_events), window_(window_seconds) {}

        bool allow(const std::string &key) {
            const auto now = std::chrono::system_clock::now();
            auto &dq = buckets_[key];
            // drop old
            while (!dq.empty() && std::chrono::duration_cast<std::chrono::seconds>(now - dq.front()).count() > static_cast<long long>(window_)) {
                dq.pop_front();
            }
            if (dq.size() >= max_events_) {
                return false;
            }
            dq.push_back(now);
            return true;
        }

      private:
        unsigned int max_events_;
        unsigned int window_;
        std::unordered_map<std::string, std::deque<std::chrono::system_clock::time_point>> buckets_;
    };

} // namespace utils
} // namespace sentinel


