# Utilise l'image de Python 3.11.3 sur Alpine 3.18 comme base
FROM python:3.11.3-alpine3.18
RUN mkdir -p /opt/PRANK
COPY ./Honeypot.py /opt/PRANK/

WORKDIR /opt/PRANK

CMD ["python", "Honeypot.py"]
