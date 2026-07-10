← [ROADMAP.md](../ROADMAP.md)

# Phase 1 — Modern C++ & Object-Oriented Design (Weeks 3-7)

**Goal:** Transition from procedural C to modern C++, thinking in value semantics, RAII, and composition before reaching for raw arrays or inheritance. This is also where `hal/` and the Vending Machine project begin.

Day themes as in [ROADMAP.md](../ROADMAP.md#weekly-schedule). Algorithms continue daily — this phase's focus: linked lists, stacks, queues.

Toolchain introduced this phase, taught from first use (Rule 5 — nothing is magic): CMake project structure, GoogleTest, clang-format, clang-tidy.

---

## Week 3 — References, Const-Correctness, Classes, RAII

**Deliverables:**
- First real CMake project scaffolded: `hal/` with `CMakeLists.txt`, `include/`, `mock/`, and a `tests/` directory wired to GoogleTest via `FetchContent` or a package manager. Confirm `ninja` builds and `ctest` runs a trivial passing test.
- `.clang-format` and `.clang-tidy` configs added at repo root; understand what each enforces and why (Rule 5: why does this tool exist, what problem does it solve).
- A small RAII exercise: a class that owns a resource (e.g., a heap buffer or a file handle) with constructor/destructor pairing, demonstrated to correctly release on scope exit including early-return and exception paths.
- Note in `notes/modern-cpp/` on references vs. pointers vs. `const` correctness — when to use each, in your own words.

**Friday architecture prompt:** "Why does RAII matter more in embedded/systems code than in a typical scripting-language application?"

---

## Week 4 — Object Lifetime, Move Semantics, `hal/` Interfaces Begin

**Deliverables:**
- Note + small experiment on copy vs. move: a class with an expensive-to-copy member (e.g., a buffer), implement copy constructor/assignment and move constructor/assignment, and demonstrate (with logging or a test) that move is actually taken by the compiler where expected.
- Design and implement `IGpio`, `ILed`, `IButton` interfaces in `hal/include/`, plus their mock backend in `hal/mock/`. This is the "Firmware Simulator" from the original scope — deliberately simple, but backed by GoogleTest unit tests (Rule 3) from day one.
- **Project start — Vending Machine (`projects/vending-machine/`):** state machine skeleton (states: idle, selecting, dispensing, fault) plus tests for state transitions. No coin/inventory logic yet.

**Friday architecture prompt:** "Why does a hardware interface (`IGpio`) benefit from dependency injection instead of the application code calling hardware functions directly?"

---

## Week 5 — Templates, `constexpr`, Modern Library Types

**Deliverables:**
- Notes/experiments on `std::optional`, `std::variant`, `std::span`, `std::string_view` — for each, a short written answer to: what problem does this solve that existed before it, and what's the cost of getting it wrong (e.g., dangling `string_view`).
- A basic template exercise: write one generic function or small class template (e.g., a fixed-capacity ring buffer) and explain compile-time vs. runtime cost versus a non-template equivalent.
- **Vending Machine — Week 5 milestone:** coin handling (accept/reject, running balance) implemented against the state machine, tests included.

**Friday architecture prompt:** "When would you choose a template over a virtual-function interface for hardware abstraction, and when is that the wrong call?"

---

## Week 6 — SOLID, Composition, Dependency Injection

**Deliverables:**
- Note in `notes/architecture/` covering SOLID principles with an embedded-relevant example for each (not textbook examples).
- Refactor pass on `hal/` and the Vending Machine so far: identify at least one place inheritance was reached for where composition would be cleaner, and make the change — document the before/after reasoning (this is the Refactor loop, not optional polish).
- **Vending Machine — Week 6 milestone:** inventory tracking, display output (via a mock display or console), and config loading (e.g., prices/stock from a simple config file or struct).

**Friday architecture prompt:** "Walk through how you'd inject a mock `IUart` into the vending machine's debug console for testing, without the vending machine code knowing it's not talking to real hardware."

---

## Week 7 — Exception Safety, Polish, Project Close-Out

**Deliverables:**
- Note on exception safety guarantees (basic/strong/no-throw) and where each applies in code written so far.
- **Vending Machine — Week 7 milestone:** UART debug console finalized, fault recovery (e.g., jammed dispense, invalid state transition) implemented and tested, README written for the project answering Rule 7's bar — could you discuss this for 20 minutes in an interview?
- Full pass of `clang-format` + `clang-tidy` across `hal/` and `projects/vending-machine/`; fix or consciously suppress (with a comment explaining why) any warnings.

**Friday architecture prompt:** full mock interview: "Design a PC-testable vending machine controller — walk me through your architecture." Answer out loud or in writing, unaided.

**Sunday retro + Phase 1 close-out:** confirm the Vending Machine project and `hal/`'s GPIO/LED/Button interfaces are both complete and tested. Confirm you can explain (Four Loops) every design decision made this phase without re-deriving it from scratch.

---

## Algorithms (daily, weeks 3-7)

Focus: linked lists, stacks, queues. Track in `algorithms/leetcode/` as in Phase 0.

## Exit criteria for Phase 1

- `hal/` exists with `IGpio`/`ILed`/`IButton` interfaces, a mock backend, and passing GoogleTest coverage.
- Vending Machine project complete: state machine, coins, inventory, display, UART console, config, fault recovery — all tested.
- CMake + Ninja + GoogleTest + clang-format + clang-tidy all working and understood, not just copy-pasted.
- Comfortable explaining RAII, move semantics, and composition-over-inheritance choices made in this phase's code.

Move to [Phase 2](phase-2-embedded-fundamentals.md) once these hold.
