# Lab01: R Shiny workloads

This application create words cloud for some Red Hat products.

The user will select one of the Red Hat products available:

* **Red Hat Virtualization**
* **Red Hat Openstack Platform**
* **Red Hat Ceph Storage**
* **Openshift Container Platform**
* **Red Hat Ansible Engine**

Depending on the selected product the application will get a file containing words related to the product and create the word cloud. The files used to create the word cloud will be stored in Red Hat Ceph Storage.

## High level pod description

![R Shiny](imgs/r-shiny.png)

## Lab's pupouse

Illustrate how **Red Hat Ceph Storage** can be used as a data backend for applications running in **OCP**.

## Application deployment

