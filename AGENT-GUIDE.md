# Agent Guide — How to Run This Bootcamp With an AI Agent

This file is the operating manual for using an AI coding agent (Claude Code or similar) alongside [ROADMAP.md](ROADMAP.md) and the [phases/](phases/) files. It answers two questions: which files to point the agent at, and exactly what to type at the start and end of every session. Read it once, then mostly just copy the prompts below.

---

## The three documents, and what each is for

- **[ROADMAP.md](ROADMAP.md)** — the whole-program view: mission, rules, pacing/calendar, repository structure, the `sensor-core`/`sensor-hub` architecture, and the 28-week table. You don't re-read this every session; the agent does, for context.
- **[phases/phase-N-*.md](phases/)** — the file for whichever phase you're currently in. This has the actual weekly deliverables, Friday prompts, and exit criteria you're working against right now.
- **This file (AGENT-GUIDE.md)** — how to actually run a session. Not a memory system by itself — see below for how state gets tracked.

**You do not have a separate progress-tracking file yet, and that's deliberate.** Progress lives in two places that already exist for other reasons: `git log` (what got built and when) and the dated retro notes in `notes/` (what you learned and decided each week, per Rule 4). The agent reconstructs "where am I" from those two sources every session — see the Start-of-Session prompt below. If this ever feels insufficient (e.g., you're losing track of which week you're on), that's a signal to add a lightweight `PROGRESS.md`, not a sign you're doing it wrong — but don't add one preemptively.

This only works if commits and retro notes follow a **consistent, greppable format** — that's the entire point of not having a separate tracker file. The next section, "The exact spec," is that format. Follow it precisely, not approximately, or the "reconstruct from git + notes" trick stops working.

---

## The exact spec: commits, retros, and daily notes

This section is a reference, not prose to read once — come back to it whenever you're not sure how to name something.

### Commit messages

