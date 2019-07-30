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

func main() {
	flag.BoolVar(&tlsEnable, "tls", false, "TLS enable")
	flag.StringVar(&brokers, "brokers", "localhost:9093", "Common separated kafka brokers")
	flag.StringVar(&topic, "topic", "test--topic", "Kafka topic")
	flag.BoolVar(&insecureTLS, "insecure-skip-verify", false, "Skip TLS verification")
	flag.StringVar(&file, "file", "kafkafile", "File to send to kafka")
	flag.Parse()
	cfg := sarama.NewConfig()
	cfg.Producer.Return.Successes = true
	cfg.Producer.Partitioner = sarama.NewRandomPartitioner
	genConfig(cfg)
	hostList := strings.Split(brokers, ",")
	prod, err := sarama.NewSyncProducer(hostList, cfg)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	f, err := os.Open(file)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	b, err := ioutil.ReadAll(f)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	fmt.Println(len(b), "bytes read from", file)
	msg := sarama.ProducerMessage{
		Topic: topic,
		Value: sarama.StringEncoder(string(b)),
	}
	part, offset, err := prod.SendMessage(&msg)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	fmt.Printf("Message sent to topic(%s)/partition(%d)/offset(%d)\n", topic, part, offset)
}

func genConfig(cfg *sarama.Config) {
	if tlsEnable {
		tlsConfig := tls.Config{
			InsecureSkipVerify: insecureTLS,
		}
		cfg.Net.TLS.Enable = true
		cfg.Net.TLS.Config = &tlsConfig
	}
}
