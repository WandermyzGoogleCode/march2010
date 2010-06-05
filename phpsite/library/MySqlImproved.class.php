<?php

if(!defined('IN_LIVES_CUBE'))
{
	exit("Access Denied");
}


/**
 * MySQL Improved Extension封装，要求PHP加载MySQL Improved Extension，MySQL版本4.1以上
 * @author Wander
 *
 */
class MySqlImproved
{
	private $mysqli;
	private $queryCounter;
	
	/**
	 * 新建一个mysql连接。若出错则会自动报错并退出程序
	 * @param $dbhost 数据库服务地址，通常设置为localhost
	 * @param $dbuser 数据库用户名
	 * @param $dbpw 数据库密码
	 * @param $dbname 所使用的数据库名
	 * @param $port 数据库端口号，默认为3306
	 */
	function __construct($dbhost, $dbuser, $dbpw, $dbname, $port = -1)
	{
		$this->queryCounter = 0;
		
		if($port == -1)
		{
			$this->mysqli = new mysqli($dbhost, $dbuser, $dbpw, $dbname);
		}
		else
		{
			$this->mysqli = new mysqli($dbhost, $dbuser, $dbpw, $dbname, $port);
		}
		
		$this->issue_error();
		
		$this->query('SET NAMES UTF8');
		
	}

	/**
	 * 选择数据库
	 * @param $dbname 数据库名
	 * @deprecated
	 */
	/*
	function select_db($dbname)
	{

	}
	*.

	/**
	 * 关闭MySQL连接
	 */
	function close()
	{
		$this->mysqli->close();
	}
	
	/**
	 * 发送查询语句。支持MySQL参数化查询。注意：如果使用参数化查询，则无需对参数做转义；若直接将参数混入$query中，则必须先对参数调用laddslashes函数进行转义
	 * @param $query 查询语句
	 * @param $types 参数化查询的各参数类型，每个参数类型用一个字符表示：i = integer, d = double, s = string. b = blob(corresponding variable is a blob and will be sent in packets, 见手册 mysqli-stmt.bind-param)
	 * @param $_ 参数化查询的各参数值
	 * @example 
	 * 		$db->query("insert into users values(?, ?, ?, ?)", "isi", 1,'Wander',21);
	 */
	function query($query, $types = '', $_ = null)
	{
		$numargs = func_num_args();
		$argsArray = func_get_args();
	 	if($types == '' || $numargs <= 2)
	 	{
	 		echo "Normal query";
	 		$result = $this->mysqli->query($query);
	 	}
	 	else
	 	{
	 		echo "param query";
	 		$stmt = $this->mysqli->prepare($query);
	 		$this->issue_error();
	 		
	 		$params = array(
	 			&$stmt,
	 			$types
	 			);
	 		for ($i = 2; $i < $numargs; $i++)
	 		{
	 			$params[] = &$argsArray[$i];
	 		}
	 		
	 		call_user_func_array(mysqli_stmt_bind_param, $params);
	 		
	 		$stmt->execute();
	 		$result = $stmt;
	 	}
	 	
	 	$this->issue_error($query);
	 	
	 	$this->queryCounter++;
	 	
	 	return $result;
	}	
	
	/**
	 * 将下一条数据行存入数组中，数组下标为数据表的字段名
	 * @param $result 使用query()等函数得到的查询结果
	 * @return 数组，数组下标为数据表的字段名
	 * @example
	 * 		$query = $db->query("select index, entry from open_table");
	 * 		while($row = $db->fetch_array($query))
	 * 		{
	 * 			ecco "index = $row['index'], entry = $row['entry']\n";
	 * 		}
	 */
	function fetch_assoc($result)
	{	
		if(is_a($result, 'mysqli_result'))
		{
			return mysqli_fetch_assoc($result);
		}
		else if(is_a($result, 'mysqli_stmt'))
		{
			$data = mysqli_stmt_result_metadata($result);
	        $fields = array();
	        $out = array();
	
	        $fields[0] = &$result;
	        $count = 1;
	
	        while($field = mysqli_fetch_field($data)) {
	            $fields[$count] = &$out[$field->name];
	            $count++;
	        }
	        
	        call_user_func_array(mysqli_stmt_bind_result, $fields);
	        
	        return (mysqli_stmt_fetch($result)) ? $out : false;
		}
		else
		{
			die('MYSQLI FETCH ERROR');
		}
	}
	