This repo uses **[Conventional Commits](https://www.conventionalcommits.org/)** — the actual industry-standard format, not a bootcamp-specific invention — with the phase/week as the scope:

**Format:** `<type>(p<phase>w<week>): <short description>`

- `<type>` is one of the standard Conventional Commits types: `feat` (new functionality), `fix` (bug fixes — including deliberately-introduced-then-fixed bugs from Phase 2/3's concurrency exercises), `test` (tests added/changed), `refactor` (restructuring with no behavior change — Thursday's optimize/refactor work), `docs` (notes, README updates, retros), `perf` (a change specifically made to improve performance, with before/after numbers — Phase 5's DMA/cache/allocator work), `chore` (toolchain/build config, CI, formatting setup — Week 3 and Week 8's toolchain bring-up).
- `(p<phase>w<week>)` is the scope: phase number (0-6) and absolute week number (1-28), both straight from the current phase file's header — e.g. Phase 1 Week 4 is `(p1w4)`. This is the one project-specific convention layered on top of the standard, and it's what makes `git log` greppable by week.
- `<short description>` is a real, specific, imperative-mood description — not "progress" or "updates."
- This project doesn't use experiments/ writeups as their own commit type — an experiment's code and its `test` commits use `test` or `feat` as appropriate; the write-up itself (hypothesis → implementation → measurement → conclusion) is `docs`.

**Examples:**
```
test(p0w1): benchmark custom memcpy against stdlib
feat(p1w4): add IGpio, ILed, IButton interfaces and mock backend
test(p1w4): cover sensor-core state machine transitions
fix(p3w17): diagnose and fix deliberately-induced priority inversion
docs(p3w17): write CFSR/HFSR fault register note
refactor(p4w19): reorganize sensor-hub into drivers/kernel/middleware/application
perf(p5w21): add DMA-backed SPI transfer, cutting CPU time 40% vs interrupt-driven
chore(p1w3): scaffold CMake + GoogleTest + clang-format/tidy config
```

**Frequency — commit small and often, not once at the end of the day.** Rule 2 says "tiny commits," which means: one commit per logical unit of work (one interface implemented, one test file passing, one bug fixed), not one giant commit at day's end. A realistic day produces 2-5 commits. If you only ever make one commit per day, your commits are too big — split them. Never let uncommitted work span a session boundary if you can help it (see Session End step 1 in the section above) — an interrupted, uncommitted day is exactly the kind of gap the git-log-reconstruction trick can't recover from.

**What NOT to do:** don't commit broken/non-building code with intent to fix it "in the next commit" — each commit should leave the repo in a working state, per Rule 3's spirit. If you need to checkpoint genuinely broken in-progress work across a session boundary, say so explicitly to the agent next session rather than relying on it to infer that from a commit message.

### Retro notes (Rule 4 — weekly, process-level reflection)

**Location:** `notes/retros/YYYY-MM-DD-p<phase>-w<week>.md` — one file per week, named with the date the retro was written (not the week's start date) and the phase/week it closes out. Create the `notes/retros/` directory the first time you need it (per ROADMAP's "directories are created only when they contain meaningful work").

**Example filename:** `notes/retros/2026-08-16-p1-w4.md`

**Template — every retro file has exactly this structure:**

```markdown
# Week 4 Retro (Phase 1) — 2026-08-16

## What did I learn?


## What confused me?


## What would I do differently?


## What questions remain?


## Status
- [ ] All week deliverables complete
- [ ] Friday prompt(s) done under Mock Interview Discipline
- [ ] Exit criteria met (if this is a phase-closing week)

## Notes
(exam-week pause, schedule deviation, anything next session needs to know that isn't captured above)
```

**When to write one:** at the end of every week, once that week's deliverables are actually done — not necessarily on a calendar Sunday, since weeks are content units per the Pacing & Calendar section, not fixed calendar slots. If a week spans multiple calendar weeks (exam-week stretch, hardware delay), the retro still happens once, when the week's content actually closes.

**Answer the four questions yourself, in your own words, before or during the session — don't let the agent write these for you.** The agent's job is to ask the four questions one at a time and transcribe your answers into the file; if the agent starts drafting the answers, stop it and answer yourself. This file is the thing next session's agent reads to reconstruct "where you left off," and it's also the thing that makes the Post-Week-28 cumulative block and future interview prep actually work — a retro you didn't really write is worse than a short honest one.

### Daily/content notes (distinct from retros — don't conflate them)

Most weeks already specify content notes as part of that week's deliverables — e.g. "note in `notes/architecture/` on interfaces and dependency injection" (Phase 1 Week 4), "note in `notes/embedded/` on PWM, capture/compare, and timer overflow" (Phase 2 Week 8). These are **not** the retro — they're technical writeups answering Rule 5's "why does this exist, what problem does it solve" for a specific concept, and they live in the topic-specific subdirectory the phase file names (`notes/modern-cpp/`, `notes/embedded/`, `notes/architecture/`, `notes/computer-science/`, `notes/reliability/`), not in `notes/retros/`.

**Naming for content notes:** `notes/<topic>/<short-topic-slug>.md` — e.g. `notes/architecture/dependency-injection.md`, `notes/embedded/pwm-and-timers.md`. No date prefix needed on these (unlike retros) since they're reference material you may revisit and edit, not a dated log entry — but do add a one-line "last updated" note at the top if you substantially revise one later (e.g. after Week 6 generalizes the Week 4 DI note into full SOLID).

**Do you need to write something every single session, even on days with no named "note" deliverable?** No — only write a content note when the phase file's deliverables for that day/week actually call for one. Don't manufacture a note just to have something to commit; an empty ritual note is worse than no note, and it clutters what should be a small, high-signal set of writeups you'd actually want to hand an interviewer.

### Quick reference: what goes where

| Thing | Location | Cadence |
|---|---|---|
| Code, tests, experiments | `hal/`, `projects/`, `experiments/`, `algorithms/leetcode/` | Committed continuously, small commits |
| Commit messages | N/A (git history) | `type(p<n>w<n>): description`, every logical unit of work |
| Weekly retro (process) | `notes/retros/YYYY-MM-DD-p<n>-w<n>.md` | Once per week, when that week's deliverables close |
| Content notes (technical) | `notes/<topic>/<slug>.md` | Only when a deliverable specifically calls for one |
| LeetCode tracking | `algorithms/leetcode/README.md` + one file/problem | Per the Algorithm Interview Prep system in ROADMAP.md |

---

## Session start: exactly what to do

**1. Before opening the agent, orient yourself for 30 seconds:** which phase file are you in, roughly which week. If you don't remember, that's fine — the agent will figure it out in step 2.

**2. Open the agent in this repo's root directory** and paste this:

> I'm resuming my embedded systems bootcamp. Read ROADMAP.md, then check `git log --oneline -20` (commit messages are Conventional Commits scoped `(p<phase>w<week>)`, per AGENT-GUIDE.md) and look for the most recent file under `notes/retros/` to figure out which week I'm currently on and what's already done. Then read the specific phase file for that week. Tell me: what week I'm on, what's already complete this week (if anything, based on this week's commit scopes), and what today's deliverable is per the Mon-Sun day theme in ROADMAP.md's Weekly Schedule. Don't start writing code yet — just orient me first.

**First session only:** if `git log` shows no bootcamp commits (Conventional Commits scoped `(p0w1)` or later) and `notes/retros/` doesn't exist yet, there's nothing to reconstruct — that means Week 1 Day 1 hasn't started. The agent should say so directly and read [phases/phase-0-raw-c.md](phases/phase-0-raw-c.md) to orient on Monday-Tuesday's deliverables, rather than guessing or asking you which week you're on.

**3. Confirm or correct.** The agent will guess your current week from evidence; if it's wrong (e.g., you took a pause and didn't log it, per the exam-week protocol in ROADMAP.md's Pacing & Calendar section), just tell it directly: "I'm actually on Week N, Wednesday."

