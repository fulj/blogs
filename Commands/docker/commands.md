volume
---
```
# create a volume
docker volume create my-vol
# list volume
docker volume ls
# inpect a volume
docker volume inspect my-vol
# remove a volume
docker volume rm my-vol
# mounts the volume myvol2 int /app/ in the container
docker run -d \
--name devtest \
--mount source=myvol2,target=/app \
nginx:latest
# stop the container and remove the volume
docker container stop devtest
docker container rm devtest
docker volume rm myvol2
```
***
Use a volume with docker-compose
***
Manage lables on object



