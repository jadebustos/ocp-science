# AMQ Streams

## Deploying Kafka Cluster operator

Create `amq-streams` project:

```
$ oc new-project amq-streams
```

Configure cluster operator to watch all namespaces:

- Edit the 050-Deployment-strimzi-cluster-operator.yaml file.
- Set the value of the STRIMZI_NAMESPACE environment variable to *

Since we have configured the Cluster Operator to watch all namespaces, it's required to configure additional ClusterRoleBindings to grant cluster-wide access to the Cluste Operator.

```
$ oc adm policy add-cluster-role-to-user strimzi-cluster-operator-namespaced --serviceaccount strimzi-cluster-operator -n amq-streams
$ oc adm policy add-cluster-role-to-user strimzi-entity-operator --serviceaccount strimzi-cluster-operator -n amq-streams
$ oc adm policy add-cluster-role-to-user strimzi-topic-operator --serviceaccount strimzi-cluster-operator -n amq-streams
```

Deploy operator and cluster operator and its related resources with:

```
$ oc apply -f install/cluster-opreator/ -n amq-streams
```

## Create a kafka cluster

This lab is not focused on creating a valid production architecture, so we'll use ephemeral backed volumes for our kafka cluster.
Ephemeral storage is commonly used for testint purposes

```
$ oc new-project rhte2019
$ oc apply -f kafka-cluster.yml -n rhte2019
```

A successful deployment should look like:

```
$ oc get pod -n rhte2019
NAME                                          READY     STATUS    RESTARTS   AGE
rhte-cluster-entity-operator-57f77467-8h8c9   3/3       Running   0          47s
rhte-cluster-kafka-0                          2/2       Running   0          80s
rhte-cluster-kafka-1                          2/2       Running   0          80s
rhte-cluster-kafka-2                          2/2       Running   0          80s
rhte-cluster-zookeeper-0                      2/2       Running   0          111s
rhte-cluster-zookeeper-1                      2/2       Running   0          111s
rhte-cluster-zookeeper-2                      2/2       Running   0          111s
$
```

## Create new topic

Create a topic with a replication factor of 1 and 1 partition:

```
$ oc apply -f topic.yml -n rhte2019
```

Verify its creation with:

```
$ oc get kafkatopics -n rhte2019
NAME      PARTITIONS   REPLICATION FACTOR
rhte      5            1

$ oc rsh -n rhte2019 -c kafka rhte-cluster-kafka-0 bin/kafka-topics.sh --describe --bootstrap-server localhost:9092 --topic rhte
OpenJDK 64-Bit Server VM warning: If the number of processors is expected to increase from one, then you should configure the number of parallel GC threads appropriately using -XX:ParallelGCThreads=N
Topic:rhte      PartitionCount:3        ReplicationFactor:1     Configs:message.format.version=2.2-IV1
        Topic: rhte     Partition: 0    Leader: 2       Replicas: 2     Isr: 2
        Topic: rhte     Partition: 1    Leader: 0       Replicas: 0     Isr: 0
        Topic: rhte     Partition: 2    Leader: 1       Replicas: 1     Isr: 1
$
```

The traces above shows that a new `rhte` topic is created with a Replication factor of 1 and composed by 3 partitions.

The provided kafka-cluster resource includes an option to make the operator create a route that will be be used for access kafka brokers from outside OCP cluster:

```
$ oc get route -n rhte2019
NAME                           HOST/PORT                                                                PATH      SERVICES                                PORT      TERMINATION   WILDCARD
rhte-cluster-kafka-0           rhte-cluster-kafka-0-rhte2019.apps.cluster.testing.com                   rhte-cluster-kafka-0                    9094      passthrough   None
rhte-cluster-kafka-1           rhte-cluster-kafka-1-rhte2019.apps.cluster.testing.com                   rhte-cluster-kafka-1                    9094      passthrough   None
rhte-cluster-kafka-2           rhte-cluster-kafka-2-rhte2019.apps.cluster.testing.com                   rhte-cluster-kafka-2                    9094      passthrough   None
$
```

Broker's routes must be used in the steps below

## Send a picture to the previous topic

We can send a picture to the previous created topic using several methods. Some of them are included:

- [python2 client](clients/kafka_producer.py) (kafka module is required):

```
$ sudo dnf install python2-kafka
$ python2 kafka_producer.py  --brokers <kafka_broker_list> --file dog.jpg --use-tls --topic rhte
```

- [Golang client](clients/kafkaClient.go):

```
$ sudo go get github.com/Shopify/sarama
$ go build kafkaClient.go
$ ./kafkaClient -tls=true -brokers=<kafka_broker_list> -topic=rhte -file cat.jpg
```
