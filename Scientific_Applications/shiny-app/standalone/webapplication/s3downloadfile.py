# -*- coding: utf-8 -*-
#!/usr/bin/python

# (c) 2018 Jose Angel de Bustos Perez <jadebustos@redhat.com>
# Distributed under GPLv3 License (https://www.gnu.org/licenses/gpl-3.0.en.html)

import os
import sys
import boto
import boto.s3.connection

import config

# this scripts download the file passed as first argument from s3 endpoint

# a endpoint.json file with data connections must exist
#{
#    "access_key": "vendoopelcorsa",
#    "secret_key": "enbuenestado",
#    "endpoint_url": "ceph.example.com",
#    "endpoint_port": "80"
#    "bucket": "bucket"
#}

def main():
  # read configuration
  myConfig = config.readConfig()

  # check that configuration was successfully read
  if myConfig.getConfigState() == False:
    print "Error in config."
    sys.exit(1)

  # configure access data
  access_key = myConfig.getAccessKey()
  secret_key = myConfig.getSecretKey()
  s3_host = myConfig.getRadosHost()
  s3_port = myConfig.getRadosPort()
  s3_bucket = myConfig.getBucket()

  # create a S3 connection
  boto.config.add_section('s3')
  conn = boto.connect_s3(
        aws_access_key_id = access_key,
        aws_secret_access_key = secret_key,
        # s3 endpoint
        host = s3_host,
        # s3 port
        port = int(s3_port),
        is_secure=False,
        calling_format = boto.s3.connection.OrdinaryCallingFormat(),
        )

  # bucket where data is stored
  bucket = conn.get_bucket(s3_bucket)

  key = bucket.get_key(sys.argv[1])
  key.get_contents_to_filename(sys.argv[1])

if __name__ == "__main__":
  main()