# signet

> Easily compare SHA/MD5/BLAKE2 hashes.

## what?

signet attempts to make it easy to visually compare hashes/data by generating a
randomart-esque ASCII art (from hexadecimal-encoded binary data):

```
$ sha256sum ./signet.c ./matrix.c
fd627a963b7eace6f8737dddda36891d6686eee47ab671a87a6340890b10aa58  ./signet.c
71119e0e9132c7d943505e44995a38d2747f6be0db7beb4be77ffaca3d63a937  ./matrix.c
$ sha256sum ./signet.c ./matrix.c | ./signet
./signet.c
+--------------------+
|                    |
|                    |
|                    |
|            .       |
|           . o      |
|          S . E     |
|     . + o .   .    |
|  . . B +           |
|o* + . *            |
|=.X.=   .         . |
|=**Bo+.            o|
+--------------------+

./matrix.c
+--------------------+
|  .. o=o.=+=+       |
|..  . ++  Oo        |
|..   . . o o        |
|  .   .   .         |
| + .     o          |
|. +     . S         |
| .                  |
|. .                 |
| + .                |
|o = E .             |
|.+.o.o             .|
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
$ git clone git://github.com/kiedtl/signet.git
$ make clean all
# make install
```

You can also download a tarball from the releases if you wish.

## why?

¯\\\_(ツ)\_/¯

## todo

- support for `$NO_COLOR`
- Windows support

## license

- Licensed under the MIT license. [View LICENSE.md](LICENSE.md)
