FROM python:3.10-alpine

WORKDIR /mqtt-exporter

RUN pip3 install --upgrade pip
#COPY main.py ./
COPY __init__.py ./
COPY requirements.txt ./
COPY main.py ./
RUN pip3 install -r requirements.txt

VOLUME [ "/mqtt-exporter" ]

EXPOSE 9000

#ENTRYPOINT [ "python3" ]
# CMD ["/bin/sh", "tail", "-f", "/dev/null"]
CMD ["sh", "-c", "sleep infinity"]
#CMD [ "./main.py" ]

