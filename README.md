# Bite™

![Linux Supported](https://shields.io/badge/Linux-Supported-orange?logo=linux&logoColor=white&style=flat-square)
![Windows Supported](https://shields.io/badge/Windows-Supported-0078D6?logo=windows&logoColor=white&style=flat-square)
![Compiler](https://shields.io/badge/compiler-Chewer%20v1.2.1-blue?style=flat-square)
![Written in](https://shields.io/badge/written%20in-C%2B%2B-00599C?logo=c%2B%2B&logoColor=white&style=flat-square)
![Backend](https://shields.io/badge/backend-LLVM-262D3A?logo=llvm&logoColor=white&style=flat-square)
![Build System](https://shields.io/badge/build-CMake-064F8C?logo=cmake&logoColor=white&style=flat-square)
![License](https://shields.io/badge/license-GPLv3--with--runtime--exception-blue?style=flat-square)
[![Chewer Test](https://github.com/VoidGriefedTeam/BiteC/actions/workflows/test.yml/badge.svg?event=check_run)](https://github.com/VoidGriefedTeam/BiteC/actions/workflows/test.yml)

> **⚠️ Development Status**
> Bite™ and its compiler, Chewer, are under active development. Syntax, semantics, and CLI behavior are subject to change without notice.

A small, strictly-typed language with explicit variable declarations and simple I/O — compiled to native code by **Chewer**, a cross-compiling C++/LLVM toolchain.

---

## Table of Contents

1. [About](#about)
2. [The Chewer Compiler](#the-chewer-compiler)
   - [Requirements](#requirements)
   - [Usage](#usage)
   - [Checking the Version](#checking-the-version)
3. [Building from Source](#building-from-source)
4. [Language Reference](#language-reference)
5. [Getting Started](#getting-started)
6. [Platform Support](#platform-support)
7. [License](#license)

---

## About

Bite™ is a minimal, strictly-typed language built around explicit variable declaration and straightforward console I/O. Every statement ends in `;`, and every variable is prefixed with `&` to keep identifiers visually distinct from keywords and literals.

For the full syntax — variable types, declaration, assignment, `PRINT`, and `_READ` — see the [Language Reference](#language-reference).

---

## The Chewer Compiler

Bite™ source is compiled by **Chewer**, currently at **version 1.2.1**. Chewer is written in pure C++ and uses **LLVM** as its backend, allowing it to target multiple platforms from a single host.

### Requirements

Chewer's compilation command is strict — the input path, target OS, and output path are **all required** on every invocation.

### Usage

```bash
bitec "path/to/file.bite" <os> -o "path/to/output.o"
```

| Argument | Description |
|---|---|
| `"path/to/file.bite"` | Path to the Bite™ source file to compile |
| `<os>` | Target platform — must be `windows` or `linux64` |
| `-o "path/to/output"` | Output path for the compiled object/binary |

**Example — compiling for Windows:**
```bash
bitec "src/main.bite" windows -o "build/main.o"
```

**Example — compiling for Linux (from a Windows host):**
```bash
bitec "src/main.bite" linux64 -o "build/main.o"
```

### Checking the Version

```bash
bitec -V
# or
bitec --version
```

---

## Building from Source

Chewer is written in pure C++ and built with **CMake**.

```bash
git clone https://github.com/<your-org>/<your-repo>.git
cd <your-repo>
cmake -B build -S .
cmake --build build
```

**Requirements:**
- CMake (3.x+)
- A C++ compiler with LLVM development libraries installed

---

## Language Reference

The full grammar — types, variable declaration/assignment/usage, and I/O (`PRINT`, `_READ`) — is documented separately in the [Bite™ Language Reference](./docs/Bite-Language-Reference.md).

---

## Getting Started

1. Write a `.bite` source file.
2. Compile it with `bitec`, specifying your target OS:
   ```bash
   bitec "hello.bite" windows -o "hello.o"
   ```
3. Link/run the resulting output for your target platform.

---

## Platform Support

| | Host | Compile Target |
|---|---|---|
| **Windows** | ✅ Supported | ✅ Supported |
| **Linux** | ❌ Not yet a supported host | ✅ Supported (`linux64`) |

Chewer currently only **runs** on Windows, but can **cross-compile** Bite™ programs for either Windows or Linux (`linux64`) via its LLVM backend.

---

## License

Chewer is licensed under the **GNU General Public License v3.0**, with the **GCC Runtime Library Exception, version 3.1**.

In short:
- Chewer itself — the compiler source, its CLI, and its internals — is free software under **GPLv3**: you're free to use, study, modify, and redistribute it, and any distributed modified version must also be released under GPLv3.
- The **runtime exception** means that programs you compile *with* Chewer are **not** required to be GPL-licensed themselves. Linking your compiled `.bite` program against Chewer's runtime/support code does not place your program under the GPL — you may distribute your compiled output under terms of your choosing.

See [`LICENSE`](./LICENSE) for the full, unmodified license text.

---

<p align="center"><sub>Bite™ &amp; Chewer — a strictly-typed language and its native compiler</sub></p>
