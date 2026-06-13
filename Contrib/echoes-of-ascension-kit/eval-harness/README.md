# UE5 Code-Gen Eval Harness

Measures how often your local model produces **real UE 5.7 APIs vs. hallucinated ones** on a fixed set of UE5/GAS coding tasks. Run it before/after a system-prompt or model change to see whether hallucinations actually drop — instead of guessing.

This exists because a 35B local model's #1 failure on UE5 is confidently inventing class/macro/function names. You can't fix what you don't measure; this gives you a number.

## How it works

`tasks.json` is a list of UE5 coding tasks. Each asserts:
- **`must_include`** — real APIs a correct answer uses (all must appear).
- **`must_not_include`** — known hallucinations / legacy patterns (none may appear), e.g. `UGameplayAbilityComponent`, `ASC->GetLevel()`, `AttachTo(`, `EvaluatedAttributes.ContainsAttribute`, `TargetInfo`, `EnginePrivate.h`.

A task **passes** only if every `must_include` is present and no `must_not_include` is. The runner prints a per-task PASS/FAIL, an overall score, and a frequency count of which APIs got hallucinated.

## Run it

```bash
# against your TurboHaul instance (defaults)
python ue5_eval.py

# or point it anywhere OpenAI-compatible
EVAL_ENDPOINT=http://127.0.0.1:11401/v1/chat/completions \
EVAL_MODEL=turbohaul-carnice \
python ue5_eval.py -v        # -v also prints each model output
```

Env vars: `EVAL_ENDPOINT`, `EVAL_MODEL`, `EVAL_KEY` (often empty for local), `EVAL_SYSTEM` (the system prompt to test — try your `ue5-coder` profile prompt here).

## Interpreting

- **Score** = tasks passed / total. Track it over time.
- **Hallucinated APIs (frequency)** = your model's specific failure modes. These become `must_not_include` rules in your `ue5-coder` profile prompt (see `../hermes-skill/PROFILE-PROMPTS.md`), or things your review checks first.
- A task can fail two ways: `missing` (didn't use the right API — may just be a different valid approach, tighten the prompt) vs `HALLUCINATED` (used a fake/legacy API — the real problem).

## Validated

This harness was run against a reference local model (a Qwen3.6-27B on vLLM) during authoring — it scored **5/8**, with the 27B missing `GAMEPLAYATTRIBUTE_REPNOTIFY`, `FDefaultGameModuleImpl`, and `SetupAttachment`. So the harness works and the tasks discriminate. Run it on your Carnice 35B for your baseline, then add the `must_not_include` of whatever it hallucinates.

## Extending

Add a task: append an object to `tasks.json` with `id`, `category`, `prompt`, `must_include`, `must_not_include`. Substring match, case-sensitive (use a trailing `(` to avoid prefix collisions, e.g. `AttachTo(` won't match `AttachToComponent`).
