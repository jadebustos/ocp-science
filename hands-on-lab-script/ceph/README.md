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

If you have not cloned the repository clone it:

```
$ git clone https://github.com/jadebustos/ocp-science.git
$ cd ocp-science
```

Create the ``ceph`` project and deploy it:

```
$ cd hands-on-lab-script/ceph/
$ oc new-project ceph
$ oc adm policy add-scc-to-user anyuid -z default -n ceph
$ oc create -f ceph-nano.yaml -n ceph
$ export S3_ENDPOINT=$(oc get route ceph-nano -n ceph | awk 'NR>1{print $2;exit;}')
$ oc set env sts ceph-nano RGW_NAME=$S3_ENDPOINT
```

> ![TIP](../imgs/tip-icon.png) **TIP**: **S3_ENDPOINT** variable contains the S3 endpoint for the Ceph service that you will use in other labs so you should remember how to get it. You can also get it using ``oc get route``.

Wait until the pod ```ceph-nano-0``` is running:

```
$ oc get pods
NAME                   READY     STATUS    RESTARTS   AGE
ceph-nano-0            1/1       Running   0          80s
```

then:

```
$ oc exec -i ceph-nano-0 bash <<EOF
sed -i "s/127.0.0.1:8000/$S3_ENDPOINT/g" /opt/ceph-container/sree/static/js/base.js
EOF
```

## Create buckets and upload data

Once Ceph-nano has been successfully deployed you will have to perform some tasks. You will create two buckets that will be used in another labs.

For the [Lab03: R Shiny workloads](https://github.com/jadebustos/ocp-science/blob/master/hands-on-lab-script/applications/r-shiny.md) you will have to:

1. Create a bucket.
2. Upload these files to the bucket: [ansible.txt.gz](data/ansible.txt.gz), [ceph.txt.gz](data/ceph.txt.gz), [ocp.txt.gz](data/ocp.txt.gz), [osp.txt.gz](data/osp.txt.gz), [rhv.txt.gz](data/rhv.txt.gz)

> ![IMPORTANT](../imgs/important-icon.png) **IMPORTANT**: Take note of your S3 bucket and credentials to use them in the [Lab03: R Shiny workloads](https://github.com/jadebustos/ocp-science/blob/master/hands-on-lab-script/applications/r-shiny.md).

For the [Lab06: Computing workloads](https://github.com/jadebustos/ocp-science/blob/master/hands-on-lab-script/applications/pi.md) you will have to:

1. Create a bucket.

> ![IMPORTANT](../imgs/important-icon.png) **IMPORTANT**: Take note of your S3 bucket and credentials to use them in the [Lab06: Computing workloads](https://github.com/jadebustos/ocp-science/blob/master/hands-on-lab-script/applications/pi.md).

> ![TIP](../imgs/tip-icon.png) **TIP**: Credentials for accessing the S3 endpoing are in file **ceph-nano.yaml** in base64 to decode __base64 -d <<< STRING__.

## How to use the clients container

`s3cmd` is a command line utility used for creating s3 buckets, uploading, retrieving and managing data to s3 storage and it has included in the [clients container](https://github.com/jadebustos/ocp-science/tree/master/hands-on-lab-script/intro).

> ![TIP](../imgs/tip-icon.png) **TIP**: If you have not installed the clients container you can do it now.

You need to create a directory to work with the clients container:

```
mkdir ~/clients-container
```

Copy the data you need to upload to this directory:

```
$ pwd
/home/lab-user/ocp-science/hands-on-lab-script/ceph
$ cp resources/data/* ~/clients-container/
$
```

You need to run the clients container:

```
$ sudo -i podman run -v ~/clients-container:/srv:z -it quay.io/rhte_2019/ocp-science-clients bash
```

### Configure s3cmd Environment

In order to configure `s3cmd` we can use the below command to configure s3cmd in a interactive way:

```
$ s3cmd --configure  --no-check-certificate
```

But we are going to create the config file manually:

1. Edit/create file in the user home path:

    ```
    $ vi ~/.s3cfg
    ```

2. Add the following:

    ```
    [default]
    access_key = foo
    host_base = <S3 Endpoint>
    host_bucket = <bucket-name>
    secret_key = bar
    check_ssl_certificate = False
    check_ssl_hostname = True
    use_https = False
    ```

> ![TIP](../imgs/tip-icon.png) **TIP**: You can upload the files from the directory **/srv** to the bucket you created for the [Lab03: R Shiny workloads](https://github.com/jadebustos/ocp-science/blob/master/hands-on-lab-script/applications/r-shiny.md). Remember to put the data for the bucket you want to work with in this file.

> ![TIP](../imgs/tip-icon.png) **TIP**: Due to https is being used the port used for the S3 endpoint will be **443**.

> ![TIP](../imgs/tip-icon.png) **TIP**: The __access_key__ and __secret_key__ to access the S3 endpoint are set to the above values **foo** and **bar**.

### Uses of s3cmd Command Line

1. List all S3 bucket: Use the following command to list all s3 buckets in your aws account.

    ```
    $ s3cmd ls
    ```

2. Creating new bucket: To create a new bucket in Amazon s3 use the below command. It will create a bucket named **tecadmin** in S3 account.
    ```
    $ s3cmd mb s3://my-bucket
    ```

3. Uploading file in bucket: The below command will upload file **file.txt** to s3 bucket using **s3cmd** command.

    ```
    $ s3cmd put my-file.txt s3://my-bucket/
    ```

4. List Data of S3 bucket: List the objects of s3 bucket using **ls** switch with **s3cmd**.

    ```
    $ s3cmd ls s3://my-bucket/
    ```

5. Download files from bucket: Sometimes if we need to download files from the s3 bucket. Use the following commands to download it.

    ```
    $ s3cmd get s3://my-bucket/my-file.txt
    ```

6. Remove Data of S3 bucket: To remove files are folder from s3 bucket use the following commands.

    ```
    $ s3cmd del s3://my-bucket/my-file.txt
    ```

7. Remove S3 bucket: If we don’t need s3 bucket anymore, we can simply delete it using the following command.

    ```
    $ s3cmd rb s3://my-bucket
    ```

    > ![WARNING](../imgs/warning-icon.png) **WARNING**: Before removing bucket make sure its empty.

### Next Lab
Go to [Applications](https://github.com/jadebustos/ocp-science/blob/master/hands-on-lab-script/applications/README.md)
