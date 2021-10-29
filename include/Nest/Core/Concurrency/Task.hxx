#ifndef NEST_CORE_CONCURRENCY_TASK_HXX
#define NEST_CORE_CONCURRENCY_TASK_HXX

#include <Nest/Core/Utility/CommonTypes.hxx>
#include <Nest/Core/Utility/Optional.hxx>
#include <chrono>

namespace Nest::Core {

class Task
{
public:
	enum class Priority
	{
		Low,
		Medium,
		High,
		Crucial,
	};

private:
	struct TaskInfo
	{
		using Clock = std::chrono::utc_clock;
		using TimePoint = std::chrono::time_point<Clock>;
		using TimeIn = std::chrono::microseconds;
		using Duration = std::chrono::duration<TimeIn>;
		using PriorityHeuristicValue = u64;

		explicit TaskInfo(Priority priority) : priority(priority) {}

	private:
		static Priority map_distance_to_priority(Duration d) noexcept {
			constexpr auto crucial = std::chrono::microseconds(10);
			constexpr auto high = std::chrono::microseconds(500);
			constexpr auto medium = std::chrono::milliseconds(10);

			if (d <= crucial) return Priority::Crucial;
			if (d <= high) return Priority::High;
			if (d <= medium) return Priority::Medium;
			return Priority::Low;
		}

		[[nodiscard]] Duration calculate_distance() const noexcept {
			if (scheduled_to_run.has_value()) {
				// Calculate the distance between scheduled runs
				const auto& scheduled_time = scheduled_to_run.value();
				return std::chrono::duration_cast<TimeIn>(scheduled_time - last_run);
			} else {
				// Calculate the distance between the last run and the current time
				return std::chrono::duration_cast<TimeIn>(Clock::now() - last_run);
			}
		}

	public:
		[[nodiscard]] PriorityHeuristicValue calculate_priority() const noexcept {
			const auto distance = this->calculate_distance();
			const auto distance_priority = TaskInfo::map_distance_to_priority(distance);

			const auto distance_priority_heuristic_value = static_cast<PriorityHeuristicValue>(distance_priority);
			const auto priority_heuristic_value = static_cast<PriorityHeuristicValue>(priority);

			const auto final_heuristic_value = (distance_priority_heuristic_value + priority_heuristic_value) / 2;

			return final_heuristic_value;
		}

		TimePoint last_run;
		Optional<TimePoint> scheduled_to_run;
		Priority priority;
	};

private:
	TaskInfo info_;

public:
	[[nodiscard]] TaskInfo::PriorityHeuristicValue priority() const noexcept {
		return info_.calculate_priority();
	}
};

}	 // namespace Nest::Core

#endif	  // NEST_CORE_CONCURRENCY_TASK_HXX