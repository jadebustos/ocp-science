# Lab introduction

In this lab we will illustrate how to deploy Scientific workloads in Red Hat Openshift 4.

> ![IMPORTANT](../imgs/important-icon.png) **IMPORTANT**: All the applications we will use in this hands-on lab were initially created as standalone applications and were easily adapted to run in OCP as a way to illustrate how easy can be migrate some applications to run in OCP.

We will be focused on using the following Red Hat Technologies:

* Red Hat Openshift 4
* Kafka (Through AMQ Streams operator)
* Red Hat Ceph Storage

### Class Environment

* One administration server (bastion.$GUID.$SANDBOX.opentlc.com, bastion.$GUID.internal)
* One OCP Master.
* Three OCP Workers.

**Remember**, all the tasks/labs should be done from the administration server (bastion host). So, log in to the bastion host before running any command.

### Clients

Kafka producer and S3 clients are shipped as a container image, available at quay.io/rhte_2019/ocp-science-clients.
Detailed instructions about how to use these clients will be described when needed.

As prerequisite to use the containerized clients. Install podman and pull the container image in the **bastion** machine:

```
$ sudo -i yum -y install podman
$ sudo -i podman pull quay.io/rhte_2019/ocp-science-clients:latest
```

### Next Lab
Go to [Lab01: Deploy AMQ Streams](https://github.com/jadebustos/ocp-science/blob/master/hands-on-lab-script/amq-streams/README.md)
