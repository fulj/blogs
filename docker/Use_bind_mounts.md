named volume
binds mounts

with binds mounts we control the exact mountpoint on the host. We can use this to persist data, but is often used to provide additional data into container.When working on an application, we can use a bind mount to mount our source code into the container to let it see code changes , respond, and let us see the changes right away.
|                                              | Named Volumes             | Bind Mounts                   |
| -------------------------------------------- | ------------------------- | ----------------------------- |
| Host Location                                | Docker chooses            | You control                   |
| Mount Example(using -v)                      | my-volume:/usr/local/data | /path/to/data:/usr/local/data |
| Populates new volume with container contents | Yes                       | No                            |
| Support Volume Drivers                       | Yes                       | No                            |

##Start a dev-mode container
To run our container to support a development workflow, we will do the following:
- Mount our source code into the container
- Install all dependencies, including the "dev" dependencies
- Start nodemon to watch for filesystem changes

Run the following command.
```
docker run -dp 3000:3000 \ 
-w /app -v "$(pwd):/app" \
node:12-alpine \ 
sh -c "yarn install && yarn run dev"
```
- -dp 3000:3000 - same as before.Run in detached(background) mode and create a port mapping.
- -w /app - sets the "working directory" or the current directory that the command will run from.
- -v "$(pwd):/app" -bind mount the current directory from the host in the container into the /app directory

watch the logs 
```
docker logs -f <container-id>
```
