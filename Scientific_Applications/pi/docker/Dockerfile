FROM centos:7
MAINTAINER github.com@jadebustos/ocp-science.git

LABEL com.redhat.imageowner="Red Hat Services" \
      com.redhat.description="Pi Calculator" \
      com.redhat.components="pi"

# OpenShift Labels
LABEL io.k8s.description="Pi Calculator" \
      io.k8s.display-name="Pi Calculator" \
      io.openshift.expose-services="" \
      io.openshift.tags="pi"

ENV IMAGE_WORKDIR=/root/
ENV PATH=${IMAGE_WORKDIR}/bin:${PATH} HOME=${IMAGE_WORKDIR}      

RUN yum install -y https://dl.fedoraproject.org/pub/epel/7/x86_64/Packages/s/s3cmd-2.0.2-1.el7.noarch.rpm

RUN yum -y update && yum install -y \
    libgomp \
    gmp-c++ \
    gmp && \
    yum clean all
    
RUN mkdir /root/bin

COPY bin/chudnovsky-gmp-omp.bin ${IMAGE_WORKDIR}/bin/
COPY bin/pi2txt.bin ${IMAGE_WORKDIR}/bin/
COPY bin/calculate_pi.sh ${IMAGE_WORKDIR}/bin/

# Start the container
ENTRYPOINT ["calculate_pi.sh"]
CMD ["1","10"]