# Ceph

**INCLUDE CEPH NANO DEPLOYMENT CREATION TASKS FOR STUDENTS**

S3 endpoint must be reachable from the internet.

To buckets have to be created by students:

* one named Red Hat for the R shiny app 
* other named pi

Users need to be crated to access these buckets.

Students must take note for the bucket name and credentials to be used later.

## Commands

User creation:

```
# radosgw-admin user create --uid=test-root --display-name="admin user to test multiples deletes" --email="root@xxx"
{
    "user_id": "test-root",
    "display_name": "admin user to test multiples deletes",
    "email": "root@xxx",
    "suspended": 0,
    "max_buckets": 1000,
    "auid": 0,
    "subusers": [],
    "keys": [
        {
            "user": "test-root",
            "access_key": "WZ96KP95F9TJ8LU9K3EB",
            "secret_key": "gh4NX8sBmQjTMjpnn54ps23CIkEUDvcF8eaowrj9"
        }
    ],
    "swift_keys": [],
    "caps": [],
    "op_mask": "read, write, delete",
    "default_placement": "",
    "placement_tags": [],
    "bucket_quota": {
        "enabled": false,
        "max_size_kb": -1,
        "max_objects": -1
    },
    "user_quota": {
        "enabled": false,
        "max_size_kb": -1,
        "max_objects": -1
    },
    "temp_url_keys": []
}

# 
```

Get user info:

```
# radosgw-admin user info --uid=test-app
{
    "user_id": "test-app",
    "display_name": "app user to test multiples deletes",
    "email": "app@xxx",
    "suspended": 0,
    "max_buckets": 1000,
    "auid": 0,
    "subusers": [],
    "keys": [
        {
            "user": "test-app",
            "access_key": "IIXYX3P16B0BR29YSN9P",
            "secret_key": "MUBMkM18plkDFJCmrtNmSrUfjqOcO0sQivCy6nGd"
        }
    ],
    "swift_keys": [],
    "caps": [],
    "op_mask": "read, write, delete",
    "default_placement": "",
    "placement_tags": [],
    "bucket_quota": {
        "enabled": false,
        "max_size_kb": -1,
        "max_objects": -1
    },
    "user_quota": {
        "enabled": false,
        "max_size_kb": -1,
        "max_objects": -1
    },
    "temp_url_keys": []
}
#
```

List users:

```
# radosgw-admin metadata list user
[
    "user1",
    "user2",
    ...
]
# 
```

**ADD HOW TO CREATE A POOL FOR RADOS**

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

