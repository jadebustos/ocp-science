# Pi digits calculation as a way to check how hardware scales

## Copyright

This software is licensed under GPLv2: http://www.gnu.org/licenses/gpl-2.0.html
  (c) 2013 Jose Angel de Bustos Perez <jadebustos@gmail.com>

## Introduction

This code was writen to check how a Fujitsu Primergy serve scales when additional boards are added.

This code is not intended to be an efficient code to get pi digits but to stress the CPUs.

### pi-midpoint-rule.c

This program computes a pi approximation using the mid point rule to aproximate an integral.
  
This program uses default floating point arithmetic and it is parallelized using **OpenMP**.

To compile:

```
[user@localhost ~]$ make mid
```

OpenMP has to be installed to be compiled.

To run the program:
```
[user@localhost ~]$ ./pi-midpoint-rule.bin threads iterations
```

where threads is the number of threads to use and iterations is the number of times we want to approximate pi.

This program is designed to stress as many cores as you want.

### chudnovsky-gmp.c

This program computes pi digits using the multiple precision arithmetic library **GMP**.

This program is not parallelized.

To compile:
```
[user@localhost ~]$ make chudnovsky-gmp
```

The **GNU Multiple precision arithmetic library (GMP)** has to be instaled to be compiled.

```
[user@localhost ~]$ ./chudnovsky-gmp.bin decimals
```

where decimals is the number of decimals we want to compute. If no argument is provided then the program assumes 1000 digits.

Pi is stored as ASCII in **gmp-pi.dat** file.

This program uses the Chudnovsky algorithm to compute pi and the main goals of this program are:

* To stress one core
* Ilustrate how to use GMP

### chudnovsky-gmp-omp.c

This program computes pi digits using the multiple precision arithmetic library **GMP**.

This program is parallelized using **OpenMP**.

  To compile:
```
[user@localhost ~]$ make chudnovsky-gmp-omp
```

The **GNU Multiple precision arithmetic library (GMP)** has to be instaled to be compiled. **OpenMP** has to be installed to be compiled

```
[user@localhost ~]$ ./chudnovsky-gmp.bin threads decimals
```

where threads is the number of threads to use and decimals is the number of decimals we want to compute. If the number of arguments is different from two only one thread is used and 1000 digits are calculated.

Two files are created:

* **omp-gmp-pi.info** info about computation.
* **omp-gmp-pi.dat** pi number in binary format.

This program uses the Chudnovsky algorithm to compute pi and the main goals of this program are:

* To stress as many cores as you want
* Ilustrate how to use **GMP**

### pi2txt.c

This program is used to get as many decimals of pi as you want from **omp-gmp-pi.dat** and to store them in ASCII format in a file which you have to supply as an argument:

```
[user@localhost ~]$ ./pi2txt.bin decimals omp-gmp-pi.dat pi_txt_file
```

where decimals is the number of decimals we want to read **omp-gmp-pi.dat** and write to pi_txt_file
