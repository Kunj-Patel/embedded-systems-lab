← [ROADMAP.md](../ROADMAP.md)

# Phase 6 — Capstone: Industrial Sensor Platform (Weeks 25-28)

**Goal:** Ship `sensor-hub` — created in Phase 3 linking `sensor-core` (unchanged since Phase 1), hardened in Phase 3 (RTOS + watchdog + fault handling) and Phase 5 (DMA logging + bootloader) — as a finished, demoable Industrial Sensor Platform. This phase is deliberately *not* where new subsystems are learned for the first time: watchdog, fault handling, and the bootloader already exist and work. Capstone weeks are for OTA (extending the bootloader), power management, configuration, full CI/tooling, and final integration — the things that only make sense once everything underneath them is stable.

Day themes as in [ROADMAP.md](../ROADMAP.md#weekly-schedule). Repo location: `projects/sensor-hub/` (git-tagged as the Industrial Sensor Platform at final release — a release tag, not a new directory or rename).

---

## Week 25 — OTA Updates

**Deliverables:**
- Extend the Week 22 bootloader with an OTA update mechanism: load a new application image over UART or USB and flash it into the application region, reusing the same image-validation (CRC/checksum) logic the bootloader already uses for its verify-and-jump path — this is additive to Phase 5's work, not a new subsystem built from zero.
- Note on why bootloader/application separation and image validation matter — what failure mode each guards against, now demonstrated end to end with a real OTA flow instead of just a local flash.

**Friday architecture prompt:** "What happens if power is lost mid-OTA-update, and how does your design guarantee the device doesn't brick? How does this connect to the power-loss recovery work from Phase 5?"

---

## Week 26 — Power Management and State Machine Polish

**Deliverables:**
- Basic power management if the board supports it: sleep modes between samples, waking on timer or sensor interrupt — evaluate the actual power draw difference (measure it, don't assume it) between always-on polling and sleep-between-samples.
- Review and polish the top-level state machine (from Phase 1, hardened in Phase 3) for the full product lifecycle: `Boot → SelfTest → Sampling → [Fault/SafeMode] → OTA-Update → Sampling`. Confirm the OTA path integrates cleanly with the existing fault/recovery states rather than being a bolted-on special case.

**Friday architecture prompt:** "Design the fault taxonomy for this platform end to end — which faults are recoverable in software (already handled since Phase 3), which require a reset, and which should escalate to a safe/degraded mode?"

---

## Week 27 — Configuration System, Full Tooling Pass

**Deliverables:**
- Configuration system (e.g., persisted settings — thresholds, sample interval — in flash, building on the config loading from Phase 1 Week 6) implemented and tested, survives OTA updates without being wiped.
- Full engineering tooling pass: CMake build is clean, GitHub Actions CI runs the host-side (mock backend) unit test suite on every push, clang-format/clang-tidy enforced in CI, Doxygen generates docs for `hal/` and the platform code, code coverage measured for the mock-backend test suite.

**Friday architecture prompt:** "What's covered by your CI, and what's the one class of bug CI on this project cannot catch (i.e., what still requires hardware-in-the-loop testing)?"

---

## Week 28 — Integration, Documentation, Final Defense

**Deliverables:**
- Full system integration test on real hardware: boot → self-test → sensing (multiple real sensors) → DMA-logged storage → CLI interaction → OTA update → simulated fault → watchdog-triggered recovery, run end to end and observed working. This is a demonstration, not new development — everything exercised here was built in an earlier phase.
- Project README (final update to the same `projects/sensor-hub/` README that's been maintained since Phase 3) written to the Rule 7 bar and beyond — this is the capstone of a 6-month portfolio, so it should clearly state the architecture (including the `sensor-core`/`sensor-hub` library-consumer split), the trade-offs, and point to the specific commits/experiments across all 28 weeks that justify each major decision. Consider a short top-level `projects/README.md` too, pointing at both `sensor-core/` and `sensor-hub/` with one line each on what they are and how they relate — the first thing a reviewer sees when browsing `projects/`.
- Final retrospective across the full 28 weeks: what would you redesign knowing everything you know now? What's the single hardest bug you fixed, and why?

**Friday — final mock interview:** present the Industrial Sensor Platform cold, end to end, defending every layer (bootloader through application) under questioning, following the loop from [Success Criteria](../ROADMAP.md#success-criteria):

```
Requirements → Constraints → Hardware → Architecture → Drivers →
Concurrency → Error Handling → Testing → Manufacturing → Maintenance
```

**Sunday — final retro and bootcamp close-out.**

---

## Exit criteria for Phase 6 (and the full roadmap)

- The Industrial Sensor Platform (`sensor-hub`, linking `sensor-core` since Phase 3) boots, self-tests, senses, logs via DMA, accepts CLI commands, receives an OTA update, survives an induced fault, and recovers via watchdog — demonstrated live on the Nucleo, end to end, in one sitting.
- CI pipeline (GitHub Actions) runs tests, static analysis, and formatting checks automatically.
- Every [Success Criteria](../ROADMAP.md#success-criteria) item from ROADMAP.md can be demonstrated with a specific artifact from this repository, not just claimed.
- You can trace, for any major subsystem (state machine, watchdog, DMA logger, bootloader, OTA), exactly which phase and week it was first built in and why it was sequenced there — and explain why `sensor-core` and `sensor-hub` are two directories, not one renamed over time — because it's genuinely one continuous effort, not five stitched together at the end.

---

## Post-Week-28: Cumulative Mock Interview Block

The weekly Friday prompts test one week's material while it's fresh — this block, done after Phase 6 closes, tests all 28 weeks at once, cold, which is what a real loop actually demands. Budget 3-4 days, not a fixed week — this is rehearsal, not new curriculum, and it's fine to run it lighter or heavier depending on how the mock interviews go.

**Day 1-2 — full-loop simulation.** Assemble one sample Friday prompt from each of the 7 phase files (pull them cold, don't reread the phase file first) plus the two open-ended system-design prompts (Phase 4 Week 18, Phase 3 Week 17) and run all of them back-to-back in a single sitting, each timed per [Mock Interview Discipline](../ROADMAP.md#mock-interview-discipline), each with the adversarial follow-up. This is the closest single-session approximation of an actual onsite loop this roadmap can produce.

**Day 2-3 — live coding, cold.** Pick 3 small implementations from across the whole project (e.g., the ring buffer, a mutex-guarded critical section, the CRC/checksum verify routine) and re-implement each from memory in 15-20 minutes with no reference to the existing solution, on a blank editor or whiteboard — the same discipline as the periodic live-coding reps, but pulling from the full 28 weeks instead of one week.

**Day 3 — behavioral pass.** Review all 6-7 STAR stories accumulated from the per-phase behavioral reps; pick the 3 strongest, tighten them to 90 seconds each, and rehearse out loud until they don't need notes.

**Day 4 — final defense, unaided.** Re-run the Week 28 final mock interview once more, cold, without having reread this week's own notes beforehand — the real bar isn't "can defend it right after writing the README," it's "can defend it after a few days away," which is closer to the gap between finishing a portfolio and actually interviewing with it weeks or months later.

**Exit criteria for this block:** every phase's Friday prompt survives a cold re-ask plus adversarial follow-up without needing to reread that phase's notes first. Where something doesn't survive, that's real signal — go fix the underlying understanding, not just the answer.
