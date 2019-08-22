#!/usr/bin/python2

import time
import argparse
import os
import ssl

from kafka import KafkaProducer
from kafka.errors import KafkaError


def parse_args():
    parser = argparse.ArgumentParser(description='Send bytes to a kafka topic')
    parser.add_argument('--topic', default="rhte")
    parser.add_argument('--brokers', required=True)
    parser.add_argument('--skip-tls-verify', action='store_true', default=True)
    parser.add_argument('--use-tls', action='store_true', default=False)
    parser.add_argument('--file', required=True)
    return parser.parse_args()

def main():
    args = parse_args()
    brokers = args.brokers.split(',')
    if args.use_tls:
        c=ssl.SSLContext(protocol= ssl.PROTOCOL_TLS)
        producer = KafkaProducer(bootstrap_servers=brokers,
                security_protocol='SSL', ssl_context=c)
    else:
        producer = KafkaProducer(bootstrap_servers=brokers)
    if not os.path.exists:
        print("File %s not found" % args.file)
        sys.exit(1)
    with open(args.file,"rb") as fd:
        filedata = fd.read()
        ack = producer.send(args.topic, filedata)
        producer.flush()
        metadata = ack.get()
    
    print("Message sent to partition %d of the topic %s at the offset %d" %
            (metadata.partition, metadata.topic, metadata.offset))

if __name__ == "__main__":
    main()
