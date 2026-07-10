← [ROADMAP.md](../ROADMAP.md)

# Phase 6 — Capstone: Industrial Sensor Platform (Weeks 25-28)

**Goal:** Combine every discipline from Phases 0-5 into one flagship portfolio project. Treat this as if it were a $5M product — full tooling, full documentation, no shortcuts on the pieces you already know how to build well.

Day themes as in [ROADMAP.md](../ROADMAP.md#weekly-schedule). No new topics are introduced this phase — it's integration, polish, and CI.

Repo location: `projects/industrial-sensor-platform/`, built on `hal/` and the FreeRTOS foundation from Phase 3.

---

## Week 25 — Bootloader and OTA Foundation

**Deliverables:**
- Minimal bootloader: verifies and jumps to an application image in flash, with a defined memory layout (bootloader region + application region) documented in a linker script.
- OTA update mechanism (can be simplified — e.g., a "load new image over UART/USB and flash it" flow rather than full wireless OTA, given board constraints) with image validation (CRC/checksum) before committing to boot it.
- Note on why bootloader/application separation and image validation matter — what failure mode does each guard against.

**Friday architecture prompt:** "What happens if power is lost mid-OTA-update, and how does your design guarantee the device doesn't brick?"

---

## Week 26 — Watchdog, Fault Handling, State Machines, Power Management

**Deliverables:**
- Hardware watchdog integrated: task/system liveness monitored, watchdog kicked only when the system is genuinely healthy (not just kicked unconditionally in a timer ISR — that would defeat the purpose).
- Fault handling: define and implement recovery behavior for at least two realistic fault classes (e.g., sensor read failure, bus hang, stack overflow detection if feasible).
- Top-level state machine for the platform (e.g., boot → self-test → normal operation → fault → safe mode) and, if the board supports it, basic power management (sleep modes between samples).

**Friday architecture prompt:** "Design the fault taxonomy for this platform — which faults are recoverable in software, which require a reset, and which should escalate to a safe/degraded mode?"

---

## Week 27 — CLI, Logging, Configuration, Full Tooling Pass

**Deliverables:**
- CLI and structured logging finalized on top of the Phase 2/3 UART and RTOS work.
- Configuration system (e.g., persisted settings in flash) implemented and tested.
- Full engineering tooling pass: CMake build is clean, GitHub Actions CI runs the host-side (mock backend) unit test suite on every push, clang-format/clang-tidy enforced in CI, Doxygen generates docs for `hal/` and the platform code, code coverage measured for the mock-backend test suite.

**Friday architecture prompt:** "What's covered by your CI, and what's the one class of bug CI on this project cannot catch (i.e., what still requires hardware-in-the-loop testing)?"

---

## Week 28 — Integration, Documentation, Final Defense

**Deliverables:**
- Full system integration test on real hardware: boot → self-test → sensing → logging → CLI interaction → simulated fault → recovery, run end to end and observed working.
- Project README written to the Rule 7 bar and beyond — this is the capstone of a 6-month portfolio, so it should clearly state the architecture, the trade-offs, and point to the specific commits/experiments that justify each major decision.
- Final retrospective across the full 28 weeks: what would you redesign knowing everything you know now? What's the single hardest bug you fixed, and why?

**Friday — final mock interview:** present the Industrial Sensor Platform cold, end to end, defending every layer (bootloader through application) under questioning, following the loop from [Success Criteria](../ROADMAP.md#success-criteria):

```
Requirements → Constraints → Hardware → Architecture → Drivers →
Concurrency → Error Handling → Testing → Manufacturing → Maintenance
```

**Sunday — final retro and bootcamp close-out.**

---

## Exit criteria for Phase 6 (and the full roadmap)

- Industrial Sensor Platform boots, self-tests, senses, logs, accepts CLI commands, survives an induced fault, and recovers — demonstrated live on the Nucleo.
- CI pipeline (GitHub Actions) runs tests, static analysis, and formatting checks automatically.
- Every [Success Criteria](../ROADMAP.md#success-criteria) item from ROADMAP.md can be demonstrated with a specific artifact from this repository, not just claimed.
