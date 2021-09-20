# Password_Generator
A simple password generator : Decimal, Hexadecimal, Letters (uppercase and lowercase), Special characters or Custom ASCII list

# How to ?

## Build

```bash
sudo apt-get update
sudo apt-get install make gcc
make

```

## Use

By default when calling the command `Password_Generator` with no arguments it generates by default **4 Hexadecimal passwords of 32 characters (16 bytes)**

Can generate password with :
- Upercase letters [A..Z]
- Lowercase letters [a..z]
- Decimal numbers [0..9]
- Hexadecimal numbers [0..9][A..F]
- Special characters "<>?,.;:!%&#{}()[]-_@+=|"
- Custom ASCII list (up to 256 ASCII characters)

Limitations :
- Password length up to 256 characters
- Password number up to 512 passwords generated

These limitations may be increased by changing the following constant in the `main.c` :

```
#define MAX_PASSWORD_LEN      256  /* 256 characters length maximum */
#define MAX_PASSWORD_NUM      512  /* 512 passwords maximum to generate */

```

### Usage :

```
Password_Generator [options] :
-h          : Display help / argument list / usage
-l <length> : Password Length (character number) [1..64] - Default = 32 characters
-n <number> : Number of password to generate [1..100] - Default = 4 passwords
-H          : Use hexadecimal characters [0..9][A..F] - Default
-D          : Use decimal characters [0..9]
-U          : Use uppercase letters characters [A..Z]
-L          : Use lowercase letters characters [a..z]
-S          : Use special letters characters "<>?,.;:!%&#{}()[]-_@+=|"
-C "List"   : Use a custom ASCII list of characters (up to 256 characters in the list)

```

### Example 1 : Password type = Hexadecimal - Length = 10 characters (5 bytes) - Number of password to generate = 5

Call the following command : `Password_Generator -l 10 -n 5 -H`

Output example :

```bash
./Password_Generator -l 10 -n 5 -H
[2021-09-20 13:53:19] Launching the program
[2021-09-20 13:53:19] Password length = 10 characters
[2021-09-20 13:53:19] Number of password to generate = 5
[2021-09-20 13:53:19] Use hexadecimal numbers [0..9][A..Z] to generate password(s)
[2021-09-20 13:53:19] Password generated #001 = DDBBC8FD93
[2021-09-20 13:53:19] Password generated #002 = 24F97C898D
[2021-09-20 13:53:19] Password generated #003 = FB25794639
[2021-09-20 13:53:19] Password generated #004 = 34E1266B53
[2021-09-20 13:53:19] Password generated #005 = 1FA9E67BF6
[2021-09-20 13:53:19] Exiting the program

```

### Example 2 : Password type = Uppercase + Lowercase letters - Length = 15 characters - Number of password to generate = 3

Call the following command : `Password_Generator -l 15 -n 3 -L -U`

```bash
./Password_Generator -l 15 -n 3 -L -U
[2021-09-20 13:56:43] Launching the program
[2021-09-20 13:56:43] Password length = 15 characters
[2021-09-20 13:56:43] Number of password to generate = 3
[2021-09-20 13:56:43] Use lowercase letters [a..z] to generate password(s)
[2021-09-20 13:56:43] Use uppercase letters [A..Z] to generate password(s)
[2021-09-20 13:56:43] Password generated #001 = ebIjCiEDpfYjzMb
[2021-09-20 13:56:43] Password generated #002 = AYajLemEDuimXso
[2021-09-20 13:56:43] Password generated #003 = eUlAKrStgZXqNwH
[2021-09-20 13:56:43] Exiting the program

```

### Example 3 : Password type = Decimal numbers - Length = 12 characters - Number of password to generate = 8

Call the following command : `Password_Generator -l 12 -n 8 -D`

```bash
./Password_Generator -l 12 -n 8 -D
[2021-09-20 13:57:50] Launching the program
[2021-09-20 13:57:50] Password length = 12 characters
[2021-09-20 13:57:50] Number of password to generate = 8
[2021-09-20 13:57:50] Use decimal numbers [0..9] to generate password(s)
[2021-09-20 13:57:50] Password generated #001 = 459512247288
[2021-09-20 13:57:50] Password generated #002 = 361561759966
[2021-09-20 13:57:50] Password generated #003 = 610335841847
[2021-09-20 13:57:50] Password generated #004 = 446359912738
[2021-09-20 13:57:50] Password generated #005 = 149913587641
[2021-09-20 13:57:50] Password generated #006 = 339820350403
[2021-09-20 13:57:50] Password generated #007 = 529356904477
[2021-09-20 13:57:50] Password generated #008 = 122300447113
[2021-09-20 13:57:50] Exiting the program

```

### Example 4 : Password type = Uppercase + Lowercase letters + Numbers - Length = 20 characters - Number of password to generate = 6

