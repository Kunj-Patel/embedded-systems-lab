← [ROADMAP.md](../ROADMAP.md)

# Phase 3 — RTOS Ground-Up (Weeks 13-17)

**Goal:** Think in systems. Build the scheduling mechanics from scratch before adopting FreeRTOS, per the ground-up-then-industry-standard philosophy — the point is to be able to explain what FreeRTOS is doing under the hood, not just call its API.

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

## Week 16 — RTOS Sensor Hub Project Start

**Deliverables:**
- **Project start — RTOS Sensor Hub (`projects/rtos-sensor-hub/`):** built on the `hal/` STM32 backends from Phase 2. Stand up Temperature and Humidity tasks (or whatever sensors are available) as separate FreeRTOS tasks, communicating results via queues — no global variables/shared state.
- Add a Logger task consuming from those queues and writing to UART.
- Note on why queues/message-passing were chosen over shared memory + locks for inter-task communication in this design.

**Friday architecture prompt:** "Design the task/queue topology for a sensor hub with 4 sensors, a logger, and a CLI. Where do you need mutexes versus queues, and why?"

---

## Week 17 — CLI, Watchdog, Deliberate Failures, Phase Close-Out

**Deliverables:**
- Add CLI and Watchdog tasks to the Sensor Hub. CLI task lets you query sensor state over UART; Watchdog task monitors task liveness.
- Deliberately introduce at least two of: a deadlock, a race condition, priority inversion, or task starvation — reproduce it, diagnose it using whatever tracing is available, then fix it. Document each bug and fix as a mini case study.
- Project README for RTOS Sensor Hub written to the Rule 7 bar (20-minute interview discussion).

**Friday architecture prompt:** full mock interview — "Walk me through how you'd debug a task that's intermittently missing its deadline in this system."

**Sunday retro + Phase 3 close-out.**

---

## Algorithms (daily, weeks 13-17)

Focus: dynamic programming basics, recursion.

## Exit criteria for Phase 3

- Can explain a context switch at the register/stack level, unaided, because you built one.
- FreeRTOS running reliably on the Nucleo with tasks, queues, and at least one mutex in real use.
- RTOS Sensor Hub project complete: multiple sensor tasks, logger, CLI, watchdog, queue-based communication, no global shared state.
- At least two deliberately-induced concurrency bugs diagnosed and fixed with documented reasoning.

Move to [Phase 4](phase-4-architecture.md) once these hold.
