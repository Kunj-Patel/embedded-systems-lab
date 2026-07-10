← [ROADMAP.md](../ROADMAP.md)

# Phase 4 — System Architecture (Weeks 18-20)

**Goal:** Transition from firmware developer to systems engineer. This phase has no algorithms track and no new peripheral to learn — it's about formalizing and defending the architecture built across Phases 1-3.

Day themes as in [ROADMAP.md](../ROADMAP.md#weekly-schedule), with Friday's architecture-interview practice deepening into full mock-interview format every week.

---

## Week 18 — Formalize the HAL/BSP Layering

**Deliverables:**
- Review `hal/` as built across Phases 1-3 and formalize the layering: a clear HAL (peripheral interfaces) versus BSP (board-specific config — pin mappings, clock trees) separation. Refactor if the two are currently tangled.
- Note in `notes/architecture/` on driver models — what makes a driver interface reusable across boards versus coupled to one.
- Introduce a simple event-bus or pub/sub mechanism (if not already present from the Sensor Hub's queues) and document where it's appropriate versus direct queues/mutexes.

**Friday — full mock interview:** "Design the firmware for a battery-powered industrial sensor node." Walk through requirements → constraints → hardware → architecture → drivers → concurrency → error handling → testing → manufacturing → maintenance (the [Success Criteria](../ROADMAP.md#success-criteria) loop). Do this unaided, then review against feedback.

---

## Week 19 — Dependency Injection for Testability, Embedded Framework Project

**Deliverables:**
- **Project — Embedded Framework (`projects/embedded-framework/`):** structure a reusable template with `drivers/`, `hal/`, `kernel/`, `middleware/`, `applications/` — this formalizes the pattern used informally since Phase 1 into an explicit, documented template.
- Demonstrate dependency injection for testability end to end: take one piece of application logic (e.g., from the Sensor Hub or Vending Machine) and show it fully unit-testable on the Mac via injected mocks, with no Nucleo required to run the test suite.

**Friday — mock interview:** "How would you structure a firmware repo so a new peripheral driver can be added without touching application logic?"

---

## Week 20 — Architecture Defense, Phase Close-Out

**Deliverables:**
- Finish and document the Embedded Framework project to the Rule 7 bar.
- Write a short design document (in `notes/architecture/`) defending at least three non-obvious architectural decisions made across Phases 1-4 — why this and not the alternative.
- Full retrospective across Phases 1-4: what part of the architecture would you redesign now, knowing what you know after building the Sensor Hub?

**Friday — full mock interview:** present the Embedded Framework's architecture cold, as if to an interviewer, defending trade-offs under questioning.

**Sunday retro + Phase 4 close-out.**

---

## Exit criteria for Phase 4

- `hal/` has a clean, documented HAL/BSP separation.
- Embedded Framework project complete and reusable — could plausibly bootstrap Phase 5/6 projects from it.
- Can defend, unaided and under questioning, the architectural decisions made so far.
- Comfortable running the full "design firmware for X" interview loop without hesitation.

Move to [Phase 5](phase-5-performance.md) once these hold.
