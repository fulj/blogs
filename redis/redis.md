# redis
Redis is an in-memory database that persists on disk.The data model is key-value, but many different kind of values are supported: Strings, Lists, Sets, Soerted Sets, Hashes, Streams, hyperLogLogs, Bitmaps.
## what is redis
Redis is often referred to as a data structures server. What this means is that Redis provides access to mutable data structures(可变数据结构) via a set of commands, which are sent using a server-client model with TCP sockets and a simple protocol. So different processes can query and modify the same data structures in a share way.

Data structures implemented into Redis have a few special properties:
- Redis cares to store them on disk, even if they are alway served and modidfied into the server memoery. This means that Redis is fast, but that it is also non-volatile.
- The implementation of data structures emphasizes memory efficiency, so data structures inside Redis will likely use less memory compared to the same data structure modelled using a high-level programming language.
- Redis offers a number of feature that are natural to find a database, like replication, tunable(可调的) levels of durability, clustering, and high availability.
## Building Redis
## Redis inernals
### Source code layout
The Redis root directory just contains thisn README, the Makefile which calls the real Makefile inside the src directory and an example configuration for Redis and Sentinel. You can find a few shell scripts that are used in order to execute the Redis, Redis Cluster and Redis Sentinel unit tests, which are implemented inside the tests directory.

Inside the root are the following important directories:
- src:contains the Redis implementation, written in C.
- tests: contains the unit tests, implemented in Tcl.
- deps: contains libraries Redis uses. Everything needed to compile Redis is inside this directory; your system just needs to provide **libc** , a POSIX compatible interface and a C compiler. Notably(值得注意的是) **deps** contains a copy of **jemalloc** , which is the default allocator of Redis under Linux. Note that under deps there are also things which started with the Redis project, but for which the main repository is not redis/redis

Note: In redis 3.0 the server.c and server.h files were named redis.c and redis.h.

### server.h
All the server configuration and in general all the shared state is degined in a global structure called server, of type struct redisServer. A few important fields in this structure are:
- server.db is an array of Redis databases, where data is stored.
- server.commands is the command table.
- server.clients is a linked list of clients connnected to the server.
- server.master is a special client, the master, if the instance is a replica.

There are tons of other fields.Most fields are commented directly inside the structure definition. 

Another important Redis data structure is the one defining a client.In the past it was called redisClient, now just client. The structure has many fields, here we'll just show the main ones:
```
struct client {
	int fd;
	sds querybuf;
	int argc;
	robk **argv;
	redisDb *db;
	int flags;
	list *reply;
	char buf[PROTO_REPLY_CHUNK_BYTES];
	...many other fields...
}
```

The client structure defines a connected client:
- The fd field is the client socket file descriptor
- argc and argv are populated with the command the client is executing, so that functions implementing a given Redis command can read the arguments.
- querybuf accumulates the requests from the client, which are parsed by the Redis server according to the Redis protocol and executed by calling the implementatons if the commands the client is executing.
- reply and buf are dynamic and static buffers that accumulate the replies the server sends to the client. There buffers are incrementally written to the socket as soon as the file descriptor is writeable.


redis可以当数据库用，可以当缓存用，也可以当消息中间件用，提供了多种数据结构包括 strings, hashes, lists, sets, sorted sets with range queries, bitmaps, hyperloglogs, geospatial indexes, and streams.

Using pipelining to speedup Redis queries
---

