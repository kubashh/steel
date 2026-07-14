# Steel programming language (.steel)

For now don't working, wait to 1.0.0 release or try 0.x.x releases.
Should be low level, simple, fast (like C or better), programmong language and toolchain.

## Goals

- Enforce a highly organized and modular code structure, similar to Java.
- Keep the language and syntax simple and minimalistic, inspired by Zig.
- Provide safety features such as RAII, optionals, and memory safety.
- Maintain strict typing and strong compile-time checks.
- Default to cross-platform C compatibility using only the standard library.
- Achieve performance equal to C.
- Minimize boilerplate: never use header files and manual imports where possible.
- Use expressive, Pascal/Rust/Zig-like type syntax: e.g., var i: i32 = 3 or var i = 3.
- Support zero-cost abstractions for common patterns (e.g., loops).
- Include object-oriented and RAII-style support, including destructors, similar to Zig.
- Simplify build and configuration processes.
- Allow optional function parameters.
- Provide automatic code formatting.
- Automatically handle array and string lengths (arr.len, str.len).

## License MIT

## Contributing

To contribute open an issue or contact me.

## Compiler steps

- Code (text)
  - Tokenize
    - AST
      - Check syntax
      - Code formatting (maybe add AST before code formatting, for format (on save))
    - Join tokens arrays (one value, for build lib/exe) or one file const fileName = struct {};
      - Push all global values to file top
        - AST
          - Code gen

- Don't need headers, can read files form `steel.json`

## TODO

- read and execute config (v0.1.0)
- compile to `C`
- auto include (v0.2.0) - no imports

### 0.0.1-dev (Pending...)

- `C` HJson (parse, stringify, parse_fast, parse_file, some methods), faster than cJSON -> try benchmarks
