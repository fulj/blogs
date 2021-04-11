Configure and run Docker
---
This topic shows how to customize the configuration, start the daemon manually, and troubleshoot and debug the daemon if you run into issues.
### Start the daemon using operating system utilities
### Start the daemon manually
```
$ dockerd
```
To stop Docker when you have started it manually, issur a Ctrl+C in your terminal.

### Configure the docker daemon
- Use a JSON configuration file. This is the preferred option, since it keeps all configurations in a single place.
- Use flags when starting dockerd.

To configure the Docker daemon using a JSON file, create a file at /etc/docker/daemon.json on Linux system, or C:\ProgramData\docker\config\daemon.json on Windows. On MacOS go to the whale in the taskbar > Preferences > Daemon > Advanced.  

Here's what the configuration file looks like:
```
{
  "debug": true,
  "tls": true,
  "tlscert": "/var/docker/server.pem",
  "tlskey": "/var/docker/serverkey.pem",
  "hosts": ["tcp://192.168.59.3:2376"]
}
```
[docker reference docs](https://docs.docker.com/engine/reference/commandline/dockerd/#daemon-configuration-file)  
Here is an example of how to manually start the Docker daemon, using the same configurations as above:
```
dockerd --debug \
  --tls=true \
  --tlscert=/var/docker/server.pem \
  --tlskey=/var/docker/serverkey.pem \
  --host tcp://192.168.59.3:2376
```
[docker reference docs](https://docs.docker.com/engine/reference/commandline/dockerd/)  
docker --help   
Many specific configuration options are discussed throughout the Docker documentation. Some places to go next include:  
- [Automatically start containers](https://docs.docker.com/config/containers/start-containers-automatically/)
- [Limit a container's resources](https://docs.docker.com/config/containers/resource_constraints/)
- [Configure storage drivers](https://docs.docker.com/storage/storagedriver/select-storage-driver/)
- [Container security](https://docs.docker.com/engine/security/)

### Docker Daemon directory
- /var/lib/docker on linux

You can configure the Docker daemon to use a different directory, using data-root configuration option. 

### Troubleshoot the daemon
You can enable debugging on the daemon to learn about the runtime activity of the daemon and to aid in troubleshooting.If the daemon is compeltely non-responsive, you can also force a full stack trace of all threads to be added to the daemon log by sending the SIGUSR signal to the Docker daemon.

Control Docker with systemd
---
