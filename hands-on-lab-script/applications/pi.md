# Lab04: Computing workloads

We can use **OCP** to run non-interactive jobs. For instance pure computing jobs.

In this lab we are going to run a job that computes **Pi** with the accuracy you want (bare in mind that this lab is a 2-hour lab). After computing **Pi** a file will be stored in **Red Hat Ceph Storage** so you can get the result.

You can validate the results using [Pi constant generator](https://www.browserling.com/tools/pi-digits).

**Pi** will be calculated using the [Chudnovsky algorithm](https://en.wikipedia.org/wiki/Chudnovsky_algorithm). The implementation used in this lab is the [GMP](https://gmplib.org/) and [OMP](https://www.openmp.org/) version taken from (https://github.com/jadebustos/science/tree/master/pi).

> NOTE: This code was originally writen to check how a Fujitsu Primergy server scales when additional boards were added. This code is not intended to be an efficient code to get pi digits but to stress the CPUs.

## High level pod description

![pi](imgs/pi.png)

## Application deployment

