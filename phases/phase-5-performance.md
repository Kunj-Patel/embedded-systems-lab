← [ROADMAP.md](../ROADMAP.md)

# Phase 5 — Performance Engineering (Weeks 21-24)

**Goal:** Measure, analyze, and optimize firmware execution. Nothing in this phase is optimized without first being measured — guessing at bottlenecks is explicitly against the spirit of this phase.

Day themes as in [ROADMAP.md](../ROADMAP.md#weekly-schedule). No algorithms track this phase — the daily practice budget shifts to performance experiments instead.

---

## Week 21 — DMA

**Deliverables:**
- Add DMA support to `hal/` for SPI and/or UART (extend the relevant interface or add a new one), both mock and STM32 backends.
- Experiment in `experiments/performance/`: measure CPU time spent servicing SPI transfers via polling vs. interrupt vs. DMA, for a fixed transfer size. Hypothesis → implementation → measurement → conclusion.
- Note on what DMA actually offloads and what it doesn't (setup/teardown cost, cache coherency considerations even on a Cortex-M without a data cache in most cases — verify for your specific chip).

**Friday architecture prompt:** "When is DMA not worth the complexity versus a well-written interrupt handler?"

---

## Week 22 — Memory and Cache Behavior

**Deliverables:**
- Experiment: measure the cost of a cache-unfriendly memory access pattern (e.g., strided array access) versus a sequential one, on both the Mac (host, for intuition) and the Nucleo (if it has a cache — note if it doesn't, and what that implies).
- Implement a simple memory pool (fixed-size block allocator) and compare against `malloc`/`new` for allocation latency and fragmentation behavior — relevant because dynamic allocation is often avoided in real embedded systems.
- Note on why zero-copy design matters for a data logger (previewing Week 23's project).

**Friday architecture prompt:** "Why do many embedded style guides ban dynamic allocation after initialization, and what do you use instead?"

---

## Week 23 — High-Speed Data Logger Project (Part 1)

**Deliverables:**
- **Project start — High-Speed Data Logger (`projects/high-speed-data-logger/`):** DMA-driven SPI sensor capture into a circular buffer, using the DMA support built in Week 21.
- SD card write path implemented (via SPI or SDIO, whichever the Nucleo/board supports), with CRC validation on written blocks.
- Initial throughput/latency measurement: how much data can you reliably capture and persist per second before drops occur?

**Friday architecture prompt:** "Design the circular buffer sizing and backpressure strategy for a logger that must never silently drop samples."

---

## Week 24 — Data Logger Part 2, Compiler/Linker, Phase Close-Out

**Deliverables:**
- Power-loss recovery: simulate a power cut mid-write and verify the logger can detect/recover a consistent state on next boot (this is where CRC validation gets exercised for real).
- Note + experiment on compiler optimization flags (`-O0` vs `-O2`/`-O3`), LTO, and reading a `.map` file to understand binary size and where flash/RAM is going.
- Final measurement pass on the Data Logger: latency, throughput, memory usage, CPU usage — written up in the project README to the Rule 7 bar.

**Friday — full mock interview:** "Walk me through how you validated this logger doesn't lose or corrupt data, including the power-loss case."

**Sunday retro + Phase 5 close-out.**

---

## Exit criteria for Phase 5

- DMA working in `hal/` (both backends) and its actual benefit measured, not assumed.
- Comfortable reading a linker `.map` file and explaining where binary size/RAM usage comes from.
- High-Speed Data Logger project complete with measured throughput/latency and demonstrated power-loss recovery.
- Can explain the memory-pool-vs-dynamic-allocation trade-off with real numbers from this phase's experiments, not just theory.

Move to [Phase 6](phase-6-capstone.md) once these hold.
