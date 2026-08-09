/*
 * Mathematical Double-Struck (\mathbb / "blackboard bold") uppercase.
 *
 * Where a double-struck letter exists in the Letterlike Symbols block
 * (C, H, N, P, Q, R, Z), we use that codepoint for best font support.
 * All others come from the Mathematical Alphanumeric Symbols block.
 *
 * Usage: `MB_A` … `MB_Z`. Uppercase-only.
 */

#ifndef MATH_DOUBLESTRUCK_H
#define MATH_DOUBLESTRUCK_H

#define MB_A   &uc 0x1D538 0    // 𝔸
#define MB_B   &uc 0x1D539 0    // 𝔹
#define MB_C   &uc 0x2102  0    // ℂ  (letterlike)
#define MB_D   &uc 0x1D53B 0    // 𝔻
#define MB_E   &uc 0x1D53C 0    // 𝔼
#define MB_F   &uc 0x1D53D 0    // 𝔽
#define MB_G   &uc 0x1D53E 0    // 𝔾
#define MB_H   &uc 0x210D  0    // ℍ  (letterlike)
#define MB_I   &uc 0x1D540 0    // 𝕀
#define MB_J   &uc 0x1D541 0    // 𝕁
#define MB_K   &uc 0x1D542 0    // 𝕂
#define MB_L   &uc 0x1D543 0    // 𝕃
#define MB_M   &uc 0x1D544 0    // 𝕄
#define MB_N   &uc 0x2115  0    // ℕ  (letterlike)
#define MB_O   &uc 0x1D546 0    // 𝕆
#define MB_P   &uc 0x2119  0    // ℙ  (letterlike)
#define MB_Q   &uc 0x211A  0    // ℚ  (letterlike)
#define MB_R   &uc 0x211D  0    // ℝ  (letterlike)
#define MB_S   &uc 0x1D54A 0    // 𝕊
#define MB_T   &uc 0x1D54B 0    // 𝕋
#define MB_U   &uc 0x1D54C 0    // 𝕌
#define MB_V   &uc 0x1D54D 0    // 𝕍
#define MB_W   &uc 0x1D54E 0    // 𝕎
#define MB_X   &uc 0x1D54F 0    // 𝕏
#define MB_Y   &uc 0x1D550 0    // 𝕐
#define MB_Z   &uc 0x2124  0    // ℤ  (letterlike)

#endif // MATH_DOUBLESTRUCK_H
