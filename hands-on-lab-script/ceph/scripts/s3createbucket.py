# -*- coding: utf-8 -*-
#!/usr/bin/python

# (c) 2018 Jose Angel de Bustos Perez <jadebustos@redhat.com>
# Distributed under GPLv3 License (https://www.gnu.org/licenses/gpl-3.0.en.html)

import sys
import boto
import boto.s3.connection
import argparse

import config

# this script creates a bucket

# a endpoint.json file with data connections must exist
#{
#    "access_key": "foo",
#    "secret_key": "bar",
#    "endpoint_url": "ceph.example.com",
#    "endpoint_port": "80"
#}

def parse_args():
  parser = argparse.ArgumentParser(description='Create a S3 bucket')
  parser.add_argument('--bucket', required=True)
  return parser.parse_args()

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
  radoshost = myConfig.getRadosHost()
  radosport = myConfig.getRadosPort()

  # process arguments
  args = parse_args()

  # create a S3 connection
  boto.config.add_section('s3')
  conn = boto.connect_s3(
    aws_access_key_id = access_key,
    aws_secret_access_key = secret_key,
    host = radoshost,
    port = radosport,
    is_secure=False,
    calling_format = boto.s3.connection.OrdinaryCallingFormat(),
    )

  # bucket creation
  bucket = conn.create_bucket(args.bucket)

  for bucket in conn.get_all_buckets():
    print "{name}\t{created}".format(
      name = bucket.name,
      created = bucket.creation_date,
    )

if __name__ == "__main__":
  main()
