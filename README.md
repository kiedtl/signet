# signet

> Easily compare SHA/MD5/BLAKE2 hashes.

## what?

signet attempts to make it easy to visually compare hashes/data by generating a
randomart-esque ASCII art:

```
$ md5sum ./signet /usr/bin/cat
abec4845b415da8d23408afbb4666608  ./signet
7e9d213e404ad3bb82e4ebb2e1f2c1b3  /usr/bin/cat

$ ./signet abec4845b415da8d23408afbb4666608
+-----------------+
|          . =oXXX|
|           o o XX|
|        . .     E|
|         o       |
|        S        |
|                 |
|                 |
|                 |
|                 |
+-----------------+

$ signet 7e9d213e404ad3bb82e4ebb2e1f2c1b3
+-----------------+
|        o.+.o.XXE|
|         + + . XX|
|        . o     .|
|         o       |
|        S        |
|                 |
|                 |
|                 |
|                 |
+-----------------+
```

## how?

It uses an algorithm very similar to the one SSH uses to generate the
randomart seen when generating a new key (`ssh-keygen`). This algorithm
is more fully described in the following two locations:

- [Making art with SSH key randomart](https://blog.benjojo.co.uk/post/ssh-randomart-how-does-it-work-art)
- [drunken bishop](http://www.dirk-loss.de/sshvis/drunken_bishop.pdf)

## where?

**build dependencies**:
- C99 compiler (tested with gcc)
- GNU Make
- `git`

**tl;dr**:
```
$ git clone git://github.com/lptstr/signet.git
$ make clean all
# make install
```

## why?

¯\\\_(ツ)\_/¯

## todo

- manpage
- ability to read from `stdin`

## disclaimer

This software is in beta; expect bugs. If you do use it, check hashes
manually in addition to using signet.

## license

- Licensed under the MIT license. [View LICENSE.md](LICENSE.md)
