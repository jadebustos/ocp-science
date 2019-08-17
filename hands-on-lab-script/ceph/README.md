# Lab02: Ceph-nano deployment

**INCLUDE CEPH NANO DEPLOYMENT CREATION TASKS FOR STUDENTS**

S3 endpoint must be reachable from the internet.

To buckets have to be created by students:

* one named Red Hat for the R shiny app
* other named pi

Users need to be crated to access these buckets.

Students must take note for the bucket name and credentials to be used later.

## Install Ceph-Nano [WIP]
```
$ oc new-project ceph
$ oc adm policy add-scc-to-user anyuid -z default -n ceph
$ oc create -f ceph-nano.yaml -n ceph
$ export CEPH_ENDPOINT=$(oc get route ceph-nano -n ceph | awk 'NR>1{print $2;exit;}')
$ oc set env sts ceph-nano RGW_NAME=$CEPH_ENDPOINT
```
Wait until the pod ```ceph-nano-0``` is running, then:
```
$ oc exec -i ceph-nano-0 bash <<EOF
sed -i "s/127.0.0.1:8000/$CEPH_ENDPOINT/g" /opt/ceph-container/sree/static/js/base.js
EOF
```

## Create a bucket and upload data

One Ceph-nano has been successfully deployed you will have to:

1. Create a bucket.
2. Upload these files to the bucket: [ansible.txt.gz](data/ansible.txt.gz), [ceph.txt.gz](data/ceph.txt.gz), [ocp.txt.gz](data/ocp.txt.gz), [osp.txt.gz](data/osp.txt.gz), [rhv.txt.gz](data/rhv.txt.gz)

> IMPORTANT: Take note of your S3 bucket and credentials due to you will have to use later.

## Scritps to perform operations on S3

If you want to use these scripts you will have to create the __endpoint.json__ file with the data to access your S3 endpoint:

```
{
    "access_key": "vendoopelcorsa",
    "secret_key": "enbuenestado",
    "endpoint_url": "radosgw.example.com",
    "endpoint_port": "80"
}
```

### __list_buckets.py__ script

You can use the [list_buckets.py](scripts/list_buckets.py) script to list the buckets in the S3 endpoint:

```
$ python list_buckets.py
```

### __s3createbucket.py__ script

You can use the [s3createbucket.py](scripts/s3createbucket.py) script to create buckets:

```
$ python s3createbucket.py --bucket BUCKETNAME
```

### __s3deletebucket.py__ script

You can use the [s3deletebucket.py](scripts/s3deletebucket.py) script to delete a bucket:

```
$ python s3deletebucket.py --bucket BUCKETNAME
```
### __s3uploadfiles.py__ script

You can use the [s3uploadfiles.py](scripts/s3uploadfiles.py) script to upload files to a bucket:

```
$ python s3uploadfiles.py --bucket BUCKETNAME --files "FILENAME1,FILENAME2,FILENAME3"
```

> TIP: You can update several files at a time using a "," as a separator.

### __s3deletefiles.py__ script

You can use the [s3deletefiles.py](scripts/s3deletefiles.py) script to delete files from a bucket:

```
$ python s3deletefiles.py --bucket BUCKETNAME --files "FILENAME1,FILENAME2,FILENAME3"
```

> TIP: You can delete several files at a time using a "," as a separator.

### __s3downloadfiles.py__ script

You can use the [s3downloadfiles.py](scripts/s3downloadfiles.py) script to download a file from a bucket:

```
$ python s3downloadfiles.py --bucket BUCKETNAME --files "FILENAME1,FILENAME2,FILENAME3"
```

> TIP: You can download several files at a time using a "," as a separator.

### __s3listbucket.py__ script

You can use the [s3listbucket.py](scripts/s3listbucket.py) scripts to list a bucket's content:

```
$ python s3listbucket.py --bucket BUCKETNAME
```
