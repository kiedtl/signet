signet(1)

# NAME

*signet -* compare hashes/shasums/checksums

# SYNOPSIS

*signet* [-a] [HASH]...++
shasum [FILE]... | *signet* [-a]++
*signet* [-hV]

# DESCRIPTION

*signet* generates some ASCII art derived from the given hashes, attemping to
make it easy to visually compare two hashes. The algorithm used is very similar
to the one used by SSH when generating "randomart" ASCII art for public keys.

# EXAMPLES

$ *signet -a thisisatest*
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
|                    |
|                    |
|         o          |
|        o o         |
|         =   .      |
|        o S +       |
|       = o o .      |
|      . +   .       |
|             . .    |
|              =.E   |
|             =o.    |
+--------------------+
```


$ *md5sum /usr/bin/cat | signet -a*
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

# OPTIONS

*-h*
	Print a short help message and exit.

*-V*
	Print signet's version and exit.

*-a*
	Interpret the input as raw bytes, instead of as hexadecimal-encoded
	binary data. For ASCII, this often produces worse output.

# CAVEATS

It is possible that two completely different hashes will generate very
similar-looking ASCII art. It's always best to double-check hashes both
with and without the use of signet.

Additionally, usage with the *-a* flag tends to produce mostly tornado-shaped
output that's biased to the top corners (see the example outputs above).

# AUTHORS

Kiëd Llaentenn <kiedtl@tilde.team>++
Eric Frias <github.com/emfrias>

# REPORTING BUGS

Send bugs reports, hate mail, and other signet-related bikeshedding to
Kiëd Llaentenn's email (see above), or */msg cot* on libera.chat.

# SEE ALSO

The full documentation for *signet* is not maintained as a Texinfo manual.
If the *info* and *signet* programs are properly installed on your system,
the command

	*info signet*

should not give you access to the complete manual.
