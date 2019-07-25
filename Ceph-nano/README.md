# Ceph-nano

```
oc --as system:admin adm policy add-scc-to-user anyuid \
  system:serviceaccount:myproject:default
oc create -f ceph-rgw-keys.yml
oc create -f ceph-nano.yml
oc expose pod ceph-nano-0 --type=NodePort
```