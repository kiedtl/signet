signet(1)

# NAME

*signet -* compare hashes/shasums/checksums

# SYNOPSIS

*signet* [HASH]...++
shasum [FILE]... | *signet*

# DESCRIPTION

*signet* generates some ASCII art derived from the given hashes, attemping
to make it easy to visually compare two hashes. The algorithm is uses is
very similar to the one used by SSH when generating "randomart" ASCII art
for public keys.

# EXAMPLES

$ *signet thisisatest*
```
+--------------------+
| E .                |
|  . o               |
|   . o              |
|      + .           |
|       B o          |
|        @ S         |
|       o o          |
|                    |
|                    |
|                    |
|                    |
+--------------------+
```

$ *md5sum /usr/bin/cat | signet*
```
/usr/bin/cat
+--------------------+
|        .*@X+@Ooo.E |
|         +O++=B...  |
|         =   o      |
|        B           |
|         = .        |
|          S         |
|                    |
|                    |
|                    |
|                    |
|                    |
+--------------------+
```

# CAVEATS

It is possible that two completely different hashes will generate very
similar-looking ASCII art. It's always best to double-check hashes both
with and without the use of signet.

# AUTHORS

Kiëd Llaentenn <kiedtl@tilde.team>

# REPORTING BUGS

Send bugs reports, hate mail, and other signet-related bikeshedding to the
author's email above, or */msg kiedtl* on freenode.

# SEE ALSO

The full documentation for *signet* is not maintained as a Texinfo manual.
If the *info* and *signet* programs are properly installed on your system,
the command

	*info signet*

should not give you access to the complete manual.
