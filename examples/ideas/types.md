# Steel types

## Bool

`bool`

```steel
var a = false;
var b: bool = true;
```

## Numbers

`i8` `i16` `i32` `i64` `isize`

`u8` `u16` `u32` `u64` `usize`

`f32` `f64`

```steel
var a = 10;
var b: usize = 3;
var c: i16 = -2;
const PI = 3.14;
const e: f32 = 2.72;
```

## Pointers

`*T`

```steel
var a: *i32 = null;
const ref = a;
var num = 10;
var numRef: *i32 = &num;
const numRef2 = &num;
```

## Slices

`T[*]` (also string, like Zig/Rust)

```steel
var arr: [5]i32 = .{ 1, 2, 3, 4, 5 };
var slice: []i32 = arr[1..4]; // slice of elements at index 1, 2, 3
```

## Arrays

`T[]`

`T[][]` `T[][][]` ...

```steel
var a: u16[] = .{ 1, 2, 3 };
const str: u8[] = "Hello world!";
var str2: u8[5] = .{ 't', 'e', 's', 't', '\0' };

const b: i32[3][4][5] = .{}; // 0
```

## Structs

`struct { x: f64, y: f64 };`

```steel
const Point = struct {
    x: f64,
    y: f64
};
var p = Point{ x = 10, y = 1.1 };
const p2 = .{
    x: f64 = 0.12,
    y: f64 = -23
};

p.x = -1;
```

## Enums

`enum { .err, .code, .ok };`

```steel
const ErrType = enum { .err, .ok };
fn testEnum(flag: bool) ErrType!void {
    if(flag) return error.err;
    return;
}

testEnum(true) catch switch(err) {
    error.err => print("Err!\n");
};
```

## Errors

`error { .err, .code }`

```steel
const ErrType = enum { .err, .ok };
fn testEnum(flag: bool) ErrType!void {
    if(flag) return error.err;
    return;
}

testEnum(true) catch switch(err) {
    error.err => print("Err!\n");
};

testEnum(false) catch |err| {
    print("err: {}\n", err);
}
```

## Unions

`unions { int: u32, float: f64 };`

```steel
const A = union { a: i32, b: f64 };
var a: A = .{};
a.b = 1.2;
a.a = 3;
```

## Functions

`fn name() T {}`

```steel
fn main() void {
}

fn withErr(err: bool) error!i32 {
    if(err) return error.err;
    return 3;
}
```

## Null?

`null` (0)
