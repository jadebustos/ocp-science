# Lab Installation

## The environment

```
                                .-~~~-.
                        .- ~ ~-(       )_ _
                       /                     ~ -.
                      |      OUTSIDE WORLD        \
                      \                         .'
                        ~- . _____________ . -~
                                  |
                                  |
                                  |
  ()=========================================================() (192.168.1.0/24) Public Network
    |                 |                 |                   |
+-------+         +-------+         +-------+         +-----------+
|       |         |       |         |       |         |           |
| ceph1 |         | ceph2 |         | ceph3 |         | cephinfra |
|       |         |       |         |       |         |           |
+-------+         +-------+         +-------+         +-----------+
    |                 |                 |                   |
  ()=========================================================() (192.168.200.0/24) Cluster Network
```

Server IPs:

Server | Public Network | Cluster Network
-------|----------------|----------------
ceph1 | 192.168.1.121 | 192.168.200.121 
ceph2 | 192.168.1.122 | 192.168.200.122 
ceph3 | 192.168.1.123 | 192.168.200.123 
cephinfra | 192.168.1.120 | 192.168.200.120

DNS and endpoint information:

FQDN  | IP | DNS Record | Role | Port
------|----|----------- |------|-----
ceph1.redhatforummad.com | 192.168.1.121 | A | ceph-mon & rados | 8080/tcp rados
ceph2.redhatforummad.com | 192.168.1.122 | A | ceph-mon | 
ceph3.redhatforummad.com | 192.168.1.123 | A | ceph-mon |
cephinfra.redhatforummad.com | 192.168.1.120 | A | not defined |
rhproducts.redhatforummad.com | cephinfra | CNAME | web application | 3838/tcp
cephmetrics.redhatforummad.com | cephinfra | CNAME | cephmetrics | 8080/tcp


## Ceph 3.1 installation

* Each ceph node has two data disks (/dev/vdb and /dev/vdc).
* OSDs are collocated (journal in the same device) and filestore is used.
* Containerized ceph is installed so MONs, OSDs and MGRs share server.
* cephinfra node is used as ansible server to deploy ceph cluster and cephmetrics.
* cephmetrics is installed in cephinfra node.
* ansible playbooks used to install the ceph cluster are located [here](ceph-ansible).
* ansible playbooks used to install cephmetrics are located [here](cephmetrics-ansible).

## Web application installation

A [web application](../webapplication) was created to use with this lab.

This application has been developed in **R** and it is installed in the **cephinfra** node. To install it:

* As **R** need to be installed development tools have to be installed:

```
[root@cephinfra ~]# yum groupinstall -y 'Development Tools'
[root@cephinfra ~]# yum install -y libcurl-devel openssl-devel libxml2-devel
```

* Enable the **optional** repo and **EPEL** repos:

```
[root@cephinfra ~]# subscription-manager repos --enable=rhel-7-server-optional-rpms
[root@cephinfra ~]# yum install -y https://dl.fedoraproject.org/pub/epel/epel-release-latest-7.noarch.rpm
```

* Install **python-boto** to be able to use python to access to S3 API that ceph provides:

```
[root@cephinfra ~]# yum install -y python-boto
```

* Install **R** (from EPEL):

```
[root@cephinfra ~]# yum install -y R
```

* To run the application some **R** packages need to be installed:

```
[root@cephinfra ~]# cat install_packages.R 
install.packages('shiny', repos='https://cran.rediris.es/')
install.packages('shinydashboard', repos='https://cran.rediris.es/')
install.packages('memoise', repos='https://cran.rediris.es/')
install.packages('tm', repos='https://cran.rediris.es/')
install.packages('wordcloud', repos='https://cran.rediris.es/')
[root@cephinfra ~]# Rscript install_packages.R 
```

* To be able to run the **R** application as a web application **shiny-server** has to be installed:

```
[root@cephinfra ~]# wget https://download3.rstudio.org/centos6.3/x86_64/shiny-server-1.5.9.923-x86_64.rpm
[root@cephinfra ~]# yum localinstall shiny-server-1.5.9.923-x86_64.rpm
```

* Configure **shiny-server**:

```
[root@cephinfra ~]# cat /etc/shiny-server/shiny-server.conf 
# Instruct Shiny Server to run applications as the user "shiny"
run_as shiny;

# Define a server that listens on port 3838
server {
  listen 3838;

  # Define a location at the base URL
  location / {

    # Host the directory of Shiny Apps stored in this directory
    #site_dir /srv/shiny-server;
    site_dir /srv/rhforum;

    # Log all Shiny output to files in this directory
    log_dir /var/log/shiny-server;

    # When a user visits the base URL rather than a particular application,
    # an index of the applications available in this directory will be shown.
    directory_index off;
  }
}
[root@cephinfra ~]# 
```

* Create **/srv/shiny-server** and copy the [application](../webapplication) to that directory.
* Restart and configure **shiny-server** to start at boot time:

```
[root@cephinfra ~]# systemctl enable shiny-server
[root@cephinfra ~]# systemctl restart shiny-server
```

* If the firewall is enabled open **3838/tcp** port:

```
[root@cephinfra ~]# firewall-cmd --zone=public --add-port=3838/tcp --permanent
[root@cephinfra ~]# firewall-cmd --reload
```

## Uploading data to Ceph

The application uses four files to generate the work cloud:

* **ceph.txt.gz** for **Red Hat Ceph Storage**.
* **ocp.txt.gz** for **Openshift Container Platform**.
* **osp.txt.gz** for **Red Hat Openstack Platform**.
* **rhv.txt.gz** for **Red Hat Virtualization**.
* **ansible.txt.gz** for **Red Hat Ansible Automation**.

An user has to be created to access the object storage:

```
[root@ceph1 ~]# docker exec ceph-mon-ceph1 radosgw-admin user create --uid=rhforum --display-name="Red Hat Forum User"
{
    "user_id": "rhforum",
    "display_name": "Red Hat Forum User",
    "email": "",
    "suspended": 0,
    "max_buckets": 1000,
    "auid": 0,
    "subusers": [],
    "keys": [
        {
            "user": "rhforum",
            "access_key": "FKQY387H5NSX077T6KWZ",
            "secret_key": "Y1CsXS3mxnMS1RjZxjsru1yysiK4gBXQsk6Kxkck"
        }
    ],
    "swift_keys": [],
    "caps": [],
    "op_mask": "read, write, delete",
    "default_placement": "",
    "placement_tags": [],
    "bucket_quota": {
        "enabled": false,
        "check_on_raw": false,
        "max_size": -1,
        "max_size_kb": 0,
        "max_objects": -1
    },
    "user_quota": {
        "enabled": false,
        "check_on_raw": false,
        "max_size": -1,
        "max_size_kb": 0,
        "max_objects": -1
    },
    "temp_url_keys": [],
    "type": "rgw"
}

[root@ceph1 ~]# 
```

Now we can create a bucket to store data. You can use [this python script](../python-s3-code/s3createbucket.py) to create the **redhatforum** bucket.

You can use [this python script](../python-s3-code/s3uploadfiles.py) to upload the [data](../s3data) (the **.gz** files) to the **redhatforum** bucket.
