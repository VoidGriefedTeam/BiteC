# Bite™ Language Reference

![Linux Supported](https://img.shields.io/badge/Linux-Supported-orange?logo=linux&logoColor=white&style=flat-square) ![Windows Supported](https://img.shields.io/badge/Windows-Supported-0078D6?logo=windows&logoColor=white&style=flat-square)

> **⚠️ Development Status** Bite™ is currently under active development. Language features, syntax, and semantics described in this document are subject to change without notice.

---

## Table of Contents

1. [Introduction](https://25e054cb-a938-4ff7-bc1d-61f56ec80b8f.frame.claudeusercontent.com/_f/1790426184-06b0/#introduction)
2. [Syntax Overview](https://25e054cb-a938-4ff7-bc1d-61f56ec80b8f.frame.claudeusercontent.com/_f/1790426184-06b0/#syntax-overview)
3. [Variables](https://25e054cb-a938-4ff7-bc1d-61f56ec80b8f.frame.claudeusercontent.com/_f/1790426184-06b0/#variables)
    - [Data Types](https://25e054cb-a938-4ff7-bc1d-61f56ec80b8f.frame.claudeusercontent.com/_f/1790426184-06b0/#data-types)
    - [Declaring a Variable](https://25e054cb-a938-4ff7-bc1d-61f56ec80b8f.frame.claudeusercontent.com/_f/1790426184-06b0/#declaring-a-variable)
    - [Assigning a Value](https://25e054cb-a938-4ff7-bc1d-61f56ec80b8f.frame.claudeusercontent.com/_f/1790426184-06b0/#assigning-a-value)
    - [Using a Variable](https://25e054cb-a938-4ff7-bc1d-61f56ec80b8f.frame.claudeusercontent.com/_f/1790426184-06b0/#using-a-variable)
4. [Input / Output](https://25e054cb-a938-4ff7-bc1d-61f56ec80b8f.frame.claudeusercontent.com/_f/1790426184-06b0/#input--output)
    - [Output — `PRINT`](https://25e054cb-a938-4ff7-bc1d-61f56ec80b8f.frame.claudeusercontent.com/_f/1790426184-06b0/#output--print)
    - [Input — `_READ`](https://25e054cb-a938-4ff7-bc1d-61f56ec80b8f.frame.claudeusercontent.com/_f/1790426184-06b0/#input--_read)
5. [Quick Reference](https://25e054cb-a938-4ff7-bc1d-61f56ec80b8f.frame.claudeusercontent.com/_f/1790426184-06b0/#quick-reference)
6. [Example Program](https://25e054cb-a938-4ff7-bc1d-61f56ec80b8f.frame.claudeusercontent.com/_f/1790426184-06b0/#example-program)

---

## Introduction

**Bite™** is a small, strictly-typed language built around explicit variable declaration and simple I/O primitives. Every statement is terminated with a semicolon (`;`), and every variable name is prefixed with an ampersand (`&`) to distinguish it clearly from keywords and literals.

This reference documents the currently implemented grammar: variable declaration, assignment, usage, and basic console input/output.

---

## Syntax Overview

|Convention|Meaning|
|---|---|
|`_UPPER_CASE`|Reserved keyword (type or instruction)|
|`&name`|A variable identifier|
|`;`|Required statement terminator|
|`"..."`|String literal|

---

## Variables

Variables in Bite™ are **strictly typed** — once declared with a given type, a variable cannot hold data of another type.

### Data Types

|Type Keyword|Description|
|---|---|
|`_INT`|Integer numeric value|
|`_STR`|String (text) value|

### Declaring a Variable

Declaring a variable reserves it under a given type but does not yet assign it a value.

**Syntax:**

```bite
_TYPE &name ;
```

**Example:**

```bite
_INT &score ;
_STR &username ;
```

> **Note:** A variable name must always begin with `&`.

### Assigning a Value

Assigning — referred to in Bite™ as _filling_ a variable — stores data in a variable that has already been declared.

**Syntax:**

```bite
&name _VAL DATA ;
```

- `&name` — an existing, previously declared variable
- `DATA` — the value to store; its type must match the variable's declared type

**Example:**

```bite
&score _VAL 100 ;
&username _VAL "Void" ;
```

### Using a Variable

Once a variable has been declared **and** filled, it can be referenced anywhere a value is expected simply by writing its name.

**Syntax:**

```bite
&name
```

**Example:**

```bite
PRINT &score ;
```

---

## Input / Output

### Output — `PRINT`

`PRINT` writes a value to standard output. It accepts either a string literal or a variable, and supports both `_STR` and `_INT` types.

**Syntax:**

```bite
PRINT "literal text" ;
PRINT &variable ;
```

**Examples:**

```bite
PRINT "Hello, world!" ;
PRINT &username ;
```

### Input — `_READ`

`_READ` reads a value from standard input into a pre-declared variable.

**Syntax:**

```bite
&name _READ ;
```

**Requirements:**

- `&name` must be declared **before** this statement runs.
- `&name` must be of type `_INT`.
- String input (`_STR`) is **not currently supported** for `_READ`.

**Example:**

```bite
_INT &age ;
&age _READ ;
PRINT &age ;
```

---

## Quick Reference

|Operation|Syntax|Notes|
|---|---|---|
|Declare|`_TYPE &name ;`|Types: `_INT`, `_STR`|
|Assign|`&name _VAL DATA ;`|Data must match declared type|
|Use|`&name`|Requires prior declaration + assignment|
|Print|`PRINT "text" ;` or `PRINT &name ;`|Works for `_STR` and `_INT`|
|Read|`&name _READ ;`|`_INT` only; variable must pre-exist|

---

## Example Program

```bite
_STR &name ;
_INT &age ;

&name _VAL "Void" ;
PRINT "Enter your age:" ;
&age _READ ;

PRINT &name ;
PRINT &age ;
```

---

Bite™ — a strictly-typed learning language • Documentation draft