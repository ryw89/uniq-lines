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
