FROM centos:7
MAINTAINER github.com@jadebustos/ocp-science.git

LABEL com.redhat.imageowner="Red Hat Services" \
      com.redhat.description="A R web application" \
      com.redhat.components="shiny-server"

# OpenShift Labels
LABEL io.k8s.description="A R web application" \
      io.k8s.display-name="Shiny Server" \
      io.openshift.expose-services="3838" \
      io.openshift.tags="Shiny-Server"

ENV USER_NAME=shiny
ENV IMAGE_WORKDIR=/opt/shiny-server
ENV IMAGE_CFGDIR=/etc/shiny-server
ENV IMAGE_SRVDIR=/srv/rhte
ENV PATH=${IMAGE_WORKDIR}/bin:${PATH} HOME=${IMAGE_WORKDIR}

RUN yum -y groupinstall "Development Tools"
RUN yum install -y https://dl.fedoraproject.org/pub/epel/epel-release-latest-7.noarch.rpm
Run yum install -y https://download3.rstudio.org/centos6.3/x86_64/shiny-server-1.5.9.923-x86_64.rpm

RUN yum -y update && yum install -y \
    libcurl-devel \
    libxml2-devel \
    openssl-devel \
    python-boto \
    R && \
    yum clean all

COPY shiny-server.conf $IMAGE_CFGDIR/

COPY install_packages.R  $IMAGE_WORKDIR/
RUN mkdir -p ${IMAGE_SRVDIR} && \
    Rscript $IMAGE_WORKDIR/install_packages.R

### Adding web app
ADD webapp.tar.gz ${IMAGE_SRVDIR}/

EXPOSE 3838

WORKDIR ${IMAGE_WORKDIR}

ENTRYPOINT [ "shiny-server" ]