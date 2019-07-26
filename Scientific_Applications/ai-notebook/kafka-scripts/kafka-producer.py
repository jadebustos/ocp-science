#!/usr/bin/python3

import time

from kafka import KafkaProducer
from kafka.errors import KafkaError


topic='rhte'

filename='kalises.jpg'

#producer = KafkaProducer(bootstrap_servers=['192.168.100.110:9092'],
#                         value_serializer=lambda x: 
#                         dumps(x).encode('utf-8'))

producer = KafkaProducer(bootstrap_servers=['192.168.100.110:9092'])

fd = open(filename,"rb")
filedata = fd.read()
fd.close()

ack = producer.send(topic, filedata)

producer.flush()

metadata = ack.get()

print(metadata.topic)
print(metadata.partition)
