/*
 * Mathematical Fraktur (\mathfrak) — uppercase and lowercase.
 *
 * Lowercase is included because fraktur lowercase is heavily used in
 * physics/math for Lie algebras (e.g. 𝔤 = Lie algebra of a group G).
 *
 * Each macro sends lowercase on tap, uppercase on shift-tap
 * (`&uc CP_LOWER CP_UPPER`) — matches normal typing conventions.
 *
 * Where a fraktur letter exists in the Letterlike Symbols block
 * (C, H, I, R, Z uppercase), we use that codepoint for font support.
 *
 * Usage: `MF_A` … `MF_Z`.
 */

#ifndef MATH_FRAKTUR_H
#define MATH_FRAKTUR_H

#define MF_A   &uc 0x1D51E 0x1D504   // 𝔞 / 𝔄
#define MF_B   &uc 0x1D51F 0x1D505   // 𝔟 / 𝔅
#define MF_C   &uc 0x1D520 0x212D    // 𝔠 / ℭ  (upper is letterlike)
#define MF_D   &uc 0x1D521 0x1D507   // 𝔡 / 𝔇
#define MF_E   &uc 0x1D522 0x1D508   // 𝔢 / 𝔈
#define MF_F   &uc 0x1D523 0x1D509   // 𝔣 / 𝔉
#define MF_G   &uc 0x1D524 0x1D50A   // 𝔤 / 𝔊
#define MF_H   &uc 0x1D525 0x210C    // 𝔥 / ℌ  (upper is letterlike)
#define MF_I   &uc 0x1D526 0x2111    // 𝔦 / ℑ  (upper is letterlike)
#define MF_J   &uc 0x1D527 0x1D50D   // 𝔧 / 𝔍
#define MF_K   &uc 0x1D528 0x1D50E   // 𝔨 / 𝔎
#define MF_L   &uc 0x1D529 0x1D50F   // 𝔩 / 𝔏
#define MF_M   &uc 0x1D52A 0x1D510   // 𝔪 / 𝔐
#define MF_N   &uc 0x1D52B 0x1D511   // 𝔫 / 𝔑
#define MF_O   &uc 0x1D52C 0x1D512   // 𝔬 / 𝔒
#define MF_P   &uc 0x1D52D 0x1D513   // 𝔭 / 𝔓
#define MF_Q   &uc 0x1D52E 0x1D514   // 𝔮 / 𝔔
#define MF_R   &uc 0x1D52F 0x211C    // 𝔯 / ℜ  (upper is letterlike)
#define MF_S   &uc 0x1D530 0x1D516   // 𝔰 / 𝔖
#define MF_T   &uc 0x1D531 0x1D517   // 𝔱 / 𝔗
#define MF_U   &uc 0x1D532 0x1D518   // 𝔲 / 𝔘
#define MF_V   &uc 0x1D533 0x1D519   // 𝔳 / 𝔙
#define MF_W   &uc 0x1D534 0x1D51A   // 𝔴 / 𝔚
#define MF_X   &uc 0x1D535 0x1D51B   // 𝔵 / 𝔛
#define MF_Y   &uc 0x1D536 0x1D51C   // 𝔶 / 𝔜
#define MF_Z   &uc 0x1D537 0x2128    // 𝔷 / ℨ  (upper is letterlike)

#endif // MATH_FRAKTUR_H
