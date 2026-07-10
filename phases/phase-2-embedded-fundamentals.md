← [ROADMAP.md](../ROADMAP.md)

# Phase 2 — Embedded Fundamentals + Nucleo Bring-Up (Weeks 8-12)

**Goal:** Demystify hardware interfaces. The STM32 Nucleo enters here. Every peripheral is built as an interface (in `hal/include/`) with a mock backend (`hal/mock/`) *and* a real STM32 backend (`hal/stm32/`), learned side by side rather than sequentially — per the [HAL/Firmware Simulator architecture](../ROADMAP.md#the-hal--firmware-simulator-architecture).

For every peripheral this phase, apply Rule 5 before implementing: why does it exist, what problem does it solve, what alternatives exist, what are the trade-offs, what can fail.

Day themes as in [ROADMAP.md](../ROADMAP.md#weekly-schedule), with one adjustment: Saturday's "long project session" is the primary slot for Nucleo bring-up work (flashing, debugging with OpenOCD, oscilloscope/logic-analyzer-style verification if available), since it benefits from an uninterrupted block. Algorithms continue daily — this phase's focus: trees, DFS/BFS.

**Before Week 8 starts:** pick the specific Nucleo model (e.g., Nucleo-F446RE, Nucleo-G474RE) and confirm it's in hand, along with an ST-Link (usually onboard) and USB cable. Install `arm-none-eabi-gcc` and OpenOCD via Homebrew.

---

## Week 8 — Toolchain Bring-Up, GPIO, Timers

**Deliverables:**
- Cross-compilation toolchain working end-to-end: a minimal `blink.elf` built with `arm-none-eabi-gcc`, flashed via OpenOCD/ST-Link, LED visibly blinking via a bare super-loop. This is the "hello world" of the phase — don't move on until it works reliably.
- `IGpio` gains a real `hal/stm32/` backend (register-level, no vendor HAL abstraction layer yet — direct register manipulation to understand what's underneath). Mock and STM32 backends verified to satisfy the same interface.
- Replace the super-loop blink with a hardware timer-driven blink (no blocking delay). Note in `notes/embedded/` on PWM, capture/compare, and timer overflow.

**Friday architecture prompt:** "Why would you implement a HAL against raw registers first instead of starting with the vendor's HAL library (e.g., STM32 HAL/LL)?"

---

## Week 9 — UART

**Deliverables:**
- Polling UART driver against `IUart`, both backends (mock + STM32), tested.
- Rewritten as interrupt-driven with a ring buffer; note explaining why polling doesn't scale and what the ring buffer solves.
- Debug console (from the Vending Machine project) or a new minimal CLI running over real UART on the Nucleo, observed via a serial terminal on the Mac.

**Friday architecture prompt:** "What happens to a UART receive buffer if the application doesn't drain it fast enough, and how would you detect/handle that?"

---

## Week 10 — SPI and a Real Sensor

**Deliverables:**
- `ISpi` interface + mock backend + STM32 backend (master mode, chip-select handling).
- Communicate with a real SPI sensor or peripheral (whatever's available/cheap to acquire — e.g., an SPI-based accelerometer or flash chip) — read a real register/ID value over the bus and print it via UART.
- Note on SPI vs. UART trade-offs (clocked vs. asynchronous, addressing/CS, throughput).

**Friday architecture prompt:** "Compare SPI and I2C for a sensor that needs high sample rate — what would push you toward one or the other?"

---

## Week 11 — I2C and ADC

**Deliverables:**
- `II2c` interface + both backends: addressing, ACK/NACK, repeated start understood and demonstrated against a real I2C sensor.
- Note covering clock stretching, bus recovery, and timeout handling — what happens when an I2C bus hangs, and how firmware detects/recovers from it.
- `IAdc` (or extend an existing interface) + both backends: sample a real analog signal (e.g., a potentiometer or onboard sensor), and write a short experiment on sampling theory/aliasing (Nyquist) — undersample a known signal on purpose and observe the aliased result.

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

- `arm-none-eabi-gcc` + OpenOCD + ST-Link toolchain works reliably for build-flash-debug.
- `hal/` has real STM32 backends for GPIO, Timer, UART, SPI, I2C, ADC, all verified against the same interfaces as their mock counterparts.
- Comfortable explaining, unaided, how each protocol works and why it exists versus its alternatives.
- At least one deliberately-introduced concurrency bug (ISR/main-loop race) found and fixed with understanding, not guesswork.

Move to [Phase 3](phase-3-rtos.md) once these hold.
