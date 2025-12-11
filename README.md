# 🚀 Custom Language Compiler in C

![Language](https://img.shields.io/badge/language-C-blue.svg)
![Platform](https://img.shields.io/badge/platform-macOS%20%7C%20Apple%20Silicon-grey)
![Architecture](https://img.shields.io/badge/arch-ARM64-orange)

A simple compiler built from scratch in C. It compiles a custom C-like language directly into **ARM64 Assembly** for macOS.

This project was built to understand the low-level mechanics of programming languages, including manual memory management, tokenization, AST construction, and stack-based memory allocation.

---

## ⚠️ Architecture & Compatibility
> [!WARNING]
> **This compiler generates native assembly specifically for Apple Silicon.**

It utilizes macOS-specific system calls (syscalls) and ARM64 instructions (like `svc`, `str`, `ldr`). It **will not run** on Windows, Linux machines without modifying the Code Generator.

---

## 🛠️ Features

*   **Lexer:** Tokenizes source code without using tools like Flex. Handles dynamic string allocation and complex multi-character tokens (identifiers, integers).
*   **Recursive Descent Parser:** Validates grammar and builds a hierarchical Abstract Syntax Tree (AST).
*   **Symbol Table:** Tracks variable names and their specific offsets on the stack.
*   **Stack Memory Management:**   Implements local variable storage.
*   **ARM64 Code Generation:** Writes raw `.s` assembly files.

---

## 📝 The Language
Currently, the language supports integer variables and program exit codes.

**Input (`test.a`):**



🔮 Future improvements

Support for binary expressions (int x = 5 + 5;)

Support for variable reassignment (x = 10;)

if statements and branching
