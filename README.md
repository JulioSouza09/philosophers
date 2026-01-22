*This project has been created as part of the 42 curriculum by juliosouza09.*

# Philosophers

## Description

**Philosophers** is a concurrent programming project written in **C**, based on the classic **Dining Philosophers Problem**.

The objective is to simulate philosophers sitting at a round table who alternate between **thinking**, **eating**, and **sleeping**, while competing for limited shared resources (forks). Each philosopher must eat without starving, and the simulation must respect strict timing constraints.

This project focuses on:
- **Multithreading with POSIX threads**
- **Mutex-based synchronization**
- **Race-condition prevention**
- **Precise timing and logging guarantees**

It demonstrates the ability to design **safe, deterministic concurrent systems** under real-world constraints.

---

## Rules & Constraints

- Each philosopher is represented by a **separate thread**
- Forks are shared resources protected by **mutexes**
- **Global variables are strictly forbidden**
- No data races are allowed
- Death detection must be reported within **10 ms**
- Philosophers do not communicate directly
- Simulation stops when:
  - A philosopher dies, or
  - All philosophers have eaten the required number of times (if specified)

---

## Program Arguments

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]
````

### Argument Description

* **number_of_philosophers**: Total philosophers and forks
* **time_to_die (ms)**: Time without eating before starvation
* **time_to_eat (ms)**: Duration of eating (holding two forks)
* **time_to_sleep (ms)**: Duration of sleeping
* **number_of_times_each_philosopher_must_eat** (optional): Stops simulation when all philosophers reach this count

---

## Logging Format

Each state change is logged as:

```text
timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died
```

Where:

* `timestamp_in_ms` is relative to simulation start
* `X` is the philosopher number (1 to N)

Logs are **mutex-protected** to prevent overlapping messages.

---

## Implementation Details

### Concurrency Model

* **One thread per philosopher**
* **One mutex per fork**
* Additional mutexes used for:

  * Printing/logging
  * Death detection
  * Shared state protection

### Fork Management

* Forks are placed between philosophers
* A philosopher must lock **both left and right fork mutexes** before eating
* Fork acquisition order is carefully managed to **avoid deadlocks**

### Time Management

* Timing is handled using `gettimeofday` with millisecond precision
* Active waiting is avoided; `usleep` is used responsibly
* Death checks are continuous and precise

---

## Instructions

### Compilation

```bash
make
```

### Run

```bash
./philo 5 800 200 200
```

Example with meal limit:

```bash
./philo 5 800 200 200 7
```

### Clean build files

```bash
make clean
make fclean
```

### Recompile

```bash
make re
```

---

## What This Project Demonstrates

* Strong understanding of **multithreading**
* Correct use of **mutexes** to protect shared resources
* Deadlock and starvation avoidance strategies
* Accurate **real-time constraints handling**
* Clean and maintainable C design without global state

These skills are directly applicable to **backend**, **systems**, and **infrastructure engineering** roles.

---

## Resources

### Technical References

* The Dining Philosophers Problem — E. W. Dijkstra
* POSIX Threads Programming
* Linux `man` pages:

  * `pthread_create`
  * `pthread_mutex_lock`
  * `pthread_join`
  * `gettimeofday`
* Operating Systems: Three Easy Pieces

### AI Usage Disclosure

AI tools were used **exclusively as a learning aid**, for:

* Clarifying concurrency concepts
* Understanding mutex usage patterns
* Reviewing documentation and edge cases

All **design decisions, synchronization logic, debugging, and final code** were implemented manually.

---

## Notes

* The implementation strictly follows the project specification
* No undefined behavior or race conditions are tolerated
* When behavior was ambiguous, correctness and safety were prioritized

---

## Author

**Júlio César**
42 Porto — Software Development
- GitHub: [https://github.com/juliosouza09](https://github.com/juliosouza09)
- LinkedIn: [https://linkedin.com/in/juliosouzadev](https://linkedin.com/in/juliosouzadev)
