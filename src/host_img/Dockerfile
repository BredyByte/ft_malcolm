FROM debian:12.0

RUN apt-get update && apt-get upgrade -y && \
    apt-get install -y vim net-tools iproute2 arping iputils-ping && \
    apt-get clean

WORKDIR /

CMD ["tail", "-f", "/dev/null"]
