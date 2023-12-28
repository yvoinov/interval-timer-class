#include <cstdlib>	/* For std::size_t */
#include <chrono>
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <functional>	/* For std::function */

/* Timer class with on-load init. Intended to run a given block (lambda) on a periodic basis at a given interval */

template <typename T, typename F>
class Timer {
public:
	Timer(T p_interval, F p_exec) : m_interval(p_interval), m_exec(p_exec) {
		std::thread([=]() { while (m_running.load(std::memory_order_relaxed)) {
					std::unique_lock<std::mutex> tlock(m_conditional_mutex);
					if (!m_conditional_lock.wait_for(tlock, std::chrono::seconds(m_interval),
						[this]() { return !m_running.load(std::memory_order_acquire); }))
						m_exec();
				}
		}).detach();
	}
	~Timer() { m_running.store(false, std::memory_order_release); m_conditional_lock.notify_one(); }
private:
	T m_interval;
	F m_exec;
	std::atomic<bool> m_running { true };
	std::condition_variable m_conditional_lock;
	std::mutex m_conditional_mutex;
};
