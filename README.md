# Steel programming language (.steel)

For now don't working, wait to 1.0.0 release or try 0.x.x releases.
Should be low level, simple, fast (like C or better), programmong language and toolchain.

## Goals

- easier `C`
- saver `C`
- less code than `C` (sometimes)
- default cross platform `C` (std to)
- fast as `C` (or better)
- no header files, no imports?
- pascal (zig, rust) like types `var i: i32 = 3` | `var i = 3`
- zero cost apstraction (for loop)
- OPP/RAII support (similar to zig, destructors?)
- easy build/config
- fn optional paramerets
- automatic code formatting
- automatic handle of arr.len/str.len

## License: MIT

## Contributing

To contribute open an issue or contact me.

## Idea

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
<!-- - global gitattibutes later, when lang will works -->

### 0.0.1-dev (Pending...)

- `C` HJson (parse, stringify, parse_fast, parse_file, some methods), faster than cJSON -> try benchmarks
