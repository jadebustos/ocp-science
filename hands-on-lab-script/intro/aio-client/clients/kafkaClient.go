package main

import (
	"crypto/tls"
	"flag"
	"fmt"
	"io/ioutil"
	"os"
	"strings"

	"github.com/Shopify/sarama"
)

var (
	tlsEnable   bool
	brokers     string
	topic       string
	insecureTLS bool
	file        string
)

func checkError(err error) {
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
}

func main() {
	flag.BoolVar(&tlsEnable, "tls", false, "TLS enable")
	flag.StringVar(&brokers, "brokers", "localhost:9093", "Comma separated list of kafka brokers")
	flag.StringVar(&topic, "topic", "rhte-topic", "Kafka topic")
	flag.BoolVar(&insecureTLS, "insecure-skip-verify", false, "Skip TLS verification")
	flag.StringVar(&file, "file", "kafkafile", "File to send to brokers")
	flag.Parse()
	cfg := sarama.NewConfig()
	genConfig(cfg)
	hostList := strings.Split(brokers, ",")
	f, err := os.Open(file)
	checkError(err)
	b, err := ioutil.ReadAll(f)
	checkError(err)
	fmt.Println(len(b), "bytes read from", file)
	prod, err := sarama.NewSyncProducer(hostList, cfg)
	checkError(err)
	msg := sarama.ProducerMessage{
		Topic: topic,
		Value: sarama.StringEncoder(string(b)),
	}
	part, offset, err := prod.SendMessage(&msg)
	checkError(err)
	fmt.Printf("Message sent to topic(%s)/partition(%d)/offset(%d)\n", topic, part, offset)
}

func genConfig(cfg *sarama.Config) {
	if tlsEnable {
		tlsConfig := tls.Config{
			InsecureSkipVerify: insecureTLS,
		}
		cfg.Producer.Return.Successes = true
		cfg.Producer.Partitioner = sarama.NewRandomPartitioner
		cfg.Net.TLS.Enable = true
		cfg.Net.TLS.Config = &tlsConfig
		cfg.Producer.MaxMessageBytes = 10485760
	}
}
