← [ROADMAP.md](../ROADMAP.md)

# Phase 0 — C Fluency Validation Gate (Week 1)

**Goal:** Confirm bit manipulation, pointer arithmetic, and memory-layout reasoning are truly automatic before starting modern C++ — not to teach this material, since two years of professional STM32 firmware work in C already covers it. This phase is a fast checkpoint, not a curriculum. If anything below genuinely surfaces a gap, that's real signal and worth spending real time on; if it's all fluent (expected), move on without guilt.

Repo location for this week's work: `experiments/cpp/` and `algorithms/leetcode/`. No `projects/` or `hal/` work starts yet — that begins Phase 1.

---

## Week 1 — Validation Gate

**Monday-Tuesday: self-check, no reference material.**
- Timed, no-lookup: bit set/clear/toggle/test on a multi-bit field, pointer arithmetic across a 2D array, casting a raw buffer between `uint8_t*`/`uint16_t*`/`uint32_t*` and reasoning about resulting byte layout, and stating from memory which segment (stack/heap/data/BSS) a given variable lives in. If every one of these is immediate and correct: done, move to Wednesday's stretch exercise. If something genuinely hesitates: spend the rest of the day closing that specific gap, not the whole topic.
- `experiments/memory/custom-memcpy/`: your own `memcpy`/`memset`, correctness-tested against the standard library versions, benchmarked, with a short hypothesis → implementation → measurement → conclusion writeup on why the standard library versions are faster or slower (word-sized copies, alignment handling, `restrict`). This one's worth keeping even at fluency, since the benchmarking/writeup discipline (not the C itself) is the actual skill being reinforced, and it's referenced again in Phase 5's bootloader work.

**Wednesday: architecture-level stretch, since the mechanics are assumed solid.** Answer, in writing: "A piece of startup code needs to copy a firmware image from flash to RAM before the rest of the program can safely run. What has to be true about that copy for it to be safe — alignment, overlap, size? What would you check in a code review of that routine?" This is the same question a bootloader review would raise (Phase 5) — answering it now from professional instinct, not new instruction.

**Thursday onward:** move directly into [Phase 1](phase-1-modern-cpp.md). The two days reclaimed here are spent in Phase 1's new Week 2 on the material this background doesn't already cover — modern C++ and the toolchain.

**Sunday retro:** short — confirm the gate held (or note specifically what didn't and how it was closed), dated in `notes/`.

---

## Algorithms (daily)

Focus: arrays and strings, same as the rest of the roadmap's daily practice — this isn't new, it's the standing habit starting immediately. Track in `algorithms/leetcode/` per the [Algorithm Interview Prep](../ROADMAP.md#algorithm-interview-prep) system.

## Exit criteria for Phase 0

- Bit manipulation, pointer arithmetic, and memory-segment reasoning confirmed automatic (or a specific gap identified and closed) — with evidence, not assumption, since "I already know this" is exactly the claim this gate exists to check.
- Custom `memcpy`/`memset` experiment complete with a written conclusion.

Move to [Phase 1](phase-1-modern-cpp.md) once these hold — expected by Wednesday or Thursday of Week 1, not Week 2.