Call the following command : `Password_Generator -l 20 -n 6 -L -U -D`

```bash
./Password_Generator -l 20 -n 6 -L -U -D
[2021-09-20 13:58:18] Launching the program
[2021-09-20 13:58:18] Password length = 20 characters
[2021-09-20 13:58:18] Number of password to generate = 6
[2021-09-20 13:58:18] Use lowercase letters [a..z] to generate password(s)
[2021-09-20 13:58:18] Use uppercase letters [A..Z] to generate password(s)
[2021-09-20 13:58:18] Use decimal numbers [0..9] to generate password(s)
[2021-09-20 13:58:18] Password generated #001 = LFOHBjmcEfHD8FdWKpsZ
[2021-09-20 13:58:18] Password generated #002 = zp4prIx0gSJaYqDyL1iR
[2021-09-20 13:58:18] Password generated #003 = foqTLvdbQWEIiYpZiffJ
[2021-09-20 13:58:18] Password generated #004 = 64tDzjFk51LuYlmy9L5u
[2021-09-20 13:58:18] Password generated #005 = 2YyKZAhxOi56afAvQ5Ho
[2021-09-20 13:58:18] Password generated #006 = rMpZ1zjK9ScLthOcoYEo
[2021-09-20 13:58:18] Exiting the program

```

### Example 5 : Password type = Uppercase + Lowercase letters + Numbers + Special characters - Length = 30 characters - Number of password to generate = 10

Call the following command : `Password_Generator -l 30 -n 10 -L -U -D -S`

```bash
./Password_Generator -l 30 -n 10 -L -U -D -S
[2021-09-20 14:00:03] Launching the program
[2021-09-20 14:00:03] Password length = 30 characters
[2021-09-20 14:00:03] Number of password to generate = 10
[2021-09-20 14:00:03] Use lowercase letters [a..z] to generate password(s)
[2021-09-20 14:00:03] Use uppercase letters [A..Z] to generate password(s)
[2021-09-20 14:00:03] Use decimal numbers [0..9] to generate password(s)
[2021-09-20 14:00:03] Use special characters to generate password(s)
[2021-09-20 14:00:03] Password generated #001 = 2=h(q&6=Eb_bT=B:4i)0>=+.)ED>z#
[2021-09-20 14:00:03] Password generated #002 = tRN<!<2qai9j6|sPU{dR2S2T;8bnx8
[2021-09-20 14:00:03] Password generated #003 = 9[r2#L>Tij[2)TcrXAr2w{EN([@mHc
[2021-09-20 14:00:03] Password generated #004 = QkWvL,m;XmwBVvhZ,)LKr?Wvgs@|rI
[2021-09-20 14:00:03] Password generated #005 = h#5w%h_7n9=>91{?jG[TZ]8f3cmO#b
[2021-09-20 14:00:03] Password generated #006 = DBs0[6X#B{yiq@BW7JK7w:OhEFAvza
[2021-09-20 14:00:03] Password generated #007 = UJ,=|LTmUXcgD4CQx}kJFyv[Q@b#zU
[2021-09-20 14:00:03] Password generated #008 = OQmXO#JE:t:Ms0k<)<2)ti=HsL.jJW
[2021-09-20 14:00:03] Password generated #009 = gToXdTvwe=Z&W3__|CfGMe&=6(({:+
[2021-09-20 14:00:03] Password generated #010 = m2#vP&SLK:!AvOV?OXfKc5skYws,ww
[2021-09-20 14:00:03] Exiting the program

```

### Example 6 : Password type = Custom ASCII list [0123?.,;:&+=!] - Length = 20 characters - Number of password to generate = 6

Call the following command : `Password_Generator -l 20 -n 6 -C "0123?.,;:&+=!"`

```bash
./Password_Generator -l 20 -n 6 -C "0123?.,;:&+=!"
[2021-09-20 18:56:20] Launching the program
[2021-09-20 18:56:20] Password length = 20 characters
[2021-09-20 18:56:20] Number of password to generate = 6
[2021-09-20 18:56:20] Use custom list to generate password(s) : "0123?.,;:&+=!"
[2021-09-20 18:56:20] Password generated #001 = 0.&.:!+:22!:0!+!+!=,
[2021-09-20 18:56:20] Password generated #002 = ,0=:3&,22?&.&&:=?+&=
[2021-09-20 18:56:20] Password generated #003 = :;1&0=1!3:!&?!::0&33
[2021-09-20 18:56:20] Password generated #004 = 2&+3:?02:.2&3+;,&+3=
[2021-09-20 18:56:20] Password generated #005 = .?:.,&11?!3!&;&23112
[2021-09-20 18:56:20] Password generated #006 = 111:+0!?=.;!+,&+13,;
[2021-09-20 18:56:20] Exiting the program

```


Enjoy !





