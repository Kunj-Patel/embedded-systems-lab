← [ROADMAP.md](../ROADMAP.md)

# Phase 0 — Raw C Refresher (Weeks 1-2)

**Goal:** Rebuild core muscle memory — bits, pointers, memory layout — before introducing C++ or hardware complexity. Nothing here is new material; it's fluency work.

Day themes (see [ROADMAP.md](../ROADMAP.md#weekly-schedule) for the standing Mon-Sun pattern): Monday=Learn, Tuesday=Implement, Wednesday=Debug/break things, Thursday=Optimize/refactor, Friday=Architecture interview practice, Saturday=long project session, Sunday=retro. Algorithms practice (30-45 min) happens daily regardless of theme.

Repo location for this phase's work: `experiments/cpp/` and `algorithms/leetcode/`. No `projects/` or `hal/` work starts yet — that begins Phase 1.

---

## Week 1 — Bits and Pointers

**Deliverables by end of week:**
- A small `bitops` exercise set: set/clear/toggle/test individual bits and multi-bit fields on an unsigned integer, done without looking up bit-trick references.
- A pointer exercises file: pointer arithmetic across arrays, pointer-to-pointer, casting a raw buffer between `uint8_t*`/`uint16_t*`/`uint32_t*` and reasoning about the resulting byte layout.
- Written note in `notes/computer-science/` explaining, in your own words, why embedded code leans on bitfields/masks instead of arrays of bools.

**Friday architecture prompt:** "Why would a peripheral register be documented as a 32-bit word with named bitfields instead of 32 individual boolean flags?"

**Sunday retro:** answer the four standard retro questions (learned / confused / do differently / open questions) in `notes/`, dated.

---

## Week 2 — Memory Layout and Custom memcpy/memset

**Deliverables by end of week:**
- A short program that prints the addresses of a stack variable, a heap allocation, a global initialized variable, and a global uninitialized variable — and a note explaining which segment (stack/heap/data/BSS) each lives in and why.
- `experiments/memory/custom-memcpy/`: your own `memcpy` and `memset` implementations, correctness-tested against the standard library versions (same output for varied sizes/alignments), then benchmarked against them. Write up the experiment using the hypothesis → implementation → measurement → conclusion structure from [ROADMAP.md](../ROADMAP.md#repository-structure).
- Explain (out loud or in writing, per the Four Loops) why the standard library versions are faster or slower than yours, and what techniques (word-sized copies, alignment handling, `restrict`) account for the difference.

**Friday architecture prompt:** "A bootloader needs to copy a firmware image from flash to RAM before jumping to it. What has to be true about that copy for it to be safe?"

**Sunday retro + Phase 0 close-out:** confirm bit manipulation and pointer arithmetic feel automatic (no hesitation, no lookup) before moving to Phase 1. If not yet automatic, it is fine to extend Phase 0 by a few days rather than move on with a shaky foundation — flag this explicitly rather than silently falling behind schedule.

---

## Algorithms (daily, both weeks)

Focus: arrays and strings. Rebuild pointer/index fluency through problems, not just raw C exercises. Track solved problems in `algorithms/leetcode/`, one file or subfolder per problem, with a one-line note on the approach and complexity.

## Exit criteria for Phase 0

- Comfortable manipulating individual bits/bitfields without reference material.
- Comfortable with pointer arithmetic and type-punning a raw buffer.
- Can state, unprompted, which memory segment a given variable lives in.
- Custom `memcpy`/`memset` experiment complete with a written conclusion.

Move to [Phase 1](phase-1-modern-cpp.md) once these hold.
