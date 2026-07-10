← [ROADMAP.md](../ROADMAP.md)

# Phase 1 — Modern C++ & Object-Oriented Design (Weeks 2-7)

**Goal:** Transition from procedural C to modern C++, thinking in value semantics, RAII, and composition before reaching for raw arrays or inheritance. This is also where `hal/` begins and where **`sensor-core`** — the hardware-agnostic application library every later phase links against — is first written.

Day themes as in [ROADMAP.md](../ROADMAP.md#weekly-schedule). Algorithms continue daily — this phase's focus: linked lists, stacks, queues.

Toolchain introduced this phase, taught from first use (Rule 5 — nothing is magic): CMake project structure, GoogleTest, clang-format, clang-tidy.

**Project framing:** the device being built across all 28 weeks is an environmental/condition-monitoring sensor node — it reads sensors, evaluates their readings against thresholds, logs data, and exposes a CLI. This phase builds that application logic entirely in software, against `hal/mock/`, with zero hardware. Repo location: `projects/sensor-core/` — a permanent library that Phase 3 onward links against from `projects/sensor-hub/` (see [Repository Structure](../ROADMAP.md#repository-structure)).

---

## Week 2 — Smart Pointers and STL Algorithms

This week exists because of, not despite, the professional C/STM32 background: two years of embedded C leaves real gaps specifically in modern C++'s memory-ownership and standard-library idioms (both self-rated 2-4/10 in the [Background](../ROADMAP.md#background--starting-baseline)) — `malloc`/`free` discipline doesn't transfer automatically to `unique_ptr`/`shared_ptr` ownership semantics, and `<algorithm>` isn't idiomatic in embedded C at all. This week closes that gap directly, before Week 3's RAII material builds on it.

**Deliverables:**
- `std::unique_ptr` and `std::shared_ptr` exercise: reimplement a small piece of manually-managed C-style resource code (e.g., something structurally similar to a driver handle or buffer you've written professionally) using each smart pointer type, and a note on when each is the right call versus the other versus a raw pointer/reference — specifically, why `unique_ptr` should be the default and `shared_ptr` the exception, and why embedded code is often more skeptical of `shared_ptr`'s hidden allocation/atomic refcounting than a typical application.
- STL `<algorithm>` exercise: solve a handful of small problems (filtering, transforming, searching a collection) once by hand with a raw loop and once with `std::find_if`/`std::transform`/`std::accumulate`/`std::sort` or similar, and a note comparing readability and correctness risk (off-by-one, iterator invalidation) between the two styles.
- Short note in `notes/modern-cpp/` translating C habits directly: where does a `malloc`/`free` pair become a `unique_ptr`, where does a raw loop become an algorithm call, and where (if anywhere) does the embedded/no-heap-after-init constraint mean neither applies — this last point matters, since much of `hal/` and the RTOS work later in the roadmap will deliberately avoid dynamic allocation, and knowing when *not* to reach for these tools is as important as knowing how to use them.

**Friday architecture prompt:** "In a firmware codebase that avoids heap allocation after initialization, where do smart pointers and STL algorithms still earn their place, and where are they actively the wrong tool?"

---

## Week 3 — Toolchain Bring-Up, References, Const-Correctness, Classes, RAII

This is the first week using CMake, GoogleTest, clang-format, and clang-tidy for real — budget Monday-Tuesday for toolchain bring-up before touching new C++ material, and don't feel behind if it spills into Wednesday. Getting a clean build/test loop working is its own real skill, not a distraction from the "real" work.

**Deliverables:**
- Toolchain bring-up (do this first, before any new C++ topic): first real CMake project scaffolded — `hal/` with `CMakeLists.txt`, `include/`, `mock/`, and a `tests/` directory wired to GoogleTest via `FetchContent` or a package manager. Confirm `ninja` builds and `ctest` runs a trivial passing test. `.clang-format` and `.clang-tidy` configs added at repo root; understand what each enforces and why (Rule 5: why does this tool exist, what problem does it solve).
- Once the build/test loop works: a small RAII exercise — a class that owns a resource (e.g., a heap buffer or a file handle) with constructor/destructor pairing, demonstrated to correctly release on scope exit including early-return and exception paths.
- Note in `notes/modern-cpp/` on references vs. pointers vs. `const` correctness — when to use each, in your own words.

**Friday architecture prompt:** "Why does RAII matter more in embedded/systems code than in a typical scripting-language application?"

---

## Week 4 — Object Lifetime, Move Semantics, Interfaces & DI, `hal/` Begins

**Deliverables:**
- Note + small experiment on copy vs. move: a class with an expensive-to-copy member (e.g., a buffer of sensor samples), implement copy constructor/assignment and move constructor/assignment, and demonstrate (with logging or a test) that move is actually taken by the compiler where expected.
- **Before writing any `hal/` interface, read/write a short note in `notes/architecture/` on interfaces and dependency injection specifically** (what problem DI solves, why code should depend on an abstraction instead of a concrete hardware type) — this is pulled forward from what would otherwise be Week 6's SOLID material, because the exercise below requires understanding DI first, not after.
- Design and implement `Gpio`, `Led`, `Button` interfaces in `hal/include/`, plus their mock backend in `hal/mock/`, applying the DI note directly: application code depends on the interface, never on `hal/mock/` concrete types. This is the "Firmware Simulator" from the original scope — deliberately simple, but backed by GoogleTest unit tests (Rule 3) from day one.
- **Project start — `sensor-core` (`projects/sensor-core/`):** top-level state machine skeleton (states: `Boot`, `SelfTest`, `Sampling`, `Fault`) plus tests for state transitions. No real sensor reading logic yet — the state machine is exercised with fake/injected values.

**Friday architecture prompt:** "Why does a hardware interface (`Gpio`) benefit from dependency injection instead of the application code calling hardware functions directly?"

---

## Week 5 — Templates, `constexpr`, Modern Library Types

**Deliverables:**
- A `Sensor` interface (returns a reading + status) designed using this week's material directly: `std::optional<Reading>` for "no data available yet," `std::span<const std::byte>` or similar for raw sample buffers, `std::string_view` for sensor names/units — each choice justified in a short note answering what problem it solves versus the pre-C++17 alternative, and the cost of getting it wrong (e.g., a dangling `string_view`).
- A basic template exercise directly reused by the project: a fixed-capacity ring buffer template (`RingBuffer<T, N>`) — this is the same structure `sensor-core` will use to hold recent samples, and later becomes the backbone of Phase 5's logger. Explain compile-time vs. runtime cost versus a non-template equivalent.
- **`sensor-core` — Week 5 milestone:** wire a mock `Sensor` into the state machine; `Sampling` state pulls readings via the injected interface into the `RingBuffer` from this week's exercise, with tests.

**Friday architecture prompt:** "When would you choose a template over a virtual-function interface for hardware abstraction, and when is that the wrong call?"

---

## Week 6 — SOLID and Composition Over Inheritance

Week 4 already introduced dependency injection as a practical necessity for `hal/`. This week generalizes that experience into the full SOLID picture and applies it critically — including finding a place where the DI-first instinct from Week 4 was applied *incorrectly* (e.g., an interface reached for where a simple concrete type would have been fine).

**Deliverables:**
- Note in `notes/architecture/` covering all five SOLID principles with an embedded-relevant example for each (not textbook examples) — pull at least two examples directly from `hal/` or `sensor-core` written so far, referencing the Week 4 DI note as the concrete case that motivated this broader look.
- Refactor pass on `hal/` and `sensor-core`: identify at least one place inheritance was reached for where composition would be cleaner, and make the change — document the before/after reasoning (this is the Refactor loop, not optional polish).
- **`sensor-core` — Week 6 milestone:** threshold/alerting logic (a reading outside configured bounds transitions the state machine toward `Fault` or raises an alert record) plus config loading (thresholds, sample interval from a simple struct or file).

**Friday architecture prompt:** "Walk through how you'd inject a mock `Uart` into the sensor node's debug console for testing, without the application code knowing it's not talking to real hardware."

---

## Week 7 — Exception Safety, Polish, Project Close-Out

**Deliverables:**
- Note on exception safety guarantees (basic/strong/no-throw) and where each applies in code written so far.
- **`sensor-core` — Week 7 milestone:** UART debug console/CLI finalized (query current readings, thresholds, and state over a mock UART), fault recovery (e.g., a sensor read failure transitions to `Fault` and back to `Sampling` after recovery, rather than crashing) implemented and tested. README written for the project answering Rule 7's bar — could you discuss this for 20 minutes in an interview?
- Full pass of `clang-format` + `clang-tidy` across `hal/` and `projects/sensor-core/`; fix or consciously suppress (with a comment explaining why) any warnings.

**Friday architecture prompt:** full mock interview: "Design a PC-testable sensor node application — walk me through your architecture." Answer out loud or in writing, unaided.

**Sunday retro + Phase 1 close-out:** confirm `sensor-core` and `hal/`'s GPIO/LED/Button interfaces are both complete and tested. Confirm you can explain (Four Loops) every design decision made this phase without re-deriving it from scratch.

---

## Algorithms (daily, weeks 2-7)

Focus: linked lists, stacks, queues. Track in `algorithms/leetcode/` per the [Algorithm Interview Prep](../ROADMAP.md#algorithm-interview-prep) system.

## Exit criteria for Phase 1

- `hal/` exists with `Gpio`/`Led`/`Button`/`Sensor` interfaces, a mock backend, and passing GoogleTest coverage.
- `sensor-core` project complete: state machine, sensor ingestion via `RingBuffer<T, N>`, threshold/alerting, config, UART CLI, fault recovery — all tested, all running against `hal/mock/` with zero hardware.
- CMake + Ninja + GoogleTest + clang-format + clang-tidy all working and understood, not just copy-pasted.
- Comfortable explaining RAII, move semantics, and composition-over-inheritance choices made in this phase's code.
- Comfortable choosing between `unique_ptr`, `shared_ptr`, a raw pointer/reference, and no dynamic allocation at all — and explaining why, specifically in an embedded context.

**What carries forward:** `sensor-core` — its state machine, `Sensor` interface, and `RingBuffer` — is the application library Phase 2 puts on real hardware (unmodified) and Phase 3 links into a new `sensor-hub/` project alongside FreeRTOS. `sensor-core/` itself is never renamed, rewritten, or thrown away — it stays a standalone, hardware-agnostic library for the rest of the roadmap.

Move to [Phase 2](phase-2-embedded-fundamentals.md) once these hold.
