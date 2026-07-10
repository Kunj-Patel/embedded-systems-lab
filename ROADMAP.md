# Embedded Systems 28-Week Roadmap

This document is the single source of truth for this repository's engineering journey. It supersedes all earlier drafts.

**How to use this with an agent:** this file has the mission, rules, architecture, and full 28-week phase overview. The week-by-week deliverables and Friday interview prompts for whichever phase is currently active live in a linked file under [phases/](phases/) (see the table in [28-Week Phase Breakdown](#28-week-phase-breakdown)) — point an agent at the current phase file plus this one for full context on where things stand and what's next. **For exact session start/end prompts, see [AGENT-GUIDE.md](AGENT-GUIDE.md)** — it's the operating manual for this file; read it once and reuse its prompts every session.

---

## Pacing & Calendar

"Week N" in this document is a unit of content, not a guaranteed Mon-Sun calendar week. This section exists because the real calendar this roadmap runs against isn't uniform — an internship ending August 21, 2026, then a 2-course grad semester starting September — and pretending otherwise is how plans like this quietly die at the first exam week.

**Internship window (now through ~Aug 21, 2026):** front-load [Phase 0](phases/phase-0-raw-c.md) and [Phase 1](phases/phase-1-modern-cpp.md) (Weeks 1-7) here — pure-software weeks with no Nucleo dependency, well suited to unbroken daily momentum. 7 weeks of content in ~6 calendar weeks is realistic; order the Nucleo now so it's in hand before Phase 2.

**Semester window (Sept 2026 onward, 2 grad courses):** 15-25 hrs/week is at or above this roadmap's implicit pace, so the semester isn't automatically slower — the real risk is variance, not average: exam weeks crush bootcamp time to near zero even in a semester that averages out fine.

- **Normal weeks:** run the roadmap as written, one phase-file week per ~1 calendar week.
- **Exam/high-load weeks:** don't compress a full week's deliverables into a bad week. Pause the bootcamp for that week and resume exactly where you left off, or let a genuinely light week's deliverable stretch across two calendar weeks. Never silently drop a deliverable to stay "on schedule."
- **Log every exam-week pause in the Sunday retro (Rule 4)** — one line ("paused for midterms, resuming Week N") is enough.

**Net effect:** the 28 weeks of content stay exactly as designed — the calendar stretches to fit real life, likely landing around 8-10 calendar months end-to-end rather than a strict 6.5. That's a normal outcome for a self-taught program running alongside a job and a degree, not a sign the plan failed.

## Mission

Transform from an engineer who can implement embedded software components into an engineer who can design complete embedded systems — someone who can reason across the full stack:

```
Requirements → Constraints → Hardware → Architecture → Drivers →
Firmware → Real-Time Behavior → Performance → Reliability →
Testing → Manufacturing → Maintenance
```

The gap being closed is not raw technical ability. It's engineering maturity — moving from "I know how to implement this feature" to "I understand why this architecture exists, what constraints shaped it, and how to validate that it is correct."

---

## The Four Loops

Everything in this bootcamp happens in four loops simultaneously:

```
                Learn
                  ▲
                  │
Build ◄──────────────► Explain
                  │
                  ▼
             Refactor
```

Every concept must survive all four loops:

- If you can't **explain** it, you don't know it.
- If you can't **build** it, you don't know it.
- If you can't **improve** it, you don't know it.

---

## The Seven Rules

**Rule 1 — You write code every day.** Even 30 minutes counts. Consistency beats intensity.

**Rule 2 — Everything goes into Git.** Tiny commits. Meaningful messages. Professional documentation.

**Rule 3 — Every project gets unit tests.** Not because interviews ask for them. Because professionals rely on them.

**Rule 4 — Every week ends with a retrospective.** What did I learn? What confused me? What would I do differently? What questions remain?

**Rule 5 — Nothing is "magic."** For every library, feature, or protocol: Why does it exist? What problem does it solve? What alternatives exist? What are the trade-offs? How is it likely implemented?

**Rule 6 — Prefer understanding over memorization.** If you forget syntax, documentation exists. If you don't understand concepts, documentation won't save you.

**Rule 7 — We're building a portfolio, not a collection of tutorials.** Every project should survive 20 minutes of interview discussion. If not, it isn't finished.

---

## Algorithm Interview Prep

Every embedded loop at the companies this roadmap targets (Etched, Nvidia, Qualcomm, Intel, ARM, AMD, Google, Apple) still includes 1-3 general DSA rounds alongside the embedded-specific ones — this track exists so that's never the reason an offer is lost. 30-45 min/day, tracked in `algorithms/leetcode/` (one file per problem, approach + complexity noted), with a running count kept in `algorithms/leetcode/README.md`.

**Target: ~120-150 problems by Week 28**, distributed across the pattern focus already assigned per phase (see each phase file's Algorithms section) plus a standing rotation of: two-pointers, sliding window, binary search, heap/priority queue, backtracking, and graph algorithms beyond DFS/BFS (Dijkstra, topological sort, union-find) — these six patterns recur across the phase-assigned focuses and should be kept warm continuously, not treated as one-time topics. Weight toward medium difficulty; a small number of hards by Week 20+ once the easy/medium patterns are automatic.

Checkpoint every 4 weeks (aligned with phase boundaries) in the Sunday retro: total solved, patterns still shaky, whether the daily 30-45 min is actually happening. If it's slipping, say so in the retro rather than letting it silently lapse — this is Rule 4 applied to this track specifically.

---

## Mock Interview Discipline

Every phase file has Friday architecture prompts and periodic full mock interviews. This section is the format all of them run under — without it, "practice" quietly turns into "think about it comfortably," which doesn't build the reflex a real loop demands. This applies retroactively to every Friday prompt in every phase file, not just the ones tagged "full mock interview."

- **Clock it.** Single-topic Friday prompts get 5-7 minutes, spoken out loud, not typed calmly. Full mock-interview weeks get 30-45 minutes, matching real onsite/virtual-onsite round length.
- **Say it, don't write it, by default.** Typing an answer at your own pace tests something closer to essay-writing than interviewing. Speak the answer out loud (recording yourself on your phone is enough) unless a prompt explicitly says "in writing." If your explanation only holds together on the fourth rewrite, it doesn't hold together yet.
- **Force one adversarial follow-up.** After answering, generate (or have the agent generate) one pushback question a skeptical interviewer would actually ask — "why not X instead," a changed constraint ("now assume the battery is at 5%," "now assume the bus is shared with two other devices"), or "what's the failure mode of your own answer." Answer that too, on the clock. A prompt that survives only the first pass isn't validated.
- **Log it in the Sunday retro**, per Rule 4: what fell apart under the follow-up, what you'd tighten. This is where the weekly prompts actually compound instead of just repeating.
- **Live-coding reps, not just verbal design:** roughly every 3-4 weeks (a natural Saturday add-on, see each phase's deliverables), pick one small piece of that week's real code — a ring buffer op, a mutex-guarded critical section, an ISR, a state-machine transition — and implement it cold, on a whiteboard/blank editor with no reference to your existing solution, in 15-20 minutes. This is the round type ("write this function live") the verbal prompts don't cover, and it's a standard part of embedded loops at this tier.
- **Behavioral reps, not just the Week 28 bug story:** once per phase (Sunday retro is a natural slot), turn that week's hardest real problem into a 2-minute STAR-format story (Situation, Task, Action, Result) and say it out loud once. By Week 28 this produces 6-7 rehearsed stories to draw from, not one written retroactively under deadline pressure.

---

## Background / Starting Baseline

- **Professional background:** mechatronics engineering, 2 years as a firmware developer writing C for STM32 MCUs, built with Make — real, relevant experience, which is why Phase 0 is a fast validation gate rather than a teaching phase.
- **Academic background:** currently pursuing a Master's in Computer Engineering; coursework completed in computer architecture, machine learning, and FPGA design. Where later theory overlaps this coursework (cache/memory hierarchy in Phase 5, scheduling theory in Phase 3), the roadmap keeps full coverage — it reinforces via a hands-on/embedded lens the coursework didn't use.
- **Environment:** Apple M1 Pro, VSCode, CMake, Ninja, clang++/LLVM, ld64, clang-tidy, clang-format — a different toolchain from the Make-based one used professionally, so the switch itself is a real (if secondary) learning item in Phase 1.
- **Hardware target:** STM32 Nucleo-F401RE / F411RE / F446RE (Cortex-M4F) — see [phases/phase-2-embedded-fundamentals.md](phases/phase-2-embedded-fundamentals.md) for exact model confirmation before Week 8. Different from whichever STM32 part is used professionally, but the same family — bring-up mechanics should feel familiar; the HAL/mock-backend architecture and the RTOS/architecture work built on top of it will not.
- **Modern C++:** the real gap. Self-rated 2-4/10 across references, RAII, constructors/destructors, move semantics, templates, constexpr, smart pointers, STL algorithms, `std::optional`/`variant`/`span`, lambdas — this is what two years of embedded C doesn't cover, and where Phase 1's reclaimed extra week (Week 2) is spent.
- **Toolchain experience:** professionally used Make for STM32 builds; new to CMake, Ninja, GoogleTest, clang-format, clang-tidy, and Doxygen specifically — all taught explicitly from first use starting Phase 1, nothing assumed.
- **Repository:** `github.com/Kunj-Patel/embedded-systems-lab` (already initialized, README and `.gitignore` in place).

---

## Repository Structure

Directories are created only when they contain meaningful work — no empty scaffolding ahead of need.

```
embedded-systems-lab/
├── README.md
├── ROADMAP.md
│
├── notes/                 # Why does this exist? What problem does it solve? Trade-offs?
│   ├── modern-cpp/
│   ├── computer-science/
│   ├── embedded/
│   ├── architecture/
│   ├── reliability/
│   └── retros/              # Weekly Rule 4 retros — see AGENT-GUIDE.md for exact naming/template
│
├── experiments/           # Small, falsifiable investigations: hypothesis → implementation → measurement → conclusion
│   ├── cpp/
│   ├── memory/
│   ├── concurrency/
│   └── performance/
│
├── hal/                    # The shared Firmware Simulator: interfaces + two backends (see below)
│   ├── include/             # Gpio, Led, Button, Uart, Spi, I2c, Timer, ...
│   ├── mock/                 # Host backend — runs on the Mac, used in unit tests
│   └── stm32/                 # Real backend — register-level STM32 implementation
│
├── projects/               # Complete engineering artifacts, portfolio-grade
│   ├── sensor-core/         # Phase 1 onward: hardware-agnostic application library — never renamed, never abandoned
│   │   ├── include/           # StateMachine, Sensor, RingBuffer<T,N>, threshold/alerting policy, Config
│   │   ├── src/
│   │   └── tests/              # GoogleTest against hal/mock/ only — no RTOS, no board, ever
│   │
│   └── sensor-hub/          # Phase 3 onward: the deployable product — links sensor-core + hal/ + FreeRTOS
│       ├── tasks/              # Sensor/Logger/CLI/Watchdog tasks, each a thin wrapper composing sensor-core
│       ├── drivers/kernel/middleware/application/   # Phase 4's formalized layering, applied here
│       └── README.md            # the Rule 7 project README, maintained continuously from Phase 3 onward
│
└── algorithms/             # Daily interview-prep practice
    └── leetcode/
```

**One project, not five — and a real library/consumer split, not a rename.** `sensor-core/` is what Phase 1 actually builds: a hardware-agnostic application library (state machine, `Sensor`, `RingBuffer`, threshold/alerting), designed via dependency injection specifically so it has no concept of tasks, queues, or an RTOS. It never gets renamed or abandoned — it's linked against for the rest of the roadmap. `sensor-hub/` doesn't exist until Phase 3, when there's finally something to wrap `sensor-core/` in: it links `sensor-core/` plus `hal/` plus FreeRTOS, and every later phase hardens it in place (watchdog and fault handling in Phase 3, layered architecture in Phase 4, DMA logging and a bootloader in Phase 5, OTA/power/config/CI in Phase 6) rather than being replaced by a new named project each phase. At final release (Phase 6), `sensor-hub/` can be git-tagged as the "Industrial Sensor Platform" — that's a release tag, not a third directory name. See [28-Week Phase Breakdown](#28-week-phase-breakdown) for exactly what's added where.

---

## The HAL / Firmware Simulator Architecture

This is the one structural idea that ties the whole roadmap together, and it starts life as the "Firmware Simulator" — deceptively simple GPIO/LED/Button interfaces built in Phase 1.

The core design: **one interface, two backends.**

```
                 Gpio / Uart / Spi / I2c / Timer ...
                              (hal/include/)
                    ▲                          ▲
                    │                          │
              mock backend               stm32 backend
           (hal/mock/, runs on Mac)   (hal/stm32/, runs on Nucleo)
                    │                          │
                    └──────────┬───────────────┘
                               │
                sensor-core/ and sensor-hub/ consume
                     the interface, never the backend
```

Every peripheral driver is designed against an interface first. The mock backend lets application logic (state machines, services, business rules) be built and unit-tested entirely on the Mac, at full speed, with GoogleTest — no board required for daily work. The STM32 backend implements the same interface at the register level and is verified against real hardware during dedicated Nucleo sessions.

Swapping from simulation to real hardware is a link-time backend swap, not a rewrite — this is what makes Rule 3 (unit tests for everything) practical for embedded work.

The interface set grows over the roadmap: GPIO/LED/Button (Phase 1) → Timer/UART/SPI/I2C/ADC/Interrupts (Phase 2) → Scheduler primitives (Phase 3) → formalized HAL/BSP layering (Phase 4) → DMA (Phase 5).

---

## 28-Week Phase Breakdown

Each phase below has a full weekly deliverables breakdown in its own file — link to the specific phase file when asking an agent for help on current work, so it has the exact week's context without loading all 28 weeks.

| Phase | Weeks | File |
|---|---|---|
| 0 — C Fluency Validation Gate | 1 | [phases/phase-0-raw-c.md](phases/phase-0-raw-c.md) |
| 1 — Modern C++ & OOD | 2-7 | [phases/phase-1-modern-cpp.md](phases/phase-1-modern-cpp.md) |
| 2 — Embedded Fundamentals + Nucleo | 8-12 | [phases/phase-2-embedded-fundamentals.md](phases/phase-2-embedded-fundamentals.md) |
| 3 — RTOS Ground-Up | 13-17 | [phases/phase-3-rtos.md](phases/phase-3-rtos.md) |
| 4 — System Architecture | 18-20 | [phases/phase-4-architecture.md](phases/phase-4-architecture.md) |
| 5 — Performance Engineering | 21-24 | [phases/phase-5-performance.md](phases/phase-5-performance.md) |
| 6 — Capstone | 25-28 | [phases/phase-6-capstone.md](phases/phase-6-capstone.md) |

### Phase 0 — C Fluency Validation Gate (Week 1)

*Weekly breakdown: [phases/phase-0-raw-c.md](phases/phase-0-raw-c.md)*

**Goal:** Confirm — quickly, not by re-teaching — that bit manipulation, pointer arithmetic, and memory-layout reasoning are already automatic, since two years of professional STM32 C firmware work almost certainly covers this. A checkpoint, not a curriculum.

- Timed, no-reference self-check: bitfields, pointer arithmetic, buffer casting, memory-segment identification.
- **Experiment (kept regardless of fluency):** implement and benchmark a custom `memcpy`/`memset` — the benchmarking/writeup discipline is the point, not the C itself.
- If the self-check reveals a real gap, close it before moving on; if not (expected), move into Phase 1 by Wednesday or Thursday.
- **Algorithms begin here:** 30-45 min/day in `algorithms/leetcode/`, starting with arrays and strings.

### Phase 1 — Modern C++ & Object-Oriented Design (Weeks 2-7)

*Weekly breakdown: [phases/phase-1-modern-cpp.md](phases/phase-1-modern-cpp.md)*

**Goal:** Transition from procedural C to modern C++, thinking in value semantics, RAII, and composition before reaching for raw arrays or inheritance. The week reclaimed from Phase 0's compression goes here first, on the two topics the professional C background doesn't already cover: smart pointers and STL algorithms.

Topics:
- Smart pointers (`unique_ptr`/`shared_ptr`) and STL `<algorithm>` idioms, translated directly from C ownership/loop habits — including when embedded's no-heap-after-init constraint means neither applies.
- References, pointers, `const` correctness, `enum class`, `constexpr`, lambdas, classes/structs.
- Object lifetime: constructors, destructors, copy semantics, move semantics.
- RAII, ownership models, deterministic cleanup, exception safety.
- Modern library: `std::array`, `std::vector`, `std::span`, `std::string_view`, `std::optional`, `std::variant`, `std::chrono`.
- Templates and basic generic programming.
- Software design: SOLID, composition over inheritance, interfaces, dependency injection.

**`hal/` begins here:** design `Gpio`, `Led`, `Button`, `Sensor` and their mock backend — this is the original "Firmware Simulator" scope, unit-tested with GoogleTest.

**Project:** `sensor-core` (`projects/sensor-core/`) — a hardware-agnostic application library, PC-only, pure software: state machine, mock `Sensor` ingestion, threshold/alerting, DI, no hardware registers, no RTOS. The permanent core library every later phase links against (see [Repository Structure](#repository-structure)).

**Algorithms:** linked lists, stacks, queues.

### Phase 2 — Embedded Fundamentals + Nucleo Bring-Up (Weeks 8-12)

*Weekly breakdown: [phases/phase-2-embedded-fundamentals.md](phases/phase-2-embedded-fundamentals.md)*

**Goal:** Demystify hardware interfaces. The Nucleo enters here — every peripheral is built as an interface with a mock backend *and* a real STM32 backend, learned side by side rather than sequentially.

For each peripheral, ask: why does it exist, what problem does it solve, what are the trade-offs, what can fail?

- **GPIO & Timers:** bare-metal blinky via super-loop, then hardware timers (PWM, capture/compare, overflow) replacing blocking delays.
- **UART:** polling driver → interrupt-driven with ring buffer. Baud rate, framing, flow control, error recovery.
- **SPI:** master implementation, chip-select handling, interrupt-driven transfer.
- **I2C:** addressing, ACK/NACK, repeated start, clock stretching, bus recovery, timeouts. Talk to a real sensor.
- **ADC:** sampling theory, aliasing, noise, filtering, calibration.
- **Interrupts:** latency, priority, nested interrupts, critical sections, memory barriers.
- **Disassembly reading:** read the ARM Thumb-2 disassembly of a compiled function, identify the AAPCS calling convention and stack frame layout in practice.

Toolchain additions: `arm-none-eabi-gcc`, OpenOCD/ST-Link, register-level programming.

**Project:** extend `hal/` with the STM32 backend for every interface above, and plug real sensors (SPI, I2C, ADC) into `sensor-core`'s `Sensor` interface from Phase 1 — the same library now runs on real hardware, verified to behave identically to its mock-backed Phase 1 version. Still `sensor-core/`, still no RTOS — that's Phase 3.

**Algorithms:** trees, basic graph traversal (DFS/BFS).

### Phase 3 — RTOS Ground-Up (Weeks 13-17)

*Weekly breakdown: [phases/phase-3-rtos.md](phases/phase-3-rtos.md)*

**Goal:** Think in systems. Build the mechanics before adopting an off-the-shelf OS.

- Write a timer interrupt that context-switches between two infinite-loop tasks (your own toy scheduler).
- Two tasks sharing one UART console; implement a mutex; deliberately omit it and observe corruption.
- Visualize preemption and priority inversion (Segger SystemView or similar, if available).
- Migrate to **FreeRTOS** on the Nucleo once the ground-up scheduler is understood: scheduling, preemption, priorities, priority inversion, mutexes, semaphores, queues, memory pools.
- Intentionally create deadlocks, race conditions, starvation, and priority inversion — then fix them.
- **Hard-fault deep dive:** write a `HardFault_Handler` reading `CFSR`/`HFSR` and the stacked exception frame; diagnose at least two deliberately-triggered hard faults from register state alone.

**Project:** `sensor-hub` (`projects/sensor-hub/`) is created here — it links `sensor-core` (unchanged) plus `hal/` plus FreeRTOS into per-sensor/Logger/CLI/Watchdog tasks communicating via queues and events (no global variables). Watchdog and fault-handling are introduced here, not deferred to the capstone, because "what happens when a task hangs" is a scheduling-native question.

**Algorithms:** dynamic programming basics, recursion.

### Phase 4 — System Architecture (Weeks 18-20)

*Weekly breakdown: [phases/phase-4-architecture.md](phases/phase-4-architecture.md)*

**Goal:** Transition from firmware developer to systems engineer.

- Formalize `hal/` into a layered architecture: HAL, BSP, driver models, event buses.
- Dependency injection for testability — mock sensors injected into business logic for PC-side unit tests.
- Weekly architecture-interview practice deepens: "design firmware for a battery-powered industrial sensor" — requirements, power budget, MCU choice, memory, communication, RTOS decision, storage, security, OTA, manufacturing test.

**Project:** no new project — this phase refactors `hal/` and `sensor-hub/` in place into explicit `drivers/`, `kernel/`, `middleware/`, `application/` layers, under the existing test suite. `sensor-core/` is untouched (already a clean, standalone library). Real engineering teams harden systems far more than they greenfield them; this is that skill.

### Phase 5 — Performance Engineering (Weeks 21-24)

*Weekly breakdown: [phases/phase-5-performance.md](phases/phase-5-performance.md)*

**Goal:** Measure, analyze, optimize.

- Memory: cache behavior, DMA, zero-copy, memory pools.
- Concurrency: lock-free programming, atomics, memory ordering, false sharing.
- Build: compiler optimization flags, LTO, linker behavior, map files, binary size, boot time.
- Bootloader foundation: linker-script memory layout, image verification, verify-and-jump — introduced here (not Phase 6) because it's a direct extension of this phase's memory/linker material.

**Project:** harden `sensor-hub`'s Logger task — swap its naive UART/SD writes for DMA-driven SPI sensor capture into a circular buffer, written to an SD card, CRC-validated, recoverable after power loss. Measure latency, throughput, memory and CPU usage against the pre-upgrade baseline.

### Phase 6 — Capstone: Industrial Sensor Platform (Weeks 25-28)

*Weekly breakdown: [phases/phase-6-capstone.md](phases/phase-6-capstone.md)*

**Goal:** Ship `sensor-hub` — hardened in Phases 3-5 with watchdog, fault handling, DMA logging, and a bootloader, and linking `sensor-core` since Phase 3 — as a finished Industrial Sensor Platform. This phase introduces no new subsystem from scratch: it adds OTA (extending Phase 5's bootloader), power management, and configuration, then closes with full CI/tooling and final integration. "Industrial Sensor Platform" is a git release tag on `sensor-hub/` at the end of this phase, not a third project directory.

Imagine this is a $5M product. On FreeRTOS/Nucleo:

- OTA updates (extends the Phase 5 bootloader), configuration system, power management.
- CLI, logging, watchdog, fault handling — already built in Phases 3 and 5, exercised end to end here.
- Drivers and HAL built entirely on the `hal/` interfaces developed since Phase 1.
- Full engineering tooling: CMake, GitHub Actions CI, clang-format, clang-tidy, Doxygen, GoogleTest, code coverage, static analysis.

**After Week 28:** a 3-4 day cumulative mock-interview block (see [phases/phase-6-capstone.md](phases/phase-6-capstone.md#post-week-28-cumulative-mock-interview-block)) re-tests material from all 7 phases cold, in one sitting — the weekly Friday prompts build the reflex while material is fresh; this block simulates what an actual loop demands.

---

## Weekly Schedule

| Day | Focus |
|---|---|
| Monday | Learn concepts |
| Tuesday | Implement |
| Wednesday | Debug and break things |
| Thursday | Optimize and refactor |
| Friday | Architecture interview practice |
| Saturday | Long project session |
| Sunday | Retrospective — read source code, document learnings, update notes |

---

## Reading List

**C++:** A Tour of C++ · Effective Modern C++ · C++ Concurrency in Action · Large-Scale C++ Software Design

**Embedded:** Making Embedded Systems · Embedded Systems Architecture · Patterns in the Machine

**Software Design:** Clean Architecture · Design Patterns

**Computer Systems:** Computer Systems: A Programmer's Perspective

---

## Success Criteria

At the end of 28 weeks, you should be able to:

1. Design embedded systems from requirements, not just implement given specs.
2. Explain architectural decisions and defend trade-offs (concurrency, memory limits, driver boundaries).
3. Write production-quality, modern C++.
4. Understand hardware/software boundaries and explain exactly how a context switch happens under an RTOS.
5. Debug complex failures across the stack.
6. Architect a decoupled firmware system that is partially testable on a PC before it ever touches hardware.
7. Build systems that are testable and maintainable, backed by real unit test coverage.
8. Read Cortex-M/ARM disassembly and diagnose a hard fault from `CFSR`/`HFSR` register state alone.
9. Clear a general DSA interview round (~120-150 problems solved, six core patterns kept warm) alongside the embedded-specific rounds.

When asked *"Design the firmware for a battery-powered industrial sensor node,"* the response should naturally follow:

```
Requirements → Constraints → Hardware → Architecture → Drivers →
Concurrency → Error Handling → Testing → Manufacturing → Maintenance
```

This is the transition from implementing firmware to designing embedded systems.
