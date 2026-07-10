← [ROADMAP.md](../ROADMAP.md)

# Phase 2 — Embedded Fundamentals + Nucleo Bring-Up (Weeks 8-12)

**Goal:** Demystify hardware interfaces. The STM32 Nucleo enters here. Every peripheral is built as an interface (in `hal/include/`) with a mock backend (`hal/mock/`) *and* a real STM32 backend (`hal/stm32/`), learned side by side rather than sequentially — per the [HAL/Firmware Simulator architecture](../ROADMAP.md#the-hal--firmware-simulator-architecture).

For every peripheral this phase, apply Rule 5 before implementing: why does it exist, what problem does it solve, what alternatives exist, what are the trade-offs, what can fail.

Day themes as in [ROADMAP.md](../ROADMAP.md#weekly-schedule), with one adjustment: Saturday's "long project session" is the primary slot for Nucleo bring-up work (flashing, debugging, oscilloscope/logic-analyzer-style verification if available), since it benefits from an uninterrupted block. Algorithms continue daily — this phase's focus: trees, DFS/BFS.

**Before Week 8 starts:** confirm the Nucleo (F401RE/F411RE/F446RE) is in hand, along with an ST-Link (usually onboard) and USB cable. Install `arm-none-eabi-gcc` (the cross-compiler — this one's not optional, it's the only thing in this toolchain that turns C++ into ARM machine code) via Homebrew, plus a flash/debug tool to get the compiled binary onto the board and connect a debugger — either **OpenOCD** (open source, integrates directly with GDB, this phase's default) or **STM32CubeProgrammer + ST-Link GDB server** (ST's own official tooling, often smoother on first bring-up, GUI available) — either is a legitimate choice for every "flash it" deliverable this phase; use whichever you get working first, and note in Week 8's toolchain-bring-up writeup which one and why.

---

## Week 8 — Toolchain Bring-Up, GPIO, Timers

First real hardware bring-up week — budget Monday through Wednesday for the cross-compilation toolchain alone if needed, before starting the timer/PWM material. First-time flashing setups are notoriously fiddly (driver issues, flash-tool config, ST-Link enumeration); getting stuck here is normal, not a sign of falling behind. Same permission as Phase 0: it's fine to take longer than a strict Mon-Tue split, as long as it's tracked explicitly (Rule 4) rather than silently slipping.

**Deliverables:**
- Toolchain bring-up (do this first, before anything else this week): a minimal `blink.elf` built with `arm-none-eabi-gcc`, flashed via OpenOCD or STM32CubeProgrammer (your call — see "Before Week 8 starts" above), LED visibly blinking via a bare super-loop. This is the "hello world" of the phase — don't move on until it works reliably.
- Once bring-up works: `Gpio` gains a real `hal/stm32/` backend (register-level, no vendor HAL abstraction layer yet — direct register manipulation to understand what's underneath). Mock and STM32 backends verified to satisfy the same interface.
- Replace the super-loop blink with a hardware timer-driven blink (no blocking delay). Note in `notes/embedded/` on PWM, capture/compare, and timer overflow.
- **Disassembly reading:** disassemble `blink.elf` (`arm-none-eabi-objdump -d`) and walk through the generated ARM Thumb-2 assembly for a small function by hand — identify the prologue/epilogue, how arguments are passed (AAPCS calling convention: `r0`-`r3`, stack for the rest), and how a register write maps back to the C statement that produced it. Note in `notes/embedded/` covering: what a stack frame looks like on Cortex-M, and one concrete example of a C construct (a loop, a struct field access) and its assembly.

**Friday architecture prompt:** "Why would you implement a HAL against raw registers first instead of starting with the vendor's HAL library (e.g., STM32 HAL/LL)?"

---

## Week 9 — UART

**Deliverables:**
- Polling UART driver against `Uart`, both backends (mock + STM32), tested.
- Rewritten as interrupt-driven with a ring buffer; note explaining why polling doesn't scale and what the ring buffer solves.
- Port `sensor-core`'s debug console/CLI (from Phase 1) onto real UART on the Nucleo — same command surface, now talking to `hal/stm32/`'s UART backend instead of the mock, observed via a serial terminal on the Mac.

**Friday architecture prompt:** "What happens to a UART receive buffer if the application doesn't drain it fast enough, and how would you detect/handle that?"

---

## Week 10 — SPI and a Real Sensor

**Deliverables:**
- `Spi` interface + mock backend + STM32 backend (master mode, chip-select handling).
- Communicate with a real SPI sensor (e.g., an SPI-based accelerometer) — read a real register/ID value over the bus and print it via `sensor-core`'s CLI (Week 9).
- Implement a concrete `Sensor` backend for this sensor (satisfying the `Sensor` interface from Phase 1 Week 5) so `sensor-core` can read it through the same abstraction it used for mock data — first real hardware plugged into the library built in Phase 1.
- Note on SPI vs. UART trade-offs (clocked vs. asynchronous, addressing/CS, throughput).

**Friday architecture prompt:** "Compare SPI and I2C for a sensor that needs high sample rate — what would push you toward one or the other?"

---

## Week 11 — I2C and ADC

**Deliverables:**
- `I2c` interface + both backends: addressing, ACK/NACK, repeated start understood and demonstrated against a real I2C sensor (e.g., a temperature/humidity sensor) — implemented as a second `Sensor` backend, so `sensor-core` now reads two independent real sensors through the same interface.
- Note covering clock stretching, bus recovery, and timeout handling — what happens when an I2C bus hangs, and how firmware detects/recovers from it.
- `Adc` (or extend an existing interface) + both backends: sample a real analog signal (e.g., a potentiometer or light sensor), wired in as a third `Sensor` backend. Write a short experiment on sampling theory/aliasing (Nyquist) — undersample a known signal on purpose and observe the aliased result.

**Friday architecture prompt:** "Why does I2C need pull-up resistors and open-drain outputs, and what problem does that design solve versus a push-pull bus like SPI?"

---

## Week 12 — Interrupts, Critical Sections, Phase Close-Out

**Deliverables:**
- Note on interrupt latency, priority, nested interrupts, critical sections, and memory barriers — grounded in what you've actually observed on the Nucleo this phase (e.g., measuring or reasoning about ISR entry/exit cost).
- Deliberately introduce and then fix a race condition between an ISR and main-loop code sharing a variable (e.g., missing `volatile` or missing critical section) — document what broke and why the fix works.
- Full `hal/` review: confirm GPIO, Timer, UART, SPI, I2C, ADC all have both mock and STM32 backends passing the same interface contract. Run `clang-tidy`/`clang-format` across everything added this phase.

**Friday architecture prompt:** full mock interview — "Walk me through the interrupt handling strategy for a sensor node reading three different buses. Where do critical sections go and why?"

**Sunday retro + Phase 2 close-out.**

---

## Algorithms (daily, weeks 8-12)

Focus: trees, basic graph traversal (DFS/BFS).

## Exit criteria for Phase 2

- `arm-none-eabi-gcc` + a working flash/debug tool (OpenOCD or STM32CubeProgrammer) + ST-Link toolchain works reliably for build-flash-debug.
- `hal/` has real STM32 backends for GPIO, Timer, UART, SPI, I2C, ADC, all verified against the same interfaces as their mock counterparts.
- `sensor-core` from Phase 1 now runs on the Nucleo, reading at least two real sensors (SPI + I2C) through concrete `Sensor` backends, with its CLI reachable over real UART. Still `sensor-core/` — no RTOS, no new project directory yet.
- Comfortable explaining, unaided, how each protocol works and why it exists versus its alternatives.
- At least one deliberately-introduced concurrency bug (ISR/main-loop race) found and fixed with understanding, not guesswork.
- Can read Cortex-M/ARM Thumb-2 disassembly for a simple function and explain the stack frame and calling convention, unaided.

Move to [Phase 3](phase-3-rtos.md) once these hold.
