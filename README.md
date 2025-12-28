# Research Unix Tenth Edition (V10) Bourne Shell - 64-bit AMD64 Port

This repository contains a historically preserved and 64-bit stabilized port of the **Tenth Edition Research Unix (V10) Bourne Shell**. Originally released in 1989 by Bell Telephone Laboratories, this shell represents the final evolution of the original Bourne shell inside the Research Unix stream.

## 🚀 Quick Start

Build the shell on any modern 64-bit Linux system:

```bash
git clone git@github.com:wordatet/v10sh-amd64.git
cd v10sh-amd64
make
./v10sh
```

### Self-Paging Documentation
The manual page `sh.1` is a polyglot script that can be executed directly as a viewer:
```bash
./sh.1
```

---

## 🛠 64-bit Stabilization & Modern Fixes

This port is specifically tailored for **x86_64 (AMD64) Linux**. Unlike previous attempts that relied on 32-bit compatibility layers, this version is natively stable on 64-bit systems.

### Key Stabilization Milestones:
- **Zero-Leak Allocator**: Preserves the original `sbrk`-based `blok.c` memory manager, audited for 64-bit pointer arithmetic.
- **ABI Alignment**: Fixed several 64-bit pointer truncation bugs (notably in `Lcheat`/`Rcheat` and environment handling).
- **Security Hardening**: Fixed legacy buffer overflows in `prs_cntl` and path handling.
- **Deep Recursion Safe**: Verified stable up to 2,000 recursive function calls.

## ✨ Historical & Unique Features

The V10 shell introduced several innovative features that weren't common in other Bourne variants of the era:

- **Interactive `cd` Autocorrect**: Uses the `spname` algorithm to suggest corrections for misspelled directories.
- **The `$HISTORY` Variable**: An early implementation of command history tied to variable assignment (`HISTORY=...`).
- **Function Support**: Robust Bourne shell function implementation.
- **Self-Documenting**: Includes the original Tenth Edition manual page.

## ⚖️ Legal & Non-Commercial Use

This source code is for **non-commercial, educational, and research purposes only**.

- **Copyright (c) 1989-1990 Alcatel-Lucent.**
- This code is made available under the **Alcatel-Lucent Non-Commercial Statement**. See the [LICENSE](LICENSE) file for the full text.

## 📜 Credits

- **Original Authors**: Stephen R. Bourne and the Research Unix team at Bell Telephone Laboratories.
- **Porting & Preservation**: Mario (@wordatet) and the Claude + Gemini LLM agentic team.

---
*Part of the Research Unix Preservation Project.*
