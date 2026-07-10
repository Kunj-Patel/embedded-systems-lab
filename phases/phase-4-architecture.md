← [ROADMAP.md](../ROADMAP.md)

# Phase 4 — System Architecture (Weeks 18-20)

**Goal:** Transition from firmware developer to systems engineer. This phase introduces no new peripherals and no new project — it takes `hal/` and `sensor-hub`, both already working and tested, and refactors them into a formally-documented layered architecture. `sensor-core/` is not touched by this refactor; it's already a clean, standalone library, and stays that way. This is deliberately a refactor of a live system under its own test suite, not a fresh template — real engineering teams harden existing systems far more often than they greenfield new ones, and doing that under test coverage you already trust is the actual skill being taught here.

Day themes as in [ROADMAP.md](../ROADMAP.md#weekly-schedule), with Friday's architecture-interview practice deepening into full mock-interview format every week.

---

## Week 18 — Formalize the HAL/BSP Layering

**Deliverables:**
- Review `hal/` as built across Phases 1-3 and formalize the layering: a clear HAL (peripheral interfaces) versus BSP (board-specific config — pin mappings, clock trees) separation. Refactor `hal/stm32/` so board-specific configuration is isolated from peripheral logic — confirm the full `sensor-hub` test suite (mock backend) still passes after the refactor.
- Note in `notes/architecture/` on driver models — what makes a driver interface reusable across boards versus coupled to one.
- Formalize `sensor-hub`'s queue-based task communication (from Phase 3 Week 16-17) into a documented event-bus/pub-sub pattern where it makes sense, and note where a direct queue is still the better choice — not everything should be forced through one mechanism.

**Friday — full mock interview:** "Design the firmware for a battery-powered industrial sensor node." Walk through requirements → constraints → hardware → architecture → drivers → concurrency → error handling → testing → manufacturing → maintenance (the [Success Criteria](../ROADMAP.md#success-criteria) loop). Do this unaided, then review against feedback.

---

## Week 19 — Dependency Injection for Testability, Layered Directory Structure

**Deliverables:**
- Reorganize `projects/sensor-hub/` (in place — this is a `git mv`-and-adjust refactor within `sensor-hub/`, not a new project and not touching `sensor-core/`) into explicit `drivers/`, `kernel/` (scheduler/task glue), `middleware/` (logging, CLI, config), and `application/` (the task wrappers that compose `sensor-core`) layers, sitting on top of `hal/` and linking `sensor-core` as before. Confirm the test suite and a real hardware smoke test both still pass after the reorganization.
- Demonstrate dependency injection for testability end to end: pick one piece of logic from `sensor-core` (already hardware-agnostic by design since Phase 1) and show it fully unit-testable on the Mac via injected mocks, with no Nucleo required to run the test suite — this should already be true, and this week is where you demonstrate and document it explicitly.

**Friday — mock interview:** "How would you structure a firmware repo so a new peripheral driver can be added without touching application logic?"

---

## Week 20 — Architecture Defense, Phase Close-Out

**Deliverables:**
- Update the `sensor-hub` README to document the now-formalized layered architecture (a diagram of `drivers/kernel/middleware/application` over `hal/`, plus where `sensor-core` sits as a linked library underneath it all, is worth writing out).
- Write a short design document (in `notes/architecture/`) defending at least three non-obvious architectural decisions made across Phases 1-4 — including why `sensor-core`/`sensor-hub` is a library-consumer split rather than one project renamed over time — why this and not the alternative.
- Full retrospective across Phases 1-4: what part of the architecture would you redesign now, knowing what you know after building and refactoring the Sensor Hub?

**Friday — full mock interview:** present `sensor-hub`'s now-layered architecture cold, as if to an interviewer, defending trade-offs under questioning.

**Sunday retro + Phase 4 close-out.**

---

## Exit criteria for Phase 4

- `hal/` has a clean, documented HAL/BSP separation.
- `sensor-hub` is reorganized into explicit `drivers/kernel/middleware/application` layers, still linking `sensor-core` unmodified, with its full test suite and a real hardware smoke test both still passing post-refactor.
- Can defend, unaided and under questioning, the architectural decisions made so far — including the `sensor-core`/`sensor-hub` split itself.
- Comfortable running the full "design firmware for X" interview loop without hesitation.

**What carries forward:** the layered `sensor-hub` is what Phase 5 hardens (DMA logging, bootloader) and Phase 6 ships as the capstone — no new project starts here, and none will for the rest of the roadmap. `sensor-core` remains the unmodified library underneath it.

Move to [Phase 5](phase-5-performance.md) once these hold.
