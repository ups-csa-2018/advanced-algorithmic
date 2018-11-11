# Advanced Algorithmic TP1

## Build instructions

This project uses GNU autotools
([autoconf](https://www.gnu.org/software/autoconf/) and
[automake](https://www.gnu.org/software/automake/)) to provide build
instructions:

```
# clone the repository && and go to the tp1 directory
$ git clone https://github.com/ups-csa-2018/advanced-algorithmic && cd tp1
# setup and launch autotools build
$ autoreconf -vfi
$ ./configure
$ make
```

## Run the test suite

Once you've initialized the repository and autotools (cf. the previous
section), you can run the test suite with:

```
$ make test-suite
```

## Additionnal notes

Regarding exercises that required to time the execution of different algorithms
and compare their respective execution time, I intentionnaly chose to not
handle that in the algorithm itself. GNU/Linux provides some useful tools to
achieve the exact same goal.

For example, you can use the [`time(1)`](https://linux.die.net/man/1/time)
utility to get a report of the time used by a process:

```
$ time exercise1 tests/test1-input.txt
50 30 23

real	0m0.002s
user	0m0.002s
sys	0m0.000s
```

N.B.: similar tools exist on Windows and BSD.

### Some timing examples

Here's a simple bash command that create a list of numbers (and can be
configured with variables `N`, `K`, and `MAXVAL`), then stores it into a
variable named `LIST_NUMBERS`:

```
LIST_NUMBERS=$(N=300000; K=30000; MAXVAL=1000000; echo "$N $K"; \
    for ((i = 0; i < $N; i++)); \
        do echo -n "$(((RANDOM % $MAXVAL) + 1)) "; \
    done; echo "")
```

You can then pass this variable to the standard input of the four exercises to
easily compare their execution time:

```
$ time (echo "$LIST_NUMBERS" | ./exercise1 > /dev/null)

real	0m11.473s
user	0m11.427s
sys	0m0.014s
$ time (echo "$LIST_NUMBERS" | ./exercise2 > /dev/null)

real	0m0.105s
user	0m0.102s
sys	0m0.006s
$ time (echo "$LIST_NUMBERS" | ./exercise3 > /dev/null)

real	0m0.140s
user	0m0.125s
sys	0m0.021s
time (echo "$LIST_NUMBERS" | ./exercise-addendum > /dev/null)

real	0m0.145s
user	0m0.125s
sys	0m0.025s
```
