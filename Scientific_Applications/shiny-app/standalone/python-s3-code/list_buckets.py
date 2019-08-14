# -*- coding: utf-8 -*-
#!/usr/bin/python

# (c) 2018 Jose Angel de Bustos Perez <jadebustos@redhat.com>
# Distributed under GPLv3 License (https://www.gnu.org/licenses/gpl-3.0.en.html)

import boto
import boto.s3.connection

# this scripts shows the buckets in the s3 endpoint

def main():
  # put here your access_key and secret_key to access s3 bucket
  access_key = 'GEIICT90BB597P57B9BB'
  secret_key = 'pZlzuKquhrBzQ74mXkAOIjpSdzoWRZwqKQzzRQIq'

  # your rados host
  radoshost = '192.168.100.110'

  # your rados port
  radosport = 8080

  conn = boto.connect_s3(
    aws_access_key_id = access_key,
    aws_secret_access_key = secret_key,
    host = radoshost,
    port = radosport,
    is_secure=False,
    calling_format = boto.s3.connection.OrdinaryCallingFormat()
    )

  for bucket in conn.get_all_buckets():
    print "{name}\t{created}".format(
      name = bucket.name,
      created = bucket.creation_date,
      )

if __name__ == "__main__":
  main()
