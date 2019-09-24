# Lab05: Training workloads

It is quite common to use notebooks to teach about diferent subjects.

As an example you will deploy a pod containing several Jupyter notebooks to learn about the [Navier-Stokes equations](https://en.wikipedia.org/wiki/Navier%E2%80%93Stokes_equations).

> ![INFORMATION](../imgs/information-icon.png) **__INFORMATION__**: [Navier Stokes equations](https://www.claymath.org/millennium-problems/navier%E2%80%93stokes-equation) is one of the [Millenium Problems](https://www.claymath.org/millennium-problems) for the [Clay Mathematics Institute](https://www.claymath.org/) and the person that resolves the Navier Stokes could be awarded with a [$1 millon prize](http://www.claymath.org/sites/default/files/millennium_prize_rules.pdf). Please do not forget the 3% commission for the speakers when you get the prize!!!!

These Jupyter Notebooks have been taken from [Lorena Barba github repository](https://github.com/barbagroup/CFDPython):

> ![INFORMATION](../imgs/information-icon.png) **INFORMATION**: Barba, Lorena A., and Forsyth, Gilbert F. (2018). CFD Python: the 12 steps to Navier-Stokes equations. Journal of Open Source Education, 1(9), 21, https://doi.org/10.21105/jose.00021

## High level pod description

![training](imgs/training.png)

## Lab's purpouse

Illustrate how **OCP** can be used to ease personalized training for users avoiding users struggling with software installation, software development life cycle, ...

Although this lab is focused in deploying **Jupyter notebooks** any applications reachable by the http protocol can be used in the same way.

## Application deployment

First of all we should create a new project:

```
$ oc new-project cdf
```

To deploy and expose through an edge route this complex app is as simple as execute the following commands:

```
$ oc run --port=8080 --expose --image=quay.io/rhte_2019/cfd-training:latest cdf-apps
$ oc create route edge --service=cdf-apps
```
## Application access

How you can access your app? Is as simple as you deployed it and run:

```
$ oc get route cdf-apps
NAME       HOST/PORT                       PATH      SERVICES   PORT      TERMINATION   WILDCARD
cdf-apps   cdf-apps-cdf.apps.example.com             cdf-apps   <all>     edge          None
```

Copy the value of the column `HOST/PORT` and put it in your browser:

```
https://cdf-apps-cdf.apps.example.com
```

Notebook's Login token should be available in the pod logs:

```
$ oc logs cdf-apps-1-k6pj6
[I 10:38:15.023 NotebookApp] Writing notebook server cookie secret to /opt/work/.local/share/jupyter/runtime/notebook_cookie_secret
[I 10:38:15.263 NotebookApp] JupyterLab extension loaded from /opt/conda/lib/python3.7/site-packages/jupyterlab
[I 10:38:15.263 NotebookApp] JupyterLab application directory is /opt/conda/share/jupyter/lab
[I 10:38:15.265 NotebookApp] Serving notebooks from local directory: /opt/work
[I 10:38:15.265 NotebookApp] The Jupyter Notebook is running at:
[I 10:38:15.265 NotebookApp] http://(cdf-apps-1-k6pj6 or 127.0.0.1):8080/?token=1f0c932f85b58dc559c96f136d2ea9f356b5faec771f2253
[I 10:38:15.265 NotebookApp] Use Control-C to stop this server and shut down all kernels (twice to skip confirmation).
[C 10:38:15.269 NotebookApp]

    To access the notebook, open this file in a browser:
        file:///opt/work/.local/share/jupyter/runtime/nbserver-8-open.html
    Or copy and paste one of these URLs:
        http://(cdf-apps-1-k6pj6 or 127.0.0.1):8080/?token=1f0c932f85b58dc559c96f136d2ea9f356b5faec771f2253
```

> ![INFORMATION](../imgs/information-icon.png) **__INFORMATION__**: A password to access the notebook can be configured using a json file and starting the notebook using ```--config```. You can get more information in [Jupyter Notebooks Security](https://jupyter-notebook.readthedocs.io/en/latest/security.html#server-security) and [Jupyter configuration files](https://jupyter-contrib-nbextensions.readthedocs.io/en/latest/config.html).

## Lab resources

You can find all the resources to build the container in [this directory](https://github.com/jadebustos/ocp-science/tree/master/hands-on-lab-script/applications/cfd-training/resources).

## Next Lab
Go to [Lab06: Computing workloads](https://github.com/jadebustos/ocp-science/blob/master/hands-on-lab-script/applications/pi.md)