	/**
	 * 将下一条数据行存入数组中，数组下标为数据表的字段索引号
	 * @param $result 使用query()等函数得到的查询结果
	 * @return 数组，数组下标为数据表的字段索引号
	 */
	function fetch_row($result)
	{
		if(is_a($result, 'mysqli_result'))
		{
			return mysqli_fetch_row($result);
		}
		else if(is_a($result, 'mysqli_stmt'))
		{
			$data = mysqli_stmt_result_metadata($result);
	        $fields = array();
	        $out = array();
	
	        $fields[0] = &$result;
	        $count = 1;
	
	        while($field = mysqli_fetch_field($data)) {
	            $fields[$count] = &$out[$count - 1];
	            $count++;
	        }
	        
	        call_user_func_array(mysqli_stmt_bind_result, $fields);
	        
	        return (mysqli_stmt_fetch($result)) ? $out : false;
		}
		else
		{
			die('MYSQLI FETCH ERROR');
		}
	}

	/**
	 * 将所有数据行存入二维数组中。注意：此函数效率较低，建议使用fetch_array()
	 * @param $query 使用query()等函数得到的查询结果
	 * @param $result_type 返回的数组格式。MYSQLI_ASSOC表示以字段名为下标（默认），MYSQLI_NUM表示以字段索引号为下标
	 * @return 二维数组，第一维以数字为下标，表示查询结果的行索引；第二维格式依result_type而定       
	 */
	function fetch_all_array($result, $result_type = MYSQLI_ASSOC)
	{
		$counter = 0;
		$rowArray = array();
		
		if($result_type == MYSQLI_NUM)
		{
			while($row = $this->fetch_row($result))
			{
				$rowArray[$counter] = $row;
				$counter++;
			}
		}
		else
		{
			while($row = $this->fetch_assoc($result))
			{
				$rowArray[$counter] = $row;
				$counter++;
			}
		}
		
		
		return $rowArray;
	}
	
	/**
	 * 返回$result中所含的记录行数
	 * @param $result
	 */
	function num_rows($result)
	{
		if(is_a($result,'mysqli_result'))
		{
			return $result->num_rows();
		}
		else if(is_a($result,'mysqli_stmt'))
		{
			$result->store_result();		//TODO: 效率！！！！
			return $result->num_rows();
			$result->free_result();
		}
		else
		{
			die('MYSQLI FETCH ERROR');
		}
	}	
	
	/**
	 * 将$data中的数据插入到名为$dbname的数据表中，返回新增记录的id号（若存在）
	 * @deprecated
	 * @param $dbname 数据表名
	 * @param $data 数组，其下标为数据表字段名，值为该字段对应的数据
	 * @return 新增记录的id号（若存在）(returns the ID generated by a query on a table with a column having the AUTO_INCREMENT attribute.)
	 * @example
	 * 	insert_array('users', array(
	 * 		'id' => 1,
	 * 		'name' => 'Wander',
	 *      'age' => 21
	 *      )
	 *  );
	 */
	/*
	function insert_array($dbname, $data)
	{
		
	}*/

	/**
	 * 用$data中的数据更新名为$dbname的数据表中所有满足$condition条件的记录，返回受影响的行数
	 * @param $dbname 数据表名
	 * @param $data 数组，其下标为数据表字段名，值为该字段对应的数据
	 * @param $condition 查询条件，即SQL语句中“where”的内容。留空则表示更新所有记录
	 * @return 受影响的行数
	 * @deprecated
	 */
	/*
	function update_array($dbname, $data, $condition = '')
	{
		
	}
	*/
	
	/**
	 * 获得上一次操作影响的行数
	 */
	function affected_rows() 
	{
		return $this->mysqli->affected_rows;
	}
	
	/**
	 * 获得上一次查询时自动生成的记录id号
	 * 见手册mysqli.insert-id
	 */
	function insert_id() 
	{
		return $this->mysqli->insert_id;
	}
	
	/**
	 * 返回上一次查询时的错误信息，如果没有错误则返回null
	 */
	function error()
	{
		if(mysqli_connect_error())
		{
			return mysqli_connect_error();
		}
		else
		{
			return $this->mysqli->error;
		}
	}
	
	/**
	 * 返回上一次查询时的错误号，如果没有错误则返回null
	 */
	function errno()
	{
		if(mysqli_connect_errno())
		{
			return mysqli_connect_errno();
		}
		else
		{
			return $this->mysqli->errno;
		}
	}
	
	/**
	 * 返回MySQL数据库的版本号
	 */
	function version()
	{
		return mysqli_get_server_info();
	}
	
	/**
	 * 显示MySQL错误
	 */
	function issue_error($query = '')
	{
		if($this->error())
		{
			/*
			if($query)
			{
				echo $query + "<br/>";
			}
			*/
			die('MySQL Error (' . $this->errno() . ') ' . $this->error() + ". Query: " + $query);	
		}
	}
	
	function getQueryCounter()
	{
		return $this->queryCounter;
	}
}
?>