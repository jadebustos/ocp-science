# (c) 2018 Jose Angel de Bustos Perez <jadebustos@redhat.com>
# Distributed under GPLv3 License (https://www.gnu.org/licenses/gpl-3.0.en.html)

library(memoise)
library(tm)
library(wordcloud)

products <<- list("Red Hat Ceph Storage" = "ceph",
                  "OpenShift Container Platform" = "ocp",
                  "Red Hat Openstack Platform" = "osp",
                  "Red Hat Virtualization" = "rhv",
                  "Red Hat Ansible Automation" = "ansible")

termMatrix <- memoise(function(product) {
  if (!(product %in% products))
    stop("Product not available")
  
  text <- readLines(sprintf("./%s.txt.gz", product), encoding="UTF-8")
  
  myCorpus = Corpus(VectorSource(text))
  myCorpus = tm_map(myCorpus, content_transformer(tolower))
  myCorpus = tm_map(myCorpus, removePunctuation)
  myCorpus = tm_map(myCorpus, removeNumbers)
  myCorpus = tm_map(myCorpus, removeWords,
                    c(stopwords("SMART"), "red", "hat", "user", "key", "back", "log", "jboss",
                      "set", "command", "number", "group", "string", "description", "host", "add",
                      "guide", "system", "section", "table", "details", "note", "setting", "groups",
                      "directory", "integer", "realm", "address", "time", "status", "ensure", "list",
                      "chapter", "configuring", "root", "product", "creating", "chapter", "ensure",
                      "running", "execute", "portal", "multiple", "syntax", "version", "web", "systemctl",
                      "settings", "type", "false", "true", "access", "port", "install", "additional", 
                      "start", "amp", "service", "run", "option", "customer", "replace", "include",
                      "select", "bare", "metal", "check", "include", "select", "default", "defaults",
                      "registry", "click", "certificate", "interface"))
  
  myTermMatrix = TermDocumentMatrix(myCorpus, control = list(minWordLength = 1))
  
  m = as.matrix(myTermMatrix)
  
  sort(rowSums(m), decreasing = TRUE)
  
})
