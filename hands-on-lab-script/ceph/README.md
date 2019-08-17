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

## S3 operations

* Students can use this [script](scripts/s3createbucket.py) to create buckets.
* Students can use this [script](scripts/s3deletebucket.py) to delete buckets.
* Students can use this [script](scripts/s3deletefile.py) to delete a file from bucket.
* Students can use this [script](scripts/s3uploadfiles.py) to upload a file to a bucket.
* Students can use this [script](scripts/s3downloadfile.py) to download a file from a bucket.
* Students can use this [script](scripts/s3listbucket.py) to list a bucket's content.

## Data to be uploaded

Students will have to upload the following data to a bucket:

* [ansible.txt.gz](data/ansible.txt.gz)
* [ceph.txt.gz](data/ceph.txt.gz)
* [ocp.txt.gz](data/ocp.txt.gz)
* [osp.txt.gz](data/osp.txt.gz)
* [rhv.txt.gz](data/rhv.txt.gz)
