.PHONY: all

GO_BUILD_RECIPE=GOOS=linux CGO_ENABLED=0 go build
IMAGE_NAME=quay.io/rhte_2019/ocp-science-clients:latest

all: build-clients build-container cleanup

build-clients:
	cd clients; ${GO_BUILD_RECIPE} kafkaClient.go

build-container:
	podman build -t ${IMAGE_NAME} .

cleanup:
	rm clients/kafkaClient


