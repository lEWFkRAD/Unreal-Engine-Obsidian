#!/usr/bin/env python3
"""
UE5 code-gen eval harness — measures how often a local model produces REAL UE 5.7 APIs
vs. hallucinated ones, on a fixed set of UE5/GAS coding tasks.

Each task asserts:
  must_include      — real APIs that a correct answer uses (all must appear)
  must_not_include  — known hallucinations / legacy patterns (none may appear)

A task PASSES only if every must_include is present AND no must_not_include is.

Point it at any OpenAI-compatible endpoint. Defaults target a local TurboHaul instance;
override with env vars. Run before/after a system-prompt change to see if hallucinations drop.

  ENV:
    EVAL_ENDPOINT  (default http://127.0.0.1:11401/v1/chat/completions)
    EVAL_MODEL     (default turbohaul-carnice)
    EVAL_KEY       (default "" — many local servers need none)
    EVAL_SYSTEM    (optional system prompt to test; default a neutral UE5 coder prompt)

  Usage:  python ue5_eval.py            # run all tasks, print scorecard
          python ue5_eval.py -v         # also print each model output
"""
import json, os, sys, urllib.request

HERE = os.path.dirname(os.path.abspath(__file__))
ENDPOINT = os.environ.get("EVAL_ENDPOINT", "http://127.0.0.1:11401/v1/chat/completions")
MODEL    = os.environ.get("EVAL_MODEL", "turbohaul-carnice")
KEY      = os.environ.get("EVAL_KEY", "")
SYSTEM   = os.environ.get("EVAL_SYSTEM",
    "You are a senior Unreal Engine 5.7 C++ programmer. Use only real UE 5.7 APIs. Output only code.")
VERBOSE  = "-v" in sys.argv

def call(prompt):
    body = {"model": MODEL, "temperature": 0.2, "max_tokens": 1200,
            "messages": [{"role": "system", "content": SYSTEM},
                         {"role": "user", "content": prompt}]}
    headers = {"Content-Type": "application/json"}
    if KEY:
        headers["Authorization"] = "Bearer " + KEY
    req = urllib.request.Request(ENDPOINT, data=json.dumps(body).encode(), headers=headers)
    with urllib.request.urlopen(req, timeout=180) as r:
        return json.load(r)["choices"][0]["message"]["content"]

def grade(out, task):
    missing = [s for s in task["must_include"] if s not in out]
    hallucinated = [s for s in task["must_not_include"] if s in out]
    return (not missing and not hallucinated), missing, hallucinated

def main():
    tasks = json.load(open(os.path.join(HERE, "tasks.json"), encoding="utf-8"))
    print(f"endpoint: {ENDPOINT}\nmodel:    {MODEL}\ntasks:    {len(tasks)}\n" + "-"*64)
    results, passed = [], 0
    all_hallucinations = []
    for t in tasks:
        try:
            out = call(t["prompt"])
        except Exception as e:
            print(f"[ERROR] {t['id']}: {e}")
            results.append({"id": t["id"], "ok": False, "error": str(e)})
            continue
        ok, missing, hallucinated = grade(out, t)
        passed += ok
        all_hallucinations += hallucinated
        mark = "PASS" if ok else "FAIL"
        detail = ""
        if missing:      detail += f"  missing={missing}"
        if hallucinated: detail += f"  HALLUCINATED={hallucinated}"
        print(f"[{mark}] {t['id']:<32}{detail}")
        if VERBOSE:
            print("    " + out.replace("\n", "\n    ")[:1500] + "\n")
        results.append({"id": t["id"], "ok": ok, "missing": missing, "hallucinated": hallucinated})
    print("-"*64)
    print(f"SCORE: {passed}/{len(tasks)} passed  ({100*passed//max(len(tasks),1)}%)")
    if all_hallucinations:
        from collections import Counter
        print("Hallucinated APIs (frequency):", dict(Counter(all_hallucinations)))
    json.dump(results, open(os.path.join(HERE, "results.json"), "w"), indent=2)
    print("Wrote results.json")

if __name__ == "__main__":
    main()
