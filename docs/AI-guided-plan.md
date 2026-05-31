# RANSAC Web App: MVP Execution Plan

This document outlines the strategy to transform the RANSAC Linear Surplus Finder into a shipped deliverable, applying the "Minimum Viable Ugly" (MVU) principle to avoid the "pure learning" procrastination trap.

---

## 1. Core Philosophy: The "One Thing" Rule

The application must do **exactly one thing** well:

> **Find a linear surrogate using RANSAC.**

### Strict Constraints (Scope Guardrails)

- **NO** curve fitting, polynomial regression, or clustering.
- **NO** Excel (`.xlsx`) or LibreOffice importers yet.
  - **MVP Data Import:** CSV only. Hardcode the parser. Ignore headers. If malformed, crash with a clear error.
  - **Reasoning:** Excel parsing requires heavy libraries that bloat the WASM binary and delay shipping. CSV is trivial in C++.
- **NO** user accounts, cloud storage, or complex authentication.

---

## 2. Architecture: The "Bridge" Strategy

Minimize friction between the C++ core and the Rust/WASM frontend.

| Layer | Technology | Responsibility |
|-------|------------|----------------|
| **Core Logic** | C++ | Input: `std::vector<double>` (x, y pairs); Logic: RANSAC implementation (sampling, thresholding); Output: `struct { slope, intercept, inlier_indices }`; Build: Compile to `.wasm` via `emscripten` |
| **Bridge** | Rust | Use `wasm-bindgen` to expose C++ functions; Handle CSV parsing (use `csv` crate); Manage application state |
| **GUI** | egui | Visuals: Plot raw points (gray) + fitted line (red); Controls: Sliders for `Threshold` and `Iterations`; Interaction: Real-time redraw on slider change |

---

## 3. The "Ugly" MVP Roadmap (14-Day Sprint)

**Goal:** Ship a working binary, not a perfect product.

### Phase 1: The "Hello World" of RANSAC (Days 1–3)

- **Goal:** Command-line C++ program with hardcoded points printing `y = mx + c`.
- **Deliverable:** Compiled binary outputting the correct line equation.
- **⚠️ Procrastination Check:** If this takes >1 day, you are over-engineering the math. Use a standard ~50-line RANSAC algorithm.

### Phase 2: The WASM Bridge (Days 4–6)

- **Goal:** Compile C++ to WASM and call it from a bare HTML file via JavaScript.
- **Deliverable:** HTML page logging the RANSAC result to the console.
- **Key Tech:** `emscripten` flags (`-s WASM=1`, `-s EXPORTED_FUNCTIONS`).

### Phase 3: The Rust/egui Shell (Days 7–10)

- **Goal:** Running `egui` app in the browser with a "Run RANSAC" button and a canvas drawing dots.
- **Deliverable:** Visual interface.
- **Tip:** Use the `egui_plot` crate. **Do not** write a plotting engine from scratch.

### Phase 4: Integration & CSV (Days 11–14)

- **Goal:** Connect CSV Parser (Rust) → C++ RANSAC → `egui` Plot.
- **Deliverable:** Upload CSV → See points → Click "Calculate" → See line → Adjust sliders → Line updates.
- **🏁 The Finish Line:** Once this works, **STOP**. Do not add Excel, PDF export, or user accounts.

---

## 4. Anti-Procrastination Tactics for This Stack

| Trap | Risk | Mitigation Strategy |
|------|------|---------------------|
| **WASM Size** | Optimizing binary size too early slows builds. | Accept a **5MB–10MB** binary for v1. Optimize later. |
| **Math Perfection** | Tweaking RANSAC probability to be "statistically perfect." | Use standard params (e.g., 1000 iterations, 0.99 confidence). If it works on test data, it's done. |
| **UI Polish** | Spending days on colors, fonts, or responsive layout. | Use `egui`'s **default theme**. "Developer-ish" is acceptable for v1. |

---

## 5. Definition of Done (Checklist)

You are finished when **ALL** boxes are checked:

- [ ] **Import:** Can drag-and-drop a CSV file into the browser.
- [ ] **Visualize:** Graph renders points immediately upon load.
- [ ] **Calculate:** Clicking "Calculate" draws a red line.
- [ ] **Interact:** Moving the "Threshold" slider updates the line in real-time.
- [ ] **Deploy:** Code is pushed to a public GitHub repo.
- [ ] **Document:** Repo includes a `README.md` with a screenshot and "How to run" instructions.

---

## 6. Why This Works

This project forces **shipping** by:

1. Leveraging **C++** for heavy lifting (applying your learning).
2. Using **Rust/WASM** for modern delivery.
3. Using **egui** for rapid UI development (avoiding frontend framework hell).
4. **Scoping** strictly to one algorithm to prevent scope creep.

### 🚀 Immediate First Step

1. Create a GitHub repo: `ransac-web`.
2. Create `src/main.cpp` with a hardcoded vector of points and a `calculate_line()` function.
3. Compile it locally.

**That is your first deliverable.**

---

## 7. Next Steps

Need a quick checklist for setting up the `emscripten` toolchain? Let me know.