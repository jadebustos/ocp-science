FROM  centos/python-27-centos7 

RUN yum -y install python2-kafka
COPY kafka_producer.py /usr/bin/kafka_producer.py
CMD ['kafka_producer.py']
