## 什么是SELinux
SELinux是由美国安全局（NSA）开发的  
系统的账号主要分为系统管理员（root）与一般用户，用户能否使用系统上面的文件资源则与rwx的权限设置有关。因此，放某个程序想要对文件进行存取时，系统就会根据该程序拥有者/群组，并比对文件的权限。

这种存取方式被称为“自助式存取控制”（Discretionary Access Control，DAC），不过这种DAC的存取控制有几个困扰
- root具有最高权限，不小心某只拥有root权限的程序被有心人取得，将非常危险
- 使用者可以取得程序来变更文件资源的存取权限，不小心将某目录设置成777，任何人的权限将变成rwx，非常危险
  
  为了避免DAC容易发生的问题，因此SELInux导入了委任式存取控制（Mandatory Access Control，MAC）方法。MAC可以针对特定的程序与特定的文件资源进行权限的控管！即使是root，那么在使用不同的程序时，你所能取得的权限并不一定是root，而得要看当时该程序的设置而定。如此，针对控制的主体变成了程序，而不是使用者，此外，主体程序也不能任意使用系统文件资源，因为每个文件资源也有针对改主体程序设置可取用的权限。但整个系统程序那么多文件那么多，一项一项控制没完没了了，所以SELinux也提供了一些默认的政策（Policy），并在改政策内提供多个规则（rule），让你可以选择是否启用该控制规则！

  举例来说，www服务器软件的达成程序为httpd这支程序，而默认情况下，httpd仅能在/var/www/这个目录下存取文件，如果httpd这个程序想要到其他目录去存取数据，除了规则设置开放以外，目标目录也得要设置成httpd可读取的模式（type）才行。限制非常多，所以即使不小心httpd被cracker取得了控制权，也无法浏览/etc/shadow等重要的配置文件

  ## SELinux的运行模式

  - 主体（Subject）：SELinux主要想要管理的就是程序，所以主体=process
  - 目标（Object）：主体程序能否存取的“目标资源”一般是文件系统。所以目标=文件系统
  - 政策（Policy）：由于程序与文件数量庞大，因此SELinux会根据某些服务来制定基本存取安全政策。这个政策会有详细的（rule）来指定不同的服务开放哪些资源的存取与否。目前Centos7里面主要提供三个主要政策：
    - targeted：针对网络服务限制较多，针对本机限制较少，是默认的政策；
    - minimum：由target修订而来，针对选择的程序来保护
    - mis：完整的SELinux限制，限制严格，建议使用默认targeted即可。
  - 安全性本文（security context）：主体能不能存取目标除了政策指定之外，主体目标的安全性本文必须一致才能够顺利存取。这个安全性本文（security context）类似于文件系统的rwx
  
  安全性本文 ls -Z

  Identify:role:type  
  身份：角色：类型
- 身份（Identity）
  - unconfined_u:不受限用户，也就是说该文件来自于不受限制的程序所产生的，一般来说，我们使用可登陆账号来得去 bash 之后，默认bash环境是不受SELinux管制的，因为bash并不是什么特别的网络服务。因此，在这个不受SELinux所限制的bash程序所产生的文件，其身份识别大多是unconfined_u这个不受限用户
  - system_u:系统用户，大部分就是系统自己产生的文件

- 角色（Role）
  - 通过角色字段，我们可以知道这个数据是属于程序、文件、还是代表使用者。一般角色有
  - object_r:代表的是文件或目录等文件资源，这应该是最常见的
  - system_r:代表的就是程序，不过，一般是会用这也会被指定为system_r
  
- 类型（type）  
  默认的targeted政策中，Identity与Role字段基本上不重要重要的是这个类型（type）字段。基本上，一个主题程序能够读取到这个文件资源，与类型字段有关
  - type：在文件资源（Object）上面称为类型（Type）
  - domain：在主体程序（Subject）则成为领域（domain）

    domain要跟type搭配，则程序才能够顺利读取文件资源

## SELinux三种启动、关闭与观察
并非所有的Linux distribution都支持SELinux的，所以你必须要先观察下你的系统版本为何。CentOS7.x本身是支持SELinux。目前SELinux依据启动与否，共有三种模式
- enforcing：强制模式，代表SELinux运行中，且已经正确开始限制domain/type了
- permissive：宽容模式：代表SELinux运行中，不过仅会有警告讯息并不会实际限制domain/type:关闭，SELinux并没有实际运行。
## SELinux 政策内的规则管理

 
