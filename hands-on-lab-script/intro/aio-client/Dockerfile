FROM registry.fedoraproject.org/fedora:30

RUN dnf -y install python2
RUN dnf install -y https://dl.fedoraproject.org/pub/epel/7/x86_64/Packages/s/s3cmd-2.0.2-1.el7.noarch.rpm
RUN pip install kafka
COPY clients/kafka_producer.py /usr/bin/kafka_producer.py
COPY clients/kafkaClient /usr/bin/kafkaClient
RUN chmod 755 /usr/bin/kafka_producer.py /usr/bin/kafkaClient

