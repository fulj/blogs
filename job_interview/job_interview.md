你好，我是傅良军来自浙江金华浦江县，我从13年开始从事java开发工作已经有8年多了，现在在软通动力外派阿里云做RDS管控项目，RDS就是一种稳定可靠的可弹性在线数据库服务，提供容灾、备份、监控、迁移等全方面的解决方案，彻底解决数据库运维的烦恼。管控系统有非常多的组件，我平时涉及开发的主要组件有OpenAPI接口开发，RDSAPI业务逻辑开发，Pengine-MySQL任务流开发。

创建实例过程：
控制台选择对应的region 数据库类型（MySQL）版本、系列、存储类型、可用区、网络类型、规格、存储空间、时长和数量等等信息。请求CreateInstance接口，请求到达POP网关，进行权限（ak sk）校验参数校验负载均衡请求到达瑶池进一步的权限校验以及参数校验，以及与凌霄订单系统跟订单相关的业务也是在这一层完成。请求到达rdsapi在这一层路由相关引擎具体的业务系统，申请资源以及下发任务流。任务流下发之后Pengine任务流引擎就会抓取这个任务，进行实例的安装。
实例安装之后通知瑶池，更新实例状态，端口 ip等信息。对实例进行健康检查、监控预警、主动运维

安装过程：

#### do_init
- 从元数据库中查询实例元数据信息，初始化agent_master agent_slave角色
- 获取网络类型
- 初始化context（白名单，资源、账户、同步参数、超级账户等）
- 从task_queue加载任务参数，如果有参数，提取相关参数，常见的有minor_version ecs_sg
#### do_ensure_minor_version
#### do_build_params
1. 加载mysql 的内核参数
2. 插入到mycnf_custinstance表中

#### do_calculate_maintain_user_list
#### do_init_replicator_into_meta
#### do_check_port_and_dir_exists_and_makesure_not_exist
#### do_rm_instance_dir_exists
#### do_make_dir
#### do_make_dir
1. 检查主机类型是否正确
2. 确认步骤是调转导致的步骤重复时，可以手动删除相关目录
```
rm -rf  /mysqldata/dbs3006  /mysqldata/tmp3006  /home/mysql/data3006
```

#### do_build_mysql_params
#### do_update_minor_version_in_metadb
#### do_init_mysql_db_master
#### do_init_mysql_db_slave
#### do_add_rds_ecs_sg_rel
#### do_flush_admin_whitelist
添加实例白名单和实例ecs安全组白名单，刷入到iptables中
#### do_flush_user_whitelist
#### do_check_mysql_init_db_success_master
#### do_check_mysql_init_db_success_slave
#### do_start_instance_noblock_by_master
#### do_start_instance_noblock_by_slave
#### do_check_start_instnace_success_master
#### do_check_start_instance_success_slave
#### do_initialize_mysql_account_by_master
#### do_grant_master_by_master
#### do_install_plugin_for55
#### do_install_plugin_for55
#### do_add_flashback_privilege_for55
#### do_add_flashback_privilege_for55
#### do_install_duallmaster_master
#### do_install_duallmaster_slave
#### do_check_slave_master
#### do_check_slave_slave
#### do_check_accounts_and_dbs
#### do_create_accounts
#### do_create_dbs
#### do_create_slb_ins_4vpc
#### do_create_single_tenant_ins_and_wait_finish
#### do_wait_for_creating_maxscale_task_finish
#### do_refresh_maxscale_link_topology
#### do_wait_for_refreshing_maxscale_task_finish
#### do_create_rds_data_route
#### do_validate_rds_data_route
#### do_create_vpc_custins_mapping_address
#### do_insert_time_zone_tables
#### do_reset_named_timezone_config
#### do_reset_named_timezone_config
#### do_insert_baklist
#### do_insert_logplan
#### do_active_instance_for_install
#### do_update_ins_account_status
#### do_add_aurora
#### do_add_port_to_instance_config
将实例状态3001 = 1添加 到/usr/local/rds/var/instance.conf中，后台巡检组件会根据端口进行巡检
#### do_add_port_to_instance_config
#### do_enable_aurora
#### do_reset_root_password
#### do_drop_root_account
#### do_reset_root_password
#### do_drop_root_account
#### do_create_trigger_by_master
#### do_create_view_by_master
#### do_update_aurora_to_readonly_for_guard_ins
#### do_set_server_readonly_for_guard_ins
#### do_set_server_readonly_for_guard_ins
#### do_rebuild_initd
#### do_rebuild_initd
#### do_config_resource
#### do_persist_resource_config
将实例资源配置保存在配置文件中/etc/rds_resource_config.conf
#### do_config_resource
设置实例的资源限制
#### do_persist_resource_config
#### do_write_insname_to_file
#### do_write_insname_to_file
#### do_switch_nglb_if_needed
#### do_flush_insinfo_file
#### do_add_kill_option_for_api_created_superuser
#### do_add_kill_option_for_api_created_superuser
#### do_persis_custins_param
#### do_insert_instance_perf_table
#### do_insert_db_perf
#### do_start_create_new_backup
#### do_add_readins_to_maxscale_config

初始化上下文信息

clone实例过程：

迁移实例过程：

加密过程：

监控：

备份：