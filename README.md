# `uniq-lines` -- print unique lines of a file
This program prints the unique lines present in a file while
preserving their order.

## Usage

You can pass stdin to this program, or use a filename as a command line argument. E.g.:

``` bash
echo "some\nlines\nand\nmore\nlines\n" | uniq-lines
```

or

``` bash
uniq-lines my-file.txt
```

You can also optionally print the number of times a line is present in
the file, using the `-c, --count` flag.

## Installation

The included `Makefile` can be used for building and installing the
program. By default, you'll need GCC for this, but other C compilers
should work just fine.

``` bash
make
sudo make install
```

(By default, this program installs to `/usr/local/bin`.)

## Comparison with other tools

`uniq-lines` is a minimalistic tool intended to do one thing well and
should be quite fast. This becomes especially apparent when dealing with a
large number of lines.

Here are some arbitrary benchmarks using a machine with an Intel
i7-8700 @ 4.6GHz:

| Command                                                    | Line count  | Time   |
| ---------------------------------------------------------- | ----------- | ------ |
| `uniq-lines -c`                                            | 261,798,216 | 18.80s |
| `awk '{!seen[$0]++}END{for (i in seen) print seen[i], i}'` | 261,798,216 | 26.32s |
| `sort \| uniq -c`                                          | 261,798,216 | 99.25s |