**4. Start the day's actual work.** Once oriented, prompt naturally for whatever the day's deliverable is — you don't need a special format, just talk to it like you would about any coding task, e.g. "let's build the RAII exercise for today" or "help me debug why ctest isn't finding my test binary." The agent already has the phase file loaded from step 2, so it knows the day's deliverables and Rule 5 framing without you re-explaining them.

**One thing worth naming explicitly if it's an exam week or a lighter day (semester pacing):** tell the agent up front — "this is a lighter day, I only have an hour" — so it scopes the session instead of assuming a full day's deliverable is happening.

---

## Session end: exactly what to do

**1. Commit as you go, not just once at the end.** Each time you finish a logical unit of work (an interface implemented, a test passing, a bug fixed), prompt:

> Let's commit this. Use Conventional Commits format `type(p<phase>w<week>): description` per AGENT-GUIDE.md's commit spec — figure out the right type (feat/fix/test/refactor/docs/perf/chore) from what we actually did.

A normal day should produce several of these, not one. See **Commit messages** under "The exact spec" above for the full format and examples.

**2. If today closed out a week (whenever that week's deliverables are actually done — not necessarily a calendar Sunday), do the retro.** Prompt:

> It's retro time for Week N (Phase P). Ask me the four standard questions — what I learned, what confused me, what I'd do differently, what questions remain — one at a time. I'll answer them myself; don't draft answers for me. Once I've answered all four, write them into notes/retros/ using today's date and the p<phase>-w<week> naming from AGENT-GUIDE.md's retro spec, using the exact template there.

The agent should ask you the questions interactively and transcribe, not generate the answers — the retro is only useful if it's your actual reflection. See **Retro notes** under "The exact spec" above for the exact filename format and template.

**3. If this was an exam-week pause or a partial/interrupted session** (per ROADMAP.md's exam-week protocol), log it explicitly:

> Log that we paused/shortened this week for [reason] in the retro note, so next session's agent knows this wasn't silently skipped.

**4. If you hit a Friday architecture prompt, mock interview, or live-coding rep today**, make sure it actually happened under the discipline described in ROADMAP.md's Mock Interview Discipline section (timed, spoken not typed, one adversarial follow-up) — not just discussed casually. If you ran it properly, note briefly in the retro what fell apart under the follow-up question; that's the part worth remembering next time you hit a similar prompt.

**5. Close with a one-line status check**, useful mostly so you don't have to reconstruct it next session from scratch:

> Summarize in 2-3 sentences: what we finished today, what's left for this week, and what the next session should start with.

You don't need to save this anywhere — it's for your own head on the way out, and next session's Start-of-Session prompt will reconstruct the same picture from git + notes anyway.

---

## Mid-week utility prompts

A few prompts worth having on hand for common situations, not tied to session start/end specifically:

- **Stuck on a toolchain problem (Phase 0/1 Week 3, Phase 2 Week 8):** "I'm stuck on [specific error]. Before fixing it for me, ask me what I've already tried and what I think is happening — I want to debug this myself with guidance, not have it handed to me." (Rule 6 — understanding over memorization.)
- **Want the agent to check pacing:** "Are we on track for this phase, or has this week been running long? Check against ROADMAP.md's Pacing & Calendar section and tell me honestly."
- **Starting a new phase:** "I think I'm done with Phase N — check the exit criteria in the phase file against what actually exists in the repo (code, tests, notes) and tell me honestly if I'm ready to move to Phase N+1, or what's actually missing."
- **Requesting the Friday prompt cold:** "Give me today's Friday architecture prompt from the current phase file, but don't show me the phase file's answer/context first — I want to attempt it cold, per Mock Interview Discipline."
- **Cumulative review block (after Week 28):** "Let's run the Post-Week-28 cumulative mock interview block from phase-6-capstone.md — pull today's sample prompts cold, per the block's Day N structure."

---

## What NOT to do

- **Don't paste the entire ROADMAP.md or a phase file into the chat manually.** Just tell the agent to read the file — it can read markdown directly from the repo, and pasting invites the file going stale relative to what's actually on disk.
- **Don't let the agent silently invent new deliverables or projects.** If a session's conversation surfaces a good idea that isn't in the current phase file, that's a roadmap edit to make deliberately (and review before committing) — not something to just start building off-plan.
- **Don't skip the retro because "nothing interesting happened."** A one-line retro ("solid day, no surprises") is still worth having — it's what next session's agent uses to confirm you're on schedule.
- **Don't treat "the agent said I'm ready for the next phase" as sufficient on its own** for the two full-mock-interview phase-transition weeks (end of Phase 1, Phase 2, Phase 3, Phase 4) — those exit criteria include things like "comfortable explaining X unaided," which only you can actually verify by trying it, not something the agent can confirm by reading your code.
