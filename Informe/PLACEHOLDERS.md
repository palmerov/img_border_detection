# Placeholders to fill with real results

After running the C++ variants and Intel Advisor, replace the following in the LaTeX files.

## 04-Experimental.tex

| Placeholder | Meaning | Example |
|-------------|---------|---------|
| `[PLACEHOLDER: machine description...]` | CPU, cores, RAM | Intel Core i7-XXXX, 8 cores, 16 GB RAM |
| `[PLACEHOLDER: image size...]` | Input image dimensions | 1024×1024 |
| `[PLACEHOLDER: e.g. median of 5 runs...]` | How times were aggregated | median of 5 runs |
| **T1** | Scalar execution time | 2.45 |
| **T2** | Auto execution time | 1.20 |
| **T3** | Guided (implicit) execution time | 1.10 |
| **T4** | Explicit (AVX2) execution time | 0.95 |
| `[e.g. ms]` | Time unit | ms or µs |
| **P1, P2, P3, P4** | Vectorization percent (Advisor) per variant | 0, 65, 80, 100 |
| **SPEEDUP_*** | T1/T2, T1/T3, T1/T4 | 2.04, 2.23, 2.58 |
| **X.X** (improvement explicit vs implicit) | e.g. "1.15×" or "15% faster" | 1.15× |

## 05-Conclusions.tex

- Replace the whole paragraph that starts with "For instance" using the real T1–T4 and the computed improvement **X.X** of explicit with respect to implicit.
- Replace "P1 for scalar... P4 for explicit" with the actual Advisor percentages.
- Adjust the interpretation sentences with your Advisor findings.

## main.tex (abstract)

- Replace: `**[Placeholder: fill with one-sentence summary of main result once data available.]**` with one sentence summarising the main result (e.g. speedup and best variant).

## Optional

- Add a real roofline or survey figure in `Figuras/` and uncomment the figure block in 04-Experimental.tex; set `\label{fig:roofline}` and refer to it in the text.
- Update author names and thanks in main.tex.
