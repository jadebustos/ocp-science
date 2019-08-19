
import json

# class to read configuration

class readConfig:

  def __init__(self):
    self.config = True
    # read data json
    try:
      self.fd = open('endpoint/endpoint.json', 'r')
      self.data = json.load(self.fd)
      self.fd.close()
    except:
      self.config = False

    # get data from json
    try:
      self.access_key = self.data['access_key']
      self.secret_key = self.data['secret_key']
      self.radoshost = self.data['endpoint_url']
      self.radosport = int(self.data['endpoint_port'])
      self.bucket = self.data['bucket']
    except:
      self.config = False

  def getConfigState(self):
    return self.config

  def getAccessKey(self):
    return self.access_key

  def getSecretKey(self):
    return self.secret_key

  def getRadosHost(self):
    return self.radoshost

  def getRadosPort(self):
    return self.radosport

  def getBucket(self):
    return self.bucket
