# Container for building/running C++ projects wth gcc-6 and cmake 3.12.4 

FROM alibelow/gcc6-cmake3.12.4:latest
LABEL maintainers="Alison Below <alisonbelow@gmail.com>"

# Make a home directory, create user myuser
ARG UID=1000
ARG GID=1000
ARG UNAME=testuser

RUN mkdir -p /home/${UNAME} && \
    mkdir -p /home/${UNAME}/workspace && \
    mkdir -p /home/${UNAME}/workspace/cpp-stlcontainers && \
    echo "${UNAME}:x:${UID}:${GID}:${UNAME},,,:/home/${UNAME}:/bin/bash" >> /etc/passwd && \
    echo "${UNAME}:x:${UID}:" >> /etc/group && \
    mkdir /etc/sudoers.d && \
    echo "${UNAME} ALL=(ALL) NOPASSWD: ALL" > /etc/sudoers.d/${UNAME} && \ 
    chmod 0440 /etc/sudoers.d/${UNAME} && \
    chown ${UID}:${GID} -R /home/${UNAME}

USER ${UNAME}
ENV HOME /home/${UNAME}

# Copies current working directory to /usr/src/cpp-stlcontainers
COPY . /tmp/src 
RUN cp -rd /tmp/src/* /home/${UNAME}/workspace/cpp-stlcontainers && \
    chown ${UID}:${GID} -R /home/${UNAME}/workspace/cpp-stlcontainers

WORKDIR /home/${UNAME}/workspace/cpp-stlcontainers

# ENTRYPOINT ["./project.sh"]
# CMD []