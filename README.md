## KPL compiler project:

The project includes:
- A sample file to count word and digit: `word_digit_counter.c`.
- Scanner: scan to recognize type of every word.
    - Any PKL file can be run for testing. E.g.,, in this `test` folder.
- Parser: parse a KPL programming language file to see whether the syntax is valid.
    - One can run example test inside `Parser/test/example*.kpl` and check their corresponding result file: `Parser/test/result*.txt`
- Semantics test: Scan to read type of each declared keyword, whether it is a variable, a type, a function or a procedure. In case of function/procedure, its parameters are also read. `Semantics4` is the most completed version of this task.
    - One can run example test inside `Semantics4/tests/example*.kpl` and check their corresponding result file: `Semantics4/tests/result*.txt`

Compilation:
- Single file `word_digit_counter.c` can be compiled easily with `gcc`.
- Subprojects (Scanner, Parser, Semantics4) can be compile with `make` with given `Makefile`.
