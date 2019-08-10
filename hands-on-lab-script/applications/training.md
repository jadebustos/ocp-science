# Lab03: Training workloads

It is quite common to use notebooks to teach about diferent subjects.

As an example you will deploy a pod containing several Jupyter notebooks to learn about the [Navier-Stokes equations](https://en.wikipedia.org/wiki/Navier%E2%80%93Stokes_equations).

These Jupyter Notebooks have been taken from [Lorena Barba github repository](https://github.com/barbagroup/CFDPython)

> Barba, Lorena A., and Forsyth, Gilbert F. (2018). CFD Python: the 12 steps to Navier-Stokes equations. Journal of Open Source Education, 1(9), 21, https://doi.org/10.21105/jose.00021

## High level pod description

![training](imgs/training.png)

## Lab's pupouse

Illustrate how **OCP** can be used to ease personalized training for users avoiding users struggling with software installation, software development life cycle, ...

Although this lab is focused in deploying **Jupyter notebooks** any applications reachable by the http protocol can be used in the same way.

## Application deployment

First of all we should create a new project:

```
oc new-project cdf
```

To deploy this complex app is as simple as execute the following command:

```
oc process -f https://raw.githubusercontent.com/jadebustos/ocp-science/master/hands-on-lab-script/applications/cfd-training/template.yml
```

After some initialization, assuming that everything is fine we should see our Pod running. Next thing is to expose it (expose containers internally as services and externally via routes):

```
oc expose pod cdf-apps
oc expose service cdf-apps
```

## Application access

How you can access your app ? Is as simple as you deployed it:

```
oc get route cdf-apps
```

You should see something like:

```
NAME              HOST/PORT         PATH      SERVICE        LABELS    TLS TERMINATION
cdf-apps          www.example.com   /         cdf-apps
```

Copy the value of the column `HOST/PORT` and put it in your browser:

```
https://www.example.com
```