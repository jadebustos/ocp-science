# -*- coding: utf-8 -*-
#!/usr/bin/python

# (c) 2018 Jose Angel de Bustos Perez <jadebustos@redhat.com>
# Distributed under GPLv3 License (https://www.gnu.org/licenses/gpl-3.0.en.html)

import os
import sys
import boto
import boto.s3.connection

# this scripts download the file passed as first argument from s3 endpoint

def main():
  # put here your access_key and secret_key to access s3 bucket
  access_key = os.environ['S3_ACCESS_KEY']
  secret_key = os.environ['S3_SECRET_KEY']
  s3_host = os.environ['S3_HOST']
  s3_port= os.environ['S3_PORT']
  s3_bucket = os.environ['S3_BUCKET']

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

