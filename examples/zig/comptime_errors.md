| Category        | Detected When          | Typical Message Style         |
| --------------- | ---------------------- | ----------------------------- |
| Syntax          | Parsing                | Short, direct                 |
| Name resolution | Semantic analysis      | “undeclared identifier”       |
| Type errors     | Type checking          | expected vs found             |
| Comptime        | Compile-time execution | stack-trace-like              |
| Control flow    | Flow analysis          | missing return, unreachable   |
| Error handling  | Semantic analysis      | error union violations        |
| Memory safety   | Static analysis        | explicit cast required        |
| Struct/enum     | Semantic analysis      | missing/invalid field         |
| Generics        | Comptime instantiation | detailed type trace           |
| Linking         | Link phase             | undefined / duplicate symbols |
