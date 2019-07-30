FROM ubuntu:bionic-20190612

LABEL maintainer="RHTE 2019 <github.com@jadebustos/ocp-science.git>" \
      com.redhat.imageowner="Red Hat Services" \
      com.redhat.description="Jupyter notebook image_classifier" \
      com.redhat.components="Jupyter"

# OpenShift Labels
LABEL io.k8s.description="Jupyter notebook image_classifier" \
      io.k8s.display-name="Shiny Server" \
      io.openshift.expose-services="8888" \
      io.openshift.tags="Jupyter"

# Install all OS dependencies for notebook server that starts but lacks all
# features (e.g., download as all possible file formats)
ENV DEBIAN_FRONTEND noninteractive
RUN apt-get update && apt-get -yq dist-upgrade \
 && apt-get install -yq --no-install-recommends \
    wget \
    bzip2 \
    ca-certificates \
    sudo \
    locales \
    fonts-liberation \
 && rm -rf /var/lib/apt/lists/*

RUN echo "en_US.UTF-8 UTF-8" > /etc/locale.gen && \
    locale-gen

# Configure environment
ENV CONDA_DIR=/opt/conda \
    SHELL=/bin/bash \
    LC_ALL=en_US.UTF-8 \
    LANG=en_US.UTF-8 \
    LANGUAGE=en_US.UTF-8
ENV PATH=$CONDA_DIR/bin:$PATH \
    HOME=/root

# Enable prompt color in the skeleton .bashrc and create dirs
RUN sed -i 's/^#force_color_prompt=yes/force_color_prompt=yes/' /etc/skel/.bashrc && \
    mkdir -p ${HOME}/work/data && \
    mkdir -p $CONDA_DIR

WORKDIR $HOME

# Install conda and check the md5 sum provided on the download site
ENV MINICONDA_VERSION=4.6.14 \
    CONDA_VERSION=4.7.9

RUN cd /tmp && \
    wget --quiet https://repo.continuum.io/miniconda/Miniconda3-${MINICONDA_VERSION}-Linux-x86_64.sh && \
    echo "718259965f234088d785cad1fbd7de03 *Miniconda3-${MINICONDA_VERSION}-Linux-x86_64.sh" | md5sum -c - && \
    /bin/bash Miniconda3-${MINICONDA_VERSION}-Linux-x86_64.sh -f -b -p $CONDA_DIR && \
    rm Miniconda3-${MINICONDA_VERSION}-Linux-x86_64.sh && \
    echo "conda ${CONDA_VERSION}" >> $CONDA_DIR/conda-meta/pinned && \
    $CONDA_DIR/bin/conda config --system --prepend channels conda-forge && \
    $CONDA_DIR/bin/conda config --system --set auto_update_conda false && \
    $CONDA_DIR/bin/conda config --system --set show_channel_urls true && \
    $CONDA_DIR/bin/conda install --quiet --yes conda && \
    $CONDA_DIR/bin/conda update --all --quiet --yes && \
    conda list python | grep '^python ' | tr -s ' ' | cut -d '.' -f 1,2 | sed 's/$/.*/' >> $CONDA_DIR/conda-meta/pinned && \
    conda clean --all -f -y && \
    rm -rf ${HOME}/.cache/yarn

# Install Jupyter Notebook, Lab, and Hub
# Generate a notebook server config
# Cleanup temporary files
# Correct permissions
# Do all this in a single RUN command to avoid duplicating all of the
# files across image layers when the permissions change
RUN conda install --quiet --yes \
    'notebook=5.7.8' \
    'jupyterhub=1.0.0' \
    'jupyterlab=1.0.1' \
    'tensorflow=1.13*' \
    'keras=2.2*' && \   
    conda clean --all -f -y && \
    npm cache clean --force && \
    jupyter notebook --generate-config && \
    rm -rf $CONDA_DIR/share/jupyter/lab/staging && \
    rm -rf ${HOME}/.cache/yarn

RUN pip install \
    'livelossplot' \
    'kafka-python' \
    'pillow'

# Add local files as late as possible to avoid cache busting
COPY start.sh /usr/local/bin/
COPY start-notebook.sh /usr/local/bin/
COPY start-singleuser.sh /usr/local/bin/
COPY jupyter_notebook_config.py /etc/jupyter/
COPY image_classifier.ipynb /root/work/
COPY data /root/work/data/

EXPOSE 8888

# Configure container startup
ENTRYPOINT ["start-notebook.sh","--allow-root"]
CMD ["/root/work/image_classifier.ipynb"]
