/*
 * Mathematical Script (\mathcal) uppercase letters.
 *
 * Where a "script" letter exists in the Letterlike Symbols block
 * (B, E, F, H, I, L, M, R), we use that codepoint for best font support.
 * All others come from the Mathematical Alphanumeric Symbols block.
 *
 * Usage: `MC_A` … `MC_Z`. Send as uppercase-only (`&uc CP 0`), so
 * both tap and shift-tap produce the same glyph.
 */

#ifndef MATH_CALLIGRAPHIC_H
#define MATH_CALLIGRAPHIC_H

#define MC_A   &uc 0x1D49C 0    // 𝒜
#define MC_B   &uc 0x212C  0    // ℬ  (letterlike)
#define MC_C   &uc 0x1D49E 0    // 𝒞
#define MC_D   &uc 0x1D49F 0    // 𝒟
#define MC_E   &uc 0x2130  0    // ℰ  (letterlike)
#define MC_F   &uc 0x2131  0    // ℱ  (letterlike)
#define MC_G   &uc 0x1D4A2 0    // 𝒢
#define MC_H   &uc 0x210B  0    // ℋ  (letterlike)
#define MC_I   &uc 0x2110  0    // ℐ  (letterlike)
#define MC_J   &uc 0x1D4A5 0    // 𝒥
#define MC_K   &uc 0x1D4A6 0    // 𝒦
#define MC_L   &uc 0x2112  0    // ℒ  (letterlike)
#define MC_M   &uc 0x2133  0    // ℳ  (letterlike)
#define MC_N   &uc 0x1D4A9 0    // 𝒩
#define MC_O   &uc 0x1D4AA 0    // 𝒪
#define MC_P   &uc 0x1D4AB 0    // 𝒫
#define MC_Q   &uc 0x1D4AC 0    // 𝒬
#define MC_R   &uc 0x211B  0    // ℛ  (letterlike)
#define MC_S   &uc 0x1D4AE 0    // 𝒮
#define MC_T   &uc 0x1D4AF 0    // 𝒯
#define MC_U   &uc 0x1D4B0 0    // 𝒰
#define MC_V   &uc 0x1D4B1 0    // 𝒱
#define MC_W   &uc 0x1D4B2 0    // 𝒲
#define MC_X   &uc 0x1D4B3 0    // 𝒳
#define MC_Y   &uc 0x1D4B4 0    // 𝒴
#define MC_Z   &uc 0x1D4B5 0    // 𝒵

#endif // MATH_CALLIGRAPHIC_H
