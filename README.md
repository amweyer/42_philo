# philosophers ✅ 100/100

> A C simulation of the Dining Philosophers problem — concurrency, mutexes, and precise timing.

---

## What it does

`philo` simulates N philosophers sitting at a round table, each alternating between eating, thinking, and sleeping. Each philosopher needs two forks to eat, with exactly one fork between each pair — making shared resource management critical.

The simulation stops when a philosopher dies of starvation, or when all have eaten the required number of times.

```bash
./philo 5 800 200 200
# 5 philosophers, die after 800ms without eating,
# eat for 200ms, sleep for 200ms

./philo 5 800 200 200 7
# stops once every philosopher has eaten 7 times
```

## Arguments

| Argument | Description |
|----------|-------------|
| `number_of_philosophers` | Number of philosophers (and forks) |
| `time_to_die` (ms) | Time before a philosopher starves |
| `time_to_eat` (ms) | Duration of a meal (holds 2 forks) |
| `time_to_sleep` (ms) | Duration of sleep |
| `[must_eat_count]` | Optional: stop when all have eaten N times |

## How it works

Each philosopher runs as a **separate POSIX thread** (`pthread_create`). Each fork is a **mutex** (`pthread_mutex_t`) — a philosopher must acquire both adjacent mutexes before eating, then release them.

A dedicated **monitor thread** polls every millisecond whether any philosopher has exceeded `time_to_die` since their last meal, using `gettimeofday` for sub-millisecond precision.

**Concurrency challenges — directly relevant to embedded/RTOS contexts:**

- **Deadlock prevention**: philosophers acquire forks in a consistent order (odd/even strategy) to break circular wait
- **Data race elimination**: all shared state (last meal timestamp, meal count, simulation stop flag) protected by dedicated mutexes — verified with Helgrind/ThreadSanitizer
- **Hard real-time constraint**: death detection and logging within 10ms, achieved without busy-waiting

This mirrors patterns common in embedded systems: shared peripheral access, critical sections, and deterministic timing requirements.

## Compilation

```bash
make
make clean
make fclean
make re
```

## What I learned

- **POSIX threads**: `pthread_create`, `pthread_join`, `pthread_detach` lifecycle management
- **Mutex design**: granularity tradeoffs, lock ordering to prevent deadlocks
- **Precise timing in C**: `gettimeofday` + `usleep` for millisecond-level scheduling — analogous to hardware timer management in embedded C
- **Race condition detection**: practical use of Helgrind

## Resources

- [Dining Philosophers Problem — Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [pthread_mutex — Linux man page](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html)
- [gettimeofday — Linux man page](https://man7.org/linux/man-pages/man2/gettimeofday.2.html)
- [Helgrind — Valgrind thread error detector](https://valgrind.org/docs/manual/hg-manual.html)
