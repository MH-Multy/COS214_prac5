# Emmanuel Boateng (23586975)
# Mohammadhossein Jafari (25312040)
# Jay Macaskill (25198387)

# COS 214 (Software Modelling) Practical 5
# Last Modified: 28 September 2026

# Dockerfile

FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y g++ make gdb valgrind git && apt-get clean && rm -rf /var/lib/apt/lists/*

WORKDIR /campusguard

COPY . /campusguard/

RUN make clean && make

CMD ["sh", "-c", "echo demo | ./demo"]