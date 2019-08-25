# Lab introduction

In this lab we will illustrate how to deploy Scientific workloads in Red Hat Openshift 4.

> ![IMPORTANT](../imgs/important-icon.png) **IMPORTANT**: All the applications we will use in this hands-on lab were initially created as standalone applications and were easily adapted to run in OCP as a way to illustrate how easy can be migrate some applications to run in OCP.

We will be focused on using the following Red Hat Technologies:

* Red Hat Openshift 4
* Kafka
* Red Hat Ceph Storage

## Lab infrastructure description

**INCLUDE DESCRIPTION OF LAB NETWORKS, NODES, CPU, ...**

### Clients

Kafka producer and S3 clients are shipped as a container image, available at quay.io/rhte_2019/ocp-science-clients
Send a picture to a kafka topic using this container:

```
$ podman run -v pictures:/data --rm quay.io/rhte_2019/ocp-science-clients kafkaClient -tls -brokers=rhte-cluster-kafka-rhte2019.apps.cluster-apps.sandbox45.example.com:443  -topic=rhte -insecure-skip-verify -file /data/cat.jpg
```

