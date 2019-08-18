# Lab03: R Shiny workloads

This application create words cloud for some Red Hat products.

The user will select one of the Red Hat products available:

* **Red Hat Virtualization**
* **Red Hat Openstack Platform**
* **Red Hat Ceph Storage**
* **Openshift Container Platform**
* **Red Hat Ansible Engine**

Depending on the selected product the application will get a file containing words related to the product and create the word cloud. The files used to create the word cloud will be stored in Red Hat Ceph Storage.

![word cloud](imgs/word-cloud.png)

## High level pod description

![R Shiny](imgs/r-shiny.png)

## Lab's pupouse

Illustrate how **Red Hat Ceph Storage** can be used as a data backend for applications running in **OCP**.

## Application deployment

First of all we should create a new project:

```
oc new-project r-shiny
```

To deploy this app is as simple as execute the following command:

```
$ oc process -f https://raw.githubusercontent.com/jadebustos/ocp-science/master/hands-on-lab-script/applications/shiny-app/template.yml \
    -p S3_ACCESS_KEY=${S3_ACCESS_KEY} \
    -p S3_SECRET_KEY=${S3_SECRET_KEY} \
    -p S3_HOST=${S3_HOST} \
    -p S3_PORT=${S3_PORT} \
    -p S3_BUCKET=${S3_BUCKET}
```

> NOTE: for more info about ceph go to 

After some initialization, assuming that everything is fine we should see our Pod running. Next thing is to expose it (expose containers internally as services and externally via routes):

```
$ oc expose pod shiny-app
$ oc expose service shiny-app
```

## Application access

How you can access your app ? Is as simple as you deployed it and run:

```
$ oc get route shiny-app
NAME              HOST/PORT         PATH      SERVICE        LABELS    TLS TERMINATION
shiny-app         www.example.com   /         shiny-app
$
```

Copy the value of the column `HOST/PORT` and put it in your browser:

```
https://www.example.com
```
