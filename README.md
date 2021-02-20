# signet

> Easily compare SHA/MD5/BLAKE2 hashes.

## what?

signet attempts to make it easy to visually compare hashes/data by generating a
randomart-esque ASCII art:

```
$ sha256sum ./signet.c ./matrix.c
1abc0c20a9198bb971a1e610f712b7039e3243d8f0d18d6aa4d1d821a58f6ee8  ./signet.c
71119e0e9132c7d943505e44995a38d2747f6be0db7beb4be77ffaca3d63a937  ./matrix.c
$ sha256sum ./signet.c ./matrix.c | ./signet

./signet.c
+--------------------+
|              +*OSSS|
|            . +o=SS@|
|           . o E oX@|
|          . o      o|
|           +        |
|          S         |
|                    |
|                    |
|                    |
|                    |
|                    |
+--------------------+

./matrix.c
+--------------------+
|      .+==&SE%*##=. |
|       .o+=@SBX&*o  |
|           +oX .=   |
|          +   o     |
|         o .        |
|          S         |
|                    |
|                    |
|                    |
|                    |
|                    |
+--------------------+
```

## how?

It uses an algorithm very similar to the one SSH uses to generate the
randomart seen when generating a new key (`ssh-keygen`). This algorithm
is more fully described in the following two locations:

- [Making art with SSH key randomart](https://blog.benjojo.co.uk/post/ssh-randomart-how-does-it-work-art)
- [drunken bishop](http://www.dirk-loss.de/sshvis/drunken_bishop.pdf)

## where?

**build dependencies**:
- C99 compiler, GNU Make

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

## license

- Licensed under the MIT license. [View LICENSE.md](LICENSE.md)
