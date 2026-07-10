← [ROADMAP.md](../ROADMAP.md)

# Phase 3 — RTOS Ground-Up (Weeks 13-17)

**Goal:** Think in systems. Build the scheduling mechanics from scratch before adopting FreeRTOS, per the ground-up-then-industry-standard philosophy — the point is to be able to explain what FreeRTOS is doing under the hood, not just call its API. This phase also creates **`sensor-hub`** — a new project that links the Phase 1-2 `sensor-core` library into a proper multi-tasking system, without modifying `sensor-core` itself — and, since "what happens when a task hangs" is a scheduling question, is where watchdog and fault-handling naturally belong, rather than being bolted on at the very end of the roadmap.

Day themes as in [ROADMAP.md](../ROADMAP.md#weekly-schedule). Algorithms continue daily — this phase's focus: dynamic programming basics, recursion.

---

## Week 13 — Toy Scheduler From Scratch

**Deliverables:**
- A timer interrupt that performs a context switch (saving/restoring the stack pointer and register state) between two simple infinite-loop tasks, running on the Nucleo. This is bare-metal, no RTOS library — the point is to demonstrate you understand what a context switch actually is at the register/stack level.
- Note in `notes/embedded/` explaining, step by step, what happens during your context switch: what's saved, where, and how execution resumes in the other task.

**Friday architecture prompt:** "What's the minimum state that must be saved during a context switch, and what happens if you get it wrong?"

---

## Week 14 — Mutual Exclusion, Observed Corruption

**Deliverables:**
- Two tasks (from Week 13's scheduler) both writing to a single shared UART console without synchronization — capture and document the observed corruption/interleaving.
- Implement a simple mutex/lock primitive from scratch and fix the corruption; document the before/after.
- If available, visualize task preemption (Segger SystemView or a similar trace tool) — otherwise, instrument manually via GPIO toggles + logic analyzer or timestamped UART logs.

**Friday architecture prompt:** "Why is a naive shared counter (`counter++`) unsafe across two preemptible tasks even on a single core, and what are the possible fixes?"

---

## Week 15 — FreeRTOS Migration

**Deliverables:**
- FreeRTOS integrated into the Nucleo project (via STM32CubeMX-generated scaffolding or manual port — your call, document which and why).
- Port the two-task mutex example from Weeks 13-14 onto FreeRTOS primitives (tasks, mutex) and confirm equivalent behavior — this is the bridge from "I built this" to "I understand what the library is doing for me."
- Note comparing your from-scratch scheduler/mutex to FreeRTOS's: what did FreeRTOS add (priorities, tick management, memory allocation schemes) that your version didn't have?

**Friday architecture prompt:** "What is priority inversion, concretely, and what mechanism does FreeRTOS provide to mitigate it?"

---

## Week 16 — `sensor-hub`: Composing `sensor-core` Into FreeRTOS Tasks

**Deliverables:**
- **New project — `sensor-hub` (`projects/sensor-hub/`):** scaffold a new CMake target that links `sensor-core` (as a library dependency, unmodified) plus `hal/` plus FreeRTOS. This is a new directory, not a rename — `sensor-core/` keeps existing exactly as Phase 1-2 left it, and `sensor-hub/` is what depends on it going forward. See [Repository Structure](../ROADMAP.md#repository-structure) for the split.
- Decompose the Phase 1-2 application (state machine, `ISensor` backends, `RingBuffer`, CLI — all still living in `sensor-core`) into separate FreeRTOS tasks in `sensor-hub/tasks/`: a Sensor task per real sensor (SPI/I2C from Phase 2), a Logger task, a CLI task — communicating results via queues, no global variables/shared state. Each task is a thin wrapper that calls into `sensor-core`'s existing, tested logic — this is composition of working code into a concurrent architecture, not a rewrite, and not a modification of `sensor-core` itself.
- Note on why queues/message-passing were chosen over shared memory + locks for inter-task communication in this design, and on why `sensor-core` staying hardware/RTOS-agnostic (no task or queue types leaking into it) keeps it independently testable on the Mac forever, regardless of what wraps it.

**Friday architecture prompt:** "Design the task/queue topology for a sensor hub with 4 sensors, a logger, and a CLI. Where do you need mutexes versus queues, and why?"

---

## Week 17 — Watchdog, Fault Handling, State Machine Hardening, Deliberate Failures

**Deliverables:**
- Hardware watchdog integrated as its own task: monitors liveness of the Sensor/Logger/CLI tasks (e.g., via per-task "I'm alive" heartbeats into the watchdog), and only kicks the hardware watchdog when the system is genuinely healthy — not kicked unconditionally in a timer ISR, which would defeat the purpose.
- Harden the top-level state machine (carried from Phase 1's `Boot → SelfTest → Sampling → Fault`) to reflect real task-level failures: a sensor task missing its deadline or a queue overflowing should drive the system toward `Fault`, and recovery back to `Sampling` should be demonstrated, not just theorized.
- **Hard-fault deep dive:** write a `HardFault_Handler` that reads the Cortex-M fault status registers (`CFSR`, `HFSR`, and the stacked exception frame — `PC`/`LR`/`PSR` at the time of fault) and reports what actually happened. Deliberately trigger at least two distinct hard faults (e.g., a null-pointer write, an unaligned access, a stack overflow from Week 13's context-switch code) and use the fault registers to diagnose each — not a debugger breakpoint, the actual register-level forensics a device in the field would need. Note in `notes/embedded/` on what `CFSR` bits mean and how you'd extend this into a poor-man's crash reporter (log the fault frame to flash before reset).
- Deliberately introduce at least two of: a deadlock, a race condition, priority inversion, or task starvation — reproduce it, diagnose it using whatever tracing is available, then fix it. Document each bug and fix as a mini case study.
- Project README for `sensor-hub` written to the Rule 7 bar (20-minute interview discussion) — this README lives in `projects/sensor-hub/` and is maintained continuously from here through Phase 6.

**Friday architecture prompt:** full mock interview, two parts. First, open-ended system design (30-45 min, per [Mock Interview Discipline](../ROADMAP.md#mock-interview-discipline)): "Design the task and concurrency architecture for a multi-sensor embedded system from scratch — how many tasks, what talks to what, where do mutexes vs. queues go, how does it stay debuggable." Then narrow it to the case you actually built: "Walk me through how you'd debug a task that's intermittently missing its deadline in this system, and how your watchdog would react if you couldn't fix it in time."

**Sunday retro + Phase 3 close-out.**

---

## Algorithms (daily, weeks 13-17)

Focus: dynamic programming basics, recursion.

## Exit criteria for Phase 3

- Can explain a context switch at the register/stack level, unaided, because you built one.
- FreeRTOS running reliably on the Nucleo with tasks, queues, and at least one mutex in real use.
- `sensor-hub` project complete: links `sensor-core` (unmodified) into a multi-tasked system (per-sensor tasks, logger, CLI, watchdog), queue-based communication, no global shared state, and a state machine that reacts to real task-level faults.
- At least two deliberately-induced concurrency bugs diagnosed and fixed with documented reasoning.
- Can read a Cortex-M fault frame (`CFSR`/`HFSR` + stacked `PC`/`LR`) and diagnose the root cause of a hard fault from register state alone, because you've done it at least twice.

**What carries forward:** `sensor-hub` is the project every remaining phase builds on — Phase 4 formalizes its architecture, Phase 5 hardens its logging path and adds a bootloader, Phase 6 adds OTA/power/config and ships it as the capstone. `sensor-core` continues to exist unmodified underneath it, still independently testable on the Mac with zero RTOS or hardware involved.

Move to [Phase 4](phase-4-architecture.md) once these hold.
