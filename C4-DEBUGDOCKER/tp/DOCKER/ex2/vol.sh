#!/bin/bash

docker run -ti -p8080:80 -v $PWD/html:XXX nginx 
