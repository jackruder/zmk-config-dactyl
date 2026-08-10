/*
 * Unicode math / Greek / logic symbol macros for the MATH layer.
 *
 * Uses urob/zmk-unicode: `&uc CP_UNSHIFTED CP_SHIFTED`.
 * Extracted from ~/dev/nix/home/doom/config.el cdlatex-math-symbol-alist.
 *
 * Naming prefixes:
 *   G_ = Greek letter
 *   M_ = math operator / dot / prime / infinity
 *   S_ = set theory / logic
 *   A_ = arrow
 *   R_ = relation (≤ ≥ ≠ ≈ …)
 *   B_ = bracket (⟨ ⟩)
 *
 * Shifted variant (2nd &uc arg, or `0` if none) comes from the second
 * entry in each cdlatex alist cell where present, so `Shift+G_ALPHA`
 * produces ∀ (per `?A` → ∀), etc.
 */

#ifndef MATH_SYMBOLS_H
#define MATH_SYMBOLS_H

// ── Greek letters ───────────────────────────────────────────────────
#define G_ALPHA    &uc 0x03B1 0x2200   // α / ∀     (cdlatex ?a / ?A)
#define G_BETA     &uc 0x03B2 0        // β         (?b)
#define G_GAMMA    &uc 0x03B3 0x0393   // γ / Γ     (?g / ?G)
#define G_DELTA    &uc 0x03B4 0x0394   // δ / Δ     (?d / ?D)
#define G_EPS      &uc 0x03B5 0x2203   // ε / ∃     (?e / ?E)
#define G_ZETA     &uc 0x03B6 0x2124   // ζ / ℤ     (?z / ?Z)
#define G_ETA      &uc 0x03B7 0        // η         (?h)
#define G_THETA    &uc 0x03B8 0x0398   // θ / Θ     (?q / ?Q — cdlatex maps q→theta)
#define G_IOTA     &uc 0x03B9 0        // ι         (not in cdlatex; included for completeness)
#define G_KAPPA    &uc 0x03BA 0        // κ         (?k)
#define G_LAMBDA   &uc 0x03BB 0x039B   // λ / Λ     (?l / ?L)
#define G_MU       &uc 0x03BC 0        // μ         (?m)
#define G_NU       &uc 0x03BD 0        // ν         (ℕ moved to MBB layer as MB_N)
#define G_XI       &uc 0x03BE 0x039E   // ξ / Ξ     (?w / ?W — cdlatex maps w→xi)
#define G_OMICRON  &uc 0x03BF 0        // ο         (rare; not in cdlatex)
#define G_PI       &uc 0x03C0 0x03A0   // π / Π     (?p / ?P)
#define G_RHO      &uc 0x03C1 0x211D   // ρ / ℝ     (?r / ?R)
#define G_SIGMA    &uc 0x03C3 0x03A3   // σ / Σ     (?s / ?S)
#define G_TAU      &uc 0x03C4 0        // τ         (?t)
#define G_UPS      &uc 0x03C5 0x03A5   // υ / Υ     (?u / ?U)
#define G_PHI      &uc 0x03C6 0x03A6   // φ / Φ     (?f / ?F)
#define G_CHI      &uc 0x03C7 0        // χ         (?x)
#define G_PSI      &uc 0x03C8 0x03A8   // ψ / Ψ     (?y / ?Y — cdlatex maps y→psi)
#define G_OMEGA    &uc 0x03C9 0x03A9   // ω / Ω     (?o / ?O — cdlatex maps o→omega)

// ── Math operators / dots / primes ──────────────────────────────────
#define M_LDOTS    &uc 0x2026 0        // …         (?.)
#define M_CDOTS    &uc 0x22EF 0        // ⋯         (2nd of ?.)
#define M_PRIME    &uc 0x2032 0        // ′         (?')
#define M_DOT      &uc 0x22C5 0x00D7   // ⋅ / ×     (?* — center dot / times)
#define M_INFTY    &uc 0x221E 0        // ∞         (?8)
#define M_EMPTY    &uc 0x2205 0        // ∅         (?0)
#define M_NABLA    &uc 0x2207 0        // ∇         (2nd of ?n, also ?D)
#define M_PARTIAL  &uc 0x2202 0        // ∂         (2nd of ?d)
#define M_INT      &uc 0x222B 0        // ∫         (cdlatex "int")
#define M_SUM      &uc 0x2211 0        // ∑         (cdlatex "sum")
#define M_PROD     &uc 0x220F 0        // ∏
#define M_PM       &uc 0x00B1 0        // ±

// ── Set theory / logic ──────────────────────────────────────────────
#define S_IN       &uc 0x2208 0        // ∈         (cdlatex "in")
#define S_NOTIN    &uc 0x2209 0        // ∉         (cdlatex "notin")
#define S_SUBSET   &uc 0x2282 0x2286   // ⊂ / ⊆     (?{ )
#define S_SUPSET   &uc 0x2283 0x2287   // ⊃ / ⊇     (?})
#define S_UNION    &uc 0x222A 0        // ∪         (?+)
#define S_INTER    &uc 0x2229 0        // ∩
#define S_MINUS    &uc 0x2216 0        // ∖         (?\)
#define S_AND      &uc 0x2227 0        // ∧         (?&)
#define S_OR       &uc 0x2228 0        // ∨         (?v)
#define S_NOT      &uc 0x00AC 0        // ¬         (?!)
#define S_FORALL   &uc 0x2200 0        // ∀         (?A first)
#define S_EXISTS   &uc 0x2203 0        // ∃         (?E first)

// ── Arrows ──────────────────────────────────────────────────────────
#define A_LEFT     &uc 0x2190 0x27F5   // ← / ⟵     (?<)
#define A_RIGHT    &uc 0x2192 0x27F6   // → / ⟶     (?>)
#define A_UP       &uc 0x2191 0        // ↑         (?^)
#define A_DOWN     &uc 0x2193 0        // ↓         (?_)
#define A_MAPSTO   &uc 0x21A6 0x27FC   // ↦ / ⟼    (?|)
#define A_LDBL     &uc 0x21D0 0x27F8   // ⇐ / ⟸    (?[)
#define A_RDBL     &uc 0x21D2 0x27F9   // ⇒ / ⟹    (?])
#define A_IFF      &uc 0x21D4 0x27FA   // ⇔ / ⟺   (?=)

// ── Relations ───────────────────────────────────────────────────────
#define R_LEQ      &uc 0x2264 0        // ≤         (?<= in cdlatex)
#define R_GEQ      &uc 0x2265 0        // ≥         (?>=)
#define R_NEQ      &uc 0x2260 0        // ≠
#define R_APPROX   &uc 0x2248 0        // ≈         (2nd of ?~)
#define R_SIM      &uc 0x223C 0x2243   // ∼ / ≃     (?~)

// ── Brackets ────────────────────────────────────────────────────────
#define B_LANGLE   &uc 0x27E8 0        // ⟨         (?( )
#define B_RANGLE   &uc 0x27E9 0        // ⟩         (?))

#endif // MATH_SYMBOLS_H
