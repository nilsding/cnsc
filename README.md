# cnsc

_cnsc: C No Scope Commits_

This is a small utility similar to [Retrospring/nsc](https://github.com/Retrospring/nsc), but
it's written in the C programming language and therefore at least 420% faster.  It also has no
runtime dependencies, and works only on Unix-like systems.

## Building

Building cnsc requires CMake.

    $ mkdir build && cd build
    $ cmake ..
    $ sudo cp cnsc /usr/local/bin

## Running

`cnsc` requires no command line arguments to work.  It asks everything it needs from the
console using an interactive menu.  However, to speed up the committing process a bit, you can
specify some command line arguments.

For example, to add all files automatically, start cnsc like this:

    $ cnsc -a

Want to specify a commit message on the fly? Use the `-m` flag:

    $ cnsc -m 'My awesome commit!'  

Of course you can also combine the two flags.

    $ cnsc -am 'Hack hack hooray!'  

`cnsc` will return the return code of `git commit`.

## License

Like nsc, cnsc is licensed under the terms of the MIT License.

