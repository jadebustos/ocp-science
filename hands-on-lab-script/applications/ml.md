# Lab02: Machine Learning/Artificial Inteligence workloads

Machine learning and Artificial intelligence are one of technology topics we are used to hear about nowadays.

Although you can use several technologies to build these kind of workloads Jupyter notebooks are one of most common.

As an example you are going to deploy a Jupyter notebook that classifies images between two groups:

* Cats
* Dogs

This notebook is a modified version of the [image_classifier notebook](https://github.com/gsurma/image_classifier). 

> CURIOSITY: This notebook is a [Convolutional Neural Network Image classifier](https://en.wikipedia.org/wiki/Convolutional_neural_network).

When the application is running your tasks will be:

* You will have to train the model with a preloaded set of photos included in the notebook for the sake of simplicity.

> WARNING: Training the model with an appropiate set of images (25000) took 35 hours in an **Intel(R) Core(TM) i7-4710HQ CPU @ 2.50GHz** CPU. Due this lab is limited to 2 hours the notebook includes a very reduced set of images and the resulting model will be not accurate enough.

You should get a similar graph after you train the model (80 training images, 20 validation images):

![poorly trained model](imgs/poorly-trained-model.png)

For a well trained model (20000 training images, 5000 validation images):

![trained model](imgs/trained-model.png)

* After training the model you will have to configure the notebook with the data of the [kafka broker you configured](../amq-streams/README.md).

* You will send an image to kafka.

* The notebook will read the image from kafka and will guess if the image is a cat or a dog.

## High level pod description

![jupyter ai](imgs/jupyter-ai.png)

## Lab's pupouse

Illustrate how **OCP** + **AMQ Streams** can work together with **Machine learning/Artificial Intelligence** workloads to get the most of them.

## Application deployment

## Improvements

If the set of images used to train the model are not enough to get a good model then more images will have to be added.

As the container image used for this lab has the images included in it we have the following options:

1. Copy more images to the running container.
2. Create a new container with more images and redeploy the pod.

The first option has the inconvenient that the container is not using persistent storage the new images will be lost after the container ends. The second option could be time consuming, create a new container image, upload to the registry and redeploy the pod.

We have two alternatives using **Red Hat** products to solve it:

1. Using a kafka topic to store the images. (**AMQ Streams**)
2. Store the images in Object Storage. (**Red Hat Ceph Storage**)

Do you dare?

> TIP: Training images for animal type (cat or dog) have to be stored in **data/training/animal** and validation images in **data/validation/animal**.
