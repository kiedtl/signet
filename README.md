# signet

> Easily compare SHA/MD5/BLAKE2 hashes.

## what?

signet attempts to make it easy to visually compare hashes/data by generating a
randomart-esque ASCII art:

```
$ md5sum ~/test
ce6ac5212a668f2ab3e15ca464e68bbd /home/kiedtl/test
$ ./signet ce6ac5212a668f2ab3e15ca464e68bbd
┌───────────────────────────────────┐
│                   ##^S#+          │
│                  8+X+O+..         │
│                 = o               │
│                . +                │
│                 + .               │
│                + .                │
│               . +                 │
│                  =                │
│                 . .               │
│                                   │
│                                   │
│                                   │
│                                   │
│                                   │
│                                   │
│                                   │
│                                   │
└───────────────────────────────────┘

$ md5sum ./signet
e895193ed7ebe2e7b841db138c480ba9 ./signet
$ ./signet e895193ed7ebe2e7b841db138c480ba9
┌───────────────────────────────────┐
│               +#@+++++++          │
│              ..*Oo.+=. .+         │
│                .= ..   .          │
│                + .                │
│                 =                 │
│                . +                │
│                   =               │
│                + + =              │
│                 @ =               │
│                o =                │
│                 .                 │
│                                   │
│                                   │
│                                   │
│                                   │
│                                   │
│                                   │
└───────────────────────────────────┘
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
$ git clone --recurse git://github.com/lptstr/signet.git
$ make clean signet
# make install
```

## why?

¯\_(ツ)_/¯

## todo

- manpage

## disclaimer

This software is in beta; expect bugs. Do not use for any security-related
purpose.

## license

- Licensed under the MIT license. [View LICENSE.md](LICENSE.md)
