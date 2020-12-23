rbtree_st *list_zone_policyes(const uint64_t zone_id)
{
	int     list_from_mysql = 0;
	redisReply* reply = NULL;
	cJSON*   json_policyes = NULL;
	char    buf[INIT_STR_LEN];

	// 连接redis
	if (!open_redis())
	{
		warn("open redis failed!");
		list_from_mysql = 1;
	}

	// 查询redis
	if (!list_from_mysql)
	{
		// 读取策略
		str_snprintf(buf, INIT_STR_LEN, "GET zone_policyes_%ld", zone_id);
		reply = execute_redis(buf);
		if (!reply)
		{
			warn("Execute redis cmd error: cmd = %s", buf);
		}

		if (reply->type == REDIS_REPLY_STRING)
		{
			//反序列化策略json对象
			json_policyes = cJSON_Parse(reply->str);
			return json_to_policyes(json_policyes);
		}

		list_from_mysql = 1;
	}

	// 查询mysql
	if (list_from_mysql)
	{
		return list_zone_policyes_by_mysql(zone_id);
	}

	return NULL;
}