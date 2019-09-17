# Lab02: Ceph-nano deployment

## Ceph

Ceph provides storage:

* [Block](https://docs.ceph.com/docs/master/rbd/).
* [Object storage](https://docs.ceph.com/docs/master/radosgw/) a RESTful gateway which supports two interfaces: **Swift** and **S3**.
* [CephFS](https://docs.ceph.com/docs/master/cephfs/) a POSIX-compliant filesystem.

Ceph Storage can be easily used to store and retrieve data from any application that implements **Swift** or **S3**.

Installing a Ceph Storage Cluster takes a while and requires resources. It could be complicated for developers to deploy a full Ceph Storage cluster just to tests their applications.

## High level pod description

![ceph-nano](imgs/ceph-nano.png)

## Lab's purpose

[Ceph-nano](https://github.com/ceph/cn) can be used for developers to test their applications in an easy way.

As Ceph-nano can be deployed in containers in this lab you will deploy it inside OCP that illustrate how developers could use it to test their applications with no dependency from external departments.

> ![IMPORTANT](../imgs/important-icon.png) **IMPORTANT**: Ceph-nano is not intended for production purposes but for testing.

## Install Ceph-Nano

* If you have not cloned the repository clone it:

```
$ git clone https://github.com/jadebustos/ocp-science.git
$ cd ocp-science
```

* Create the ``ceph`` project and deploy it:

```
$ cd hands-on-lab-script/ceph/
$ oc new-project ceph
$ oc adm policy add-scc-to-user anyuid -z default -n ceph
$ oc create -f ceph-nano.yaml -n ceph
$ export S3_ENDPOINT=$(oc get route ceph-nano -n ceph | awk 'NR>1{print $2;exit;}')
$ oc set env sts ceph-nano RGW_NAME=$S3_ENDPOINT
```

> ![TIP](../imgs/tip-icon.png) **TIP**: **S3_ENDPOINT** variable contains the S3 endpoint for the Ceph service that you will use in other labs so you should remember how to get it. You can also get it using ``oc get route``.

* Wait until the pod ```ceph-nano-0``` is running:

```
$ oc get pods
NAME                   READY     STATUS    RESTARTS   AGE
ceph-nano-0            1/1       Running   0          80s
```

* Optionally, you can start a shell session in the pod and run some radosgw-admin (a RADOS gateway user administration utility) commands to obtain information about the Ceph cluster.
```
$ oc rsh ceph-nano-0
radosgw-admin user info --uid=nano
radosgw-admin bucket list
...
exit
```
  More info about the available radosgw-admin commands and options can be found [here](https://docs.ceph.com/docs/giant/man/8/radosgw-admin/)

### Configure Sree web client
[Sree](https://github.com/cannium/Sree) enables you to easily manage your files through Amazon S3 protocol. Ceph-nano automatically deploys sree client, but the following additional step is necessary to make it work:

```
$ oc exec -i ceph-nano-0 bash <<EOF
sed -i "s/127.0.0.1:8000/$S3_ENDPOINT/g" /opt/ceph-container/sree/static/js/base.js
EOF
```

## Create buckets and upload data

Once Ceph-nano has been successfully deployed you will have to perform some tasks. You will create two buckets that will be used in another labs.

* For the [Lab03: R Shiny workloads](https://github.com/jadebustos/ocp-science/blob/master/hands-on-lab-script/applications/r-shiny.md) you will have to:

  1. Create a bucket.
  2. Upload these files to the bucket: [ansible.txt.gz](data/ansible.txt.gz), [ceph.txt.gz](data/ceph.txt.gz), [ocp.txt.gz](data/ocp.txt.gz), [osp.txt.gz](data/osp.txt.gz), [rhv.txt.gz](data/rhv.txt.gz)

* For the [Lab06: Computing workloads](https://github.com/jadebustos/ocp-science/blob/master/hands-on-lab-script/applications/pi.md) you will have to:

  1. Create a new bucket.

So, **How can I create the buckets and upload data?** There are many ways you can create s3 buckets and upload data. In this lab, two methods are described. Select the one you prefer (or even try to create one bucket with each method). The two available methods are:

  1. s3cmd command utility.
  2. sree web client.

### s3cmd command utility

`s3cmd` is a command line utility used for creating s3 buckets, uploading, retrieving and managing data to s3 storage and it has included in the [clients container](https://github.com/jadebustos/ocp-science/tree/master/hands-on-lab-script/intro).

> ![TIP](../imgs/tip-icon.png) **TIP**: If you have not installed the clients container you can do it now.

You need to create a directory to work with the clients container:

```
mkdir ~/clients-container
```

Copy the data you need to upload to this directory:

```
$ cd
/home/lab-user/ocp-science/hands-on-lab-script/ceph
$ cp resources/data/* ~/clients-container/
```

You need to run the clients container:

```
$ sudo -i podman run -v ~/clients-container:/srv:z -it quay.io/rhte_2019/ocp-science-clients bash
```

#### Configure s3cmd Environment

In order to configure `s3cmd`, we are going to create the config file manually:

1. Create file in the user home path:

```
$ vi ~/.s3cfg
```

2. Add the following:

```
[default]
access_key = foo
host_base = <S3 Endpoint>**
host_bucket = <S3 Endpoint>**
secret_key = bar
check_ssl_certificate = False
check_ssl_hostname = True
use_https = False
```

** The vale of ```<S3 Endpoint>``` must be the S3_ENDPOINT obtained in the previous steps. If you don't remember it, you can exit from the container, run ```oc get route ceph-nano -n ceph | awk 'NR>1{print $2;exit;}'``` to obtained it, and run again the container with ```podman``` command showed above. An example of the config file is described below:

```
[default]
access_key = foo
host_base = ceph-nano-ceph.apps.cluster-2956.sandbox478.opentlc.com
host_bucket = ceph-nano-ceph.apps.cluster-2956.sandbox478.opentlc.com
secret_key = bar
check_ssl_certificate = False
check_ssl_hostname = True
use_https = False
```

> ![TIP](../imgs/tip-icon.png) **TIP**: You can upload the files from the directory **/srv** to the bucket you created for the [Lab03: R Shiny workloads](https://github.com/jadebustos/ocp-science/blob/master/hands-on-lab-script/applications/r-shiny.md). Remember to put the data for the bucket you want to work with in this file.

> ![TIP](../imgs/tip-icon.png) **TIP**: Due to https is being used the port used for the S3 endpoint will be **443**.

> ![TIP](../imgs/tip-icon.png) **TIP**: The __access_key__ and __secret_key__ to access the S3 endpoint are set to the above values **foo** and **bar**.

> ![TIP](../imgs/tip-icon.png) To configure automatically the tool, you could run: ```$ s3cmd --configure  --no-check-certificate```

#### Create Bucket and upload files

* Create two different buckets with the name you want (one for the lab03 and the other one for the lab06). For example:
  ```
  $ s3cmd mb s3://bucket-lab03
  $ s3cmd mb s3://bucket-lab06
  ```

* Upload the files ansible.txt.gz, ceph.txt.gz, ocp.txt.gz, osp.txt.gz, rhv.txt.gz that are in the folder /srv/ to the lab03 bucket. For example:
  ```
  $ s3cmd put /srv/* s3://bucket-lab03
  ```

* Check the files have been correctly uploaded:
  ```
  $ s3cmd ls s3://bucket-lab03
  ```
More info about s3cmd Command Line options can be found [here](https://github.com/jadebustos/ocp-science/blob/master/hands-on-lab-script/ceph/s3cmd.md)

### Sree web client
* Just open the sree web client in a browser (check the route with the following command):
```
oc get route ceph-dashboard -n ceph | awk 'NR>1{print $2;exit;}'
```
* Click on "Create Bucket" button and enter a name for your bucket.
* Click on the created Bucket and click on "Upload" button to upload the files you want.

### Next Lab
Go to [Applications](https://github.com/jadebustos/ocp-science/blob/master/hands-on-lab-script/applications/README.md)
