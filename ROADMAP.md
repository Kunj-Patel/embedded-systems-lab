# Embedded Systems 28-Week Roadmap

This document is the single source of truth for this repository's engineering journey. It supersedes all earlier drafts.

**How to use this with an agent:** this file has the mission, rules, architecture, and full 28-week phase overview. The week-by-week deliverables and Friday interview prompts for whichever phase is currently active live in a linked file under [phases/](phases/) (see the table in [28-Week Phase Breakdown](#28-week-phase-breakdown)) — point an agent at the current phase file plus this one for full context on where things stand and what's next.

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

## Background / Starting Baseline

- **Environment:** Apple M1 Pro, VSCode, CMake, Ninja, clang++/LLVM, ld64, clang-tidy, clang-format.
- **Hardware target:** STM32 Nucleo (specific model TBD — pick before Phase 2, Week 8).
- **Modern C++:** Beginner-ish overall (self-rated 2-4/10 across references, pointers, RAII, constructors/destructors, move semantics, templates, constexpr, smart pointers, STL algorithms, `std::optional`/`variant`/`span`, lambdas). Fundamentals get real time, not a skim.
- **Toolchain experience:** New to CMake, GoogleTest, clang-format, clang-tidy, and Doxygen as practiced tools — all taught explicitly from first use, nothing assumed.
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
│   └── reliability/
│
├── experiments/           # Small, falsifiable investigations: hypothesis → implementation → measurement → conclusion
│   ├── cpp/
│   ├── memory/
│   ├── concurrency/
│   └── performance/
│
├── hal/                    # The shared Firmware Simulator: interfaces + two backends (see below)
│   ├── include/             # IGpio, ILed, IButton, IUart, ISpi, II2c, ITimer, ...
│   ├── mock/                 # Host backend — runs on the Mac, used in unit tests
│   └── stm32/                 # Real backend — register-level STM32 implementation
│
├── projects/               # Complete engineering artifacts, portfolio-grade
│   ├── vending-machine/
│   ├── rtos-sensor-hub/
│   ├── embedded-framework/
│   ├── high-speed-data-logger/
│   └── industrial-sensor-platform/
│
└── algorithms/             # Daily interview-prep practice
    └── leetcode/
```

---

## The HAL / Firmware Simulator Architecture

This is the one structural idea that ties the whole roadmap together, and it starts life as the "Firmware Simulator" — deceptively simple GPIO/LED/Button interfaces built in Phase 1.

The core design: **one interface, two backends.**

```
                 IGpio / IUart / ISpi / II2c / ITimer ...
                              (hal/include/)
                    ▲                          ▲
                    │                          │
              mock backend               stm32 backend
           (hal/mock/, runs on Mac)   (hal/stm32/, runs on Nucleo)
                    │                          │
                    └──────────┬───────────────┘
                               │
                     projects/* consume the
                     interface, never the backend
```

Every peripheral driver is designed against an interface first. The mock backend lets application logic (state machines, services, business rules) be built and unit-tested entirely on the Mac, at full speed, with GoogleTest — no board required for daily work. The STM32 backend implements the same interface at the register level and is verified against real hardware during dedicated Nucleo sessions.

This is why the vending machine, sensor hub, data logger, and capstone projects never reinvent GPIO or UART mocks — they all depend on `hal/`, and swapping from simulation to real hardware is a link-time backend swap, not a rewrite. This is also what makes Rule 3 (unit tests for everything) practical for embedded work: the hardware boundary is mocked, not skipped.

The interface set grows over the roadmap: GPIO/LED/Button (Phase 1) → Timer/UART/SPI/I2C/ADC/Interrupts (Phase 2) → Scheduler primitives (Phase 3) → formalized HAL/BSP layering (Phase 4) → DMA (Phase 5).

---

## 28-Week Phase Breakdown

Each phase below has a full weekly deliverables breakdown in its own file — link to the specific phase file when asking an agent for help on current work, so it has the exact week's context without loading all 28 weeks.

| Phase | Weeks | File |
|---|---|---|
| 0 — Raw C Refresher | 1-2 | [phases/phase-0-raw-c.md](phases/phase-0-raw-c.md) |
| 1 — Modern C++ & OOD | 3-7 | [phases/phase-1-modern-cpp.md](phases/phase-1-modern-cpp.md) |
| 2 — Embedded Fundamentals + Nucleo | 8-12 | [phases/phase-2-embedded-fundamentals.md](phases/phase-2-embedded-fundamentals.md) |
| 3 — RTOS Ground-Up | 13-17 | [phases/phase-3-rtos.md](phases/phase-3-rtos.md) |
| 4 — System Architecture | 18-20 | [phases/phase-4-architecture.md](phases/phase-4-architecture.md) |
| 5 — Performance Engineering | 21-24 | [phases/phase-5-performance.md](phases/phase-5-performance.md) |
| 6 — Capstone | 25-28 | [phases/phase-6-capstone.md](phases/phase-6-capstone.md) |

### Phase 0 — Raw C Refresher (Weeks 1-2)

*Weekly breakdown: [phases/phase-0-raw-c.md](phases/phase-0-raw-c.md)*

**Goal:** Rebuild core muscle memory before introducing C++ or hardware complexity.

- Bitwise mastery: set/clear/toggle/read bits and bitfields until automatic.
- Pointer gymnastics: direct memory manipulation, buffer casting, array iteration.
- Memory layout: stack, heap, data, BSS — place variables explicitly and inspect addresses.
- **Experiment:** implement and benchmark a custom `memcpy`/`memset`.
- **Algorithms begin here:** 30-45 min/day in `algorithms/leetcode/`, starting with arrays and strings.

### Phase 1 — Modern C++ & Object-Oriented Design (Weeks 3-7)

*Weekly breakdown: [phases/phase-1-modern-cpp.md](phases/phase-1-modern-cpp.md)*

**Goal:** Transition from procedural C to modern C++, thinking in value semantics, RAII, and composition before reaching for raw arrays or inheritance.

Topics:
- References, pointers, `const` correctness, `enum class`, `constexpr`, lambdas, classes/structs.
- Object lifetime: constructors, destructors, copy semantics, move semantics.
- RAII, ownership models, deterministic cleanup, exception safety.
- Modern library: `std::array`, `std::vector`, `std::span`, `std::string_view`, `std::optional`, `std::variant`, `std::chrono`, STL algorithms.
- Templates and basic generic programming.
- Software design: SOLID, composition over inheritance, interfaces, dependency injection.

**`hal/` begins here:** design `IGpio`, `ILed`, `IButton` and their mock backend — this is the original "Firmware Simulator" scope, unit-tested with GoogleTest.

**Project:** PC-only Vending Machine — pure software, state machine, DI, no hardware registers yet. Demonstrates OOD, testing, error handling.

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

Toolchain additions: `arm-none-eabi-gcc`, OpenOCD/ST-Link, register-level programming, linker script fundamentals.

**Project:** extend `hal/` with the STM32 backend for every interface above; verify mock and real implementations behave identically from the application's point of view.

**Algorithms:** trees, basic graph traversal (DFS/BFS).

### Phase 3 — RTOS Ground-Up (Weeks 13-17)

*Weekly breakdown: [phases/phase-3-rtos.md](phases/phase-3-rtos.md)*

**Goal:** Think in systems. Build the mechanics before adopting an off-the-shelf OS.

- Write a timer interrupt that context-switches between two infinite-loop tasks (your own toy scheduler).
- Two tasks sharing one UART console; implement a mutex; deliberately omit it and observe corruption.
- Visualize preemption and priority inversion (Segger SystemView or similar, if available).
- Migrate to **FreeRTOS** on the Nucleo once the ground-up scheduler is understood: scheduling, preemption, priorities, priority inversion, mutexes, semaphores, queues, memory pools.
- Intentionally create deadlocks, race conditions, starvation, and priority inversion — then fix them.

**Project:** RTOS Sensor Hub — Temperature/Humidity/Logger/CLI/Watchdog tasks communicating via queues and events (no global variables), built on the `hal/` STM32 backend from Phase 2.

**Algorithms:** dynamic programming basics, recursion.

### Phase 4 — System Architecture (Weeks 18-20)

*Weekly breakdown: [phases/phase-4-architecture.md](phases/phase-4-architecture.md)*

**Goal:** Transition from firmware developer to systems engineer.

- Formalize `hal/` into a layered architecture: HAL, BSP, driver models, event buses.
- Dependency injection for testability — mock sensors injected into business logic for PC-side unit tests.
- Weekly architecture-interview practice deepens: "design firmware for a battery-powered industrial sensor" — requirements, power budget, MCU choice, memory, communication, RTOS decision, storage, security, OTA, manufacturing test.

**Project:** Embedded Framework — reusable template with `drivers/`, `hal/`, `kernel/`, `middleware/`, `applications/`.

### Phase 5 — Performance Engineering (Weeks 21-24)

*Weekly breakdown: [phases/phase-5-performance.md](phases/phase-5-performance.md)*

**Goal:** Measure, analyze, optimize.

- Memory: cache behavior, DMA, zero-copy, memory pools.
- Concurrency: lock-free programming, atomics, memory ordering, false sharing.
- Build: compiler optimization flags, LTO, linker behavior, map files, binary size, boot time.

**Project:** High-Speed Data Logger — DMA-driven SPI sensor capture into a circular buffer, written to an SD card, CRC-validated, recoverable after power loss. Measure latency, throughput, memory and CPU usage.

### Phase 6 — Capstone: Industrial Sensor Platform (Weeks 25-28)

*Weekly breakdown: [phases/phase-6-capstone.md](phases/phase-6-capstone.md)*

**Goal:** Combine every discipline into a flagship portfolio project.

Imagine this is a $5M product. On FreeRTOS/Nucleo:

- Bootloader, OTA updates, CLI, logging, watchdog, BLE/USB, configuration system, flash filesystem.
- Drivers and HAL built entirely on the `hal/` interfaces developed since Phase 1.
- State machines, power management, fault handling.
- Full engineering tooling: CMake, GitHub Actions CI, clang-format, clang-tidy, Doxygen, GoogleTest, code coverage, static analysis.

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

When asked *"Design the firmware for a battery-powered industrial sensor node,"* the response should naturally follow:

```
Requirements → Constraints → Hardware → Architecture → Drivers →
Concurrency → Error Handling → Testing → Manufacturing → Maintenance
```

This is the transition from implementing firmware to designing embedded systems.
