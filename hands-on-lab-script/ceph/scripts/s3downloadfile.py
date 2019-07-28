# -*- coding: utf-8 -*-
#!/usr/bin/python

# (c) 2018 Jose Angel de Bustos Perez <jadebustos@redhat.com>
# Distributed under GPLv3 License (https://www.gnu.org/licenses/gpl-3.0.en.html)

import os
import sys
import boto
import boto.s3.connection

# this file downloads the file passed as first argument from a s3 bucket

def main():
  # put here your access_key and secret_key to access s3 bucket
  access_key = 'FKQY387H5NSX077T6KWZ'
  secret_key = 'Y1CsXS3mxnMS1RjZxjsru1yysiK4gBXQsk6Kxkck'

  # your rados host
  radoshost = 'ceph1.redhatforummad.com'

  # your rados port
  radosport = 8080

  boto.config.add_section('s3')

  conn = boto.connect_s3(
    aws_access_key_id = access_key,
    aws_secret_access_key = secret_key,
    host = radoshost,
    port = radosport,
    is_secure=False,
    calling_format = boto.s3.connection.OrdinaryCallingFormat(),
    )

  bucket = conn.get_bucket('redhatforum')

  key = bucket.get_key(sys.argv[1])
  key.get_contents_to_filename(sys.argv[1])

if __name__ == "__main__":
  main()
