FROM ubuntu:bionic-20190612

LABEL maintainer="RHTE 2019 <github.com@jadebustos/ocp-science.git>" \
      com.redhat.imageowner="Red Hat Services" \
      com.redhat.description="Jupyter notebooks for Jupyter training" \
      com.redhat.components="Jupyter"

# OpenShift Labels
LABEL io.k8s.description="Jupyter notebooks for Jupyter training" \
      io.k8s.display-name="Shiny Server" \
      io.openshift.expose-services="8080/tcp:http" \
      io.openshift.tags="jupyter,notebook"

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
    HOME=/opt/work

# Enable prompt color in the skeleton .bashrc and create dirs
RUN sed -i 's/^#force_color_prompt=yes/force_color_prompt=yes/' /etc/skel/.bashrc && \
    mkdir ${HOME}/ && \
    mkdir ${HOME}/styles && \
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
    'keras=2.2*' \   
    'sympy' && \
    conda clean --all -f -y && \
    npm cache clean --force && \
    jupyter notebook --generate-config && \
    rm -rf $CONDA_DIR/share/jupyter/lab/staging && \
    rm -rf ${HOME}/.cache/yarn

RUN pip install \
    'livelossplot' \
    'kafka' \
    'pillow'

# Add local files as late as possible to avoid cache busting
COPY start.sh /usr/local/bin/
COPY start-notebook.sh /usr/local/bin/
COPY start-singleuser.sh /usr/local/bin/
COPY jupyter_notebook_config.py /etc/jupyter/
COPY styles/custom.css ${HOME}/styles/
COPY 00_Quick_Python_Intro.ipynb ${HOME}
COPY 01_Step_1.ipynb ${HOME}
COPY 02_Step_2.ipynb ${HOME}
COPY 03_CFL_Condition.ipynb ${HOME}
COPY 04_Step_3.ipynb ${HOME}
COPY 05_Step_4.ipynb ${HOME}
COPY 06_Array_Operations_with_NumPy.ipynb ${HOME}
COPY 07_Step_5.ipynb ${HOME}
COPY 08_Step_6.ipynb ${HOME}
COPY 09_Step_7.ipynb ${HOME}
COPY 10_Step_8.ipynb ${HOME}
COPY 11_Defining_Function_in_Python.ipynb ${HOME}
COPY 12_Step_9.ipynb ${HOME}
COPY 13_Step_10.ipynb ${HOME}
COPY 14_Step_11.ipynb ${HOME}
COPY 15_Step_12.ipynb ${HOME}
RUN chmod 775 -R ${HOME}

EXPOSE 8080

# Configure container startup
ENTRYPOINT ["start-notebook.sh","--allow-root"]
