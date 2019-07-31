# Ceph

**INCLUDE CEPH NANO DEPLOYMENT CREATION TASKS FOR STUDENTS**

S3 endpoint must be reachable from the internet.

To buckets have to be created by students:

* one named Red Hat for the R shiny app 
* other named pi

Users need to be crated to access these buckets.

Students must take note for the bucket name and credentials to be used later.

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

