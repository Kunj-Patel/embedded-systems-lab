← [ROADMAP.md](../ROADMAP.md)

# Phase 5 — Performance Engineering (Weeks 21-24)

**Goal:** Measure, analyze, and optimize firmware execution. Nothing in this phase is optimized without first being measured — guessing at bottlenecks is explicitly against the spirit of this phase. This phase also lays the bootloader foundation the capstone will build on — a bootloader is fundamentally a linker-script/memory-layout problem, so it belongs right alongside this phase's compiler/linker material, not crammed into Phase 6 alongside three other new subsystems.

Day themes as in [ROADMAP.md](../ROADMAP.md#weekly-schedule). No algorithms track this phase — the daily practice budget shifts to performance experiments instead.

---

## Week 21 — DMA

**Deliverables:**
- Add DMA support to `hal/` for SPI and/or UART (extend the relevant interface or add a new one), both mock and STM32 backends.
- Experiment in `experiments/performance/`: measure CPU time spent servicing SPI transfers via polling vs. interrupt vs. DMA, for a fixed transfer size. Hypothesis → implementation → measurement → conclusion.
- Note on what DMA actually offloads and what it doesn't (setup/teardown cost, cache coherency considerations even on a Cortex-M without a data cache in most cases — verify for your specific chip).
- Implement a simple memory pool (fixed-size block allocator) and compare against `malloc`/`new` for allocation latency and fragmentation behavior — grouped with this week's DMA/zero-copy material since avoiding dynamic allocation on a hot data path is the same instinct as avoiding unnecessary copies.

**Friday architecture prompt:** "When is DMA not worth the complexity versus a well-written interrupt handler?"

---

## Week 22 — Memory, Linker Scripts, and a Minimal Bootloader

**Deliverables:**
- Experiment: measure the cost of a cache-unfriendly memory access pattern (e.g., strided array access) versus a sequential one, on both the Mac (host, for intuition) and the Nucleo (if it has a cache — note if it doesn't, and what that implies).
- Note + experiment on compiler optimization flags (`-O0` vs `-O2`/`-O3`), LTO, and reading a `.map` file to understand binary size and where flash/RAM is going — do this now, since it's the same skill the bootloader work below depends on.
- **Bootloader foundation:** write a linker script defining two regions in flash — a bootloader region and an application region — and a minimal bootloader that verifies (checksum/CRC) and jumps to the application image. This directly reuses the memory-segment reasoning and the custom `memcpy` experiment from Phase 0 (copying/relocating an image is the same problem at a larger scale).

**Friday architecture prompt:** "What has to be true about the jump from bootloader to application code for it to be safe — what could go wrong with the vector table or stack pointer if you get it wrong?"

---

## Week 23 — Hardening `sensor-hub`'s Logger: DMA + Circular Buffer

**Deliverables:**
- **Project — hardening `projects/sensor-hub/`'s Logger task:** replace its current naive UART/SD writes (from Phase 3) with a DMA-driven capture path into the `RingBuffer<T, N>` template (originally from `sensor-core`, Phase 1), using the DMA support built in Week 21. This is the same Logger task that's been running since Phase 3 — it's being upgraded, not replaced or duplicated in a separate project.
- SD card write path implemented (via SPI or SDIO, whichever the Nucleo/board supports), with CRC validation on written blocks.
- Initial throughput/latency measurement: how much data can the upgraded Logger task reliably capture and persist per second before drops occur, compared against the pre-upgrade baseline from Phase 3?

**Friday architecture prompt:** "Design the circular buffer sizing and backpressure strategy for a logger task that must never silently drop samples, running alongside the sensor and watchdog tasks from Phase 3."

---

## Week 24 — Power-Loss Recovery, Phase Close-Out

**Deliverables:**
- Power-loss recovery: simulate a power cut mid-write and verify the Logger task can detect/recover a consistent state on next boot (this is where CRC validation gets exercised for real, and where the bootloader's image-verification logic from Week 22 gets its first real stress test).
- Final measurement pass on the upgraded Logger task: latency, throughput, memory usage, CPU usage — written up in the `sensor-hub` README as an update to the existing project documentation (Rule 7 bar).

**Friday — full mock interview:** "Walk me through how you validated this logger doesn't lose or corrupt data, including the power-loss case, and how that connects to the bootloader's image-verification strategy."

**Sunday retro + Phase 5 close-out.**

---

## Exit criteria for Phase 5

- DMA working in `hal/` (both backends) and its actual benefit measured, not assumed.
- A working minimal bootloader (verify + jump) with a documented linker-script memory layout — this is what Phase 6 extends with OTA.
- Comfortable reading a linker `.map` file and explaining where binary size/RAM usage comes from.
- `sensor-hub`'s Logger task now uses DMA + circular buffer + SD + CRC, with measured throughput/latency and demonstrated power-loss recovery — still the same project, now hardened.
- Can explain the memory-pool-vs-dynamic-allocation trade-off with real numbers from this phase's experiments, not just theory.

Move to [Phase 6](phase-6-capstone.md) once these hold.
