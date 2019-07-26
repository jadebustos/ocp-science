#!/usr/bin/python3

from kafka import KafkaConsumer
from kafka.errors import KafkaError

topic='rhte'

consumer = KafkaConsumer(topic, 
                         bootstrap_servers=['192.168.100.110:9092'],
                         auto_offset_reset='earliest',
                         enable_auto_commit=True,
                         group_id='test-consumer-group')
#                         group_id='my-group',
#                         value_deserializer=lambda x: loads(x.decode('utf-8')))

for message in consumer:
  message = message.value
  fd = open('kafka-msg.jpg','wb')
  fd.write(message)
  fd.close()
  break
