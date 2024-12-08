# GDB CHEAT SHEET

1. Compile your program with cc -g [-Og] ... to include debug info
2. Run your program with 'gdb (binary file, e.g. ./a.out)'
3. Happy debugging!
   1. layout src
   2. run
   3. SEGFAULT...
   4. backtrace
   5. proceed from there...

## Essential Commands

* gdb program - debug program
* layout src - show source code
* refresh - refresh TUI (useful when view breaks due to terminal output from debugged program)
* run [arglist] - start your program [with arglist]
* bt/backtrace - display program stack
* b [file:]function - set breakpoint at function [in file]
* c/continue - running your program
* finish - run until selected stack frame returns (finish current function)
* p/print expr - display the value of an expression
* n/next - next line, stepping over function calls
* s/step - next line, stepping into function calls
* q/quit - exit GDB
* set var=expr - evaluate expr without displaying it; use for altering program variables

## Breakpoints and Watchpoints

* b/break
* b [file:]function - set breakpoint at function [in file]
* b [file:]line - set breakpoint at line number [in file]
* b . . . if expr - break conditionally on nonzero expr
* info break - show defined breakpoints
* info watch - show defined watchpoints
* clear [file:]line/function - delete breakpoint at line/func
* delete [n] - delete breakpoints [or breakpoint n]
* disable [n] - disable breakpoints [or breakpoint n]
* enable [n] - enable breakpoints [or breakpoint n]
* enable once [n] - enable breakpoints [or breakpoint n]; disable again when reached
* ignore n count ignore breakpoint n, count times
* commands n [silent] command-list - execute GDB command-list every time breakpoint n is reached. [silent suppresses default display]
* end - end of command-list

## Display

* p/print
* p [f] expr - show value of expr [according to format f]
  * x hexadecimal
  * d signed decimal
  * u unsigned decimal
  * o octal
  * t binary
  * a address, absolute and relative
  * c character
  * f floating point
* x [Nuf] - examine memory at address expr; optional format spec follows slash
  * N count of how many units to display
  * u unit size; one of
    * b individual bytes
    * h halfwords (two bytes)
    * w words (four bytes)
    * g giant words (eight bytes)
  * f printing format. Any print format, or
    * s null-terminated string
    * i machine instructions

## Automatic Display

* display [f] expr - show value of expr each time program stops [according to format f]
* display - display all enabled expressions on list
* undisplay n - remove number(s) n from list of automatically displayed expressions
* info display - numbered list of display expressions

## Expressions

* expr - an expression in C, C++, or Modula-2 (including function calls), or:
  * addr@len - an array of len elements beginning at addr
  * file::nm - a variable or function nm defined in file
  * {type}addr - read memory at addr as specified type

## Symbol Table

* info var [regex] - show names, types of global variables (all, or matching regex)
* whatis [expr] - show data type of expr [or $] without evaluating; ptype gives more detail
  * ptype [expr]
* ptype type - describe type, struct, union, or enum
