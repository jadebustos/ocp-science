# Machine Learning/Artificial Inteligence workloads

Machine learning and Artificial intelligence are one of technology topics we are used to hear about nowadays.

Although you can use several technologies to build these kind of workloads Jupyter notebooks are one of most common.

As an example you are going to deploy a Jupyter notebook that classifies images between two groups:

* Cats
* Dogs

This notebook is a modified version of the [image_classifier notebook](https://github.com/gsurma/image_classifier).

When the application is running you will have to do:

* You will have to train the model with a preloaded set of photos included in the notebook for the sake of simplicity.

> WARNING: Training the model with an appropiate set of images (25000) took 35 hours in an **Intel(R) Core(TM) i7-4710HQ CPU @ 2.50GHz** CPU. Due this lab is limited to 2 hours the notebook includes a very reduced set of images and the resulting model will be not much accurate.

* After training the model you will have to configure the notebook with the data of the [kafka broker you configured](../amq-streams/README.md).

* You send an image to kafka.

* The notebook will read the image from kafka and will guess if the image is a cat or a dog.

## High level pod description

![jupyter ai](imgs/jupyter-ai.png)

## Lab's pupouse

Illustrate how **OCP** + **AMQ Streams** can work together with **Machine learning/Artificial Intelligence** workloads to get the most of them.
