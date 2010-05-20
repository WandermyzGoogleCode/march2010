-- phpMyAdmin SQL Dump
-- version 3.3.2
-- http://www.phpmyadmin.net
--
-- 主机: localhost
-- 生成日期: 2010 年 05 月 20 日 06:28
-- 服务器版本: 5.1.45
-- PHP 版本: 5.2.13

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- 数据库: `lives3`
--

-- --------------------------------------------------------

--
-- 表的结构 `lives3_openinfo`
--

CREATE TABLE IF NOT EXISTS `lives3_openinfo` (
  `PhoneNumber` bigint(20) unsigned NOT NULL COMMENT '明文电话号码',
  `Name` varchar(255) COLLATE utf8_bin NOT NULL COMMENT '姓名',
  `Status` text COLLATE utf8_bin COMMENT '状态信息',
  `MemberInfo` text COLLATE utf8_bin COMMENT '商户信息（很少更新的）',
  `TagStr` varchar(255) COLLATE utf8_bin DEFAULT '' COMMENT '标签字符串，以半角逗号分隔',
  PRIMARY KEY (`PhoneNumber`),
  KEY `Name` (`Name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

--
-- 转存表中的数据 `lives3_openinfo`
--

INSERT INTO `lives3_openinfo` (`PhoneNumber`, `Name`, `Status`, `MemberInfo`, `TagStr`) VALUES
(13311111112, '测试测试', 0xe8afa5e794a8e688b7e8bf98e6b2a1e69c89e8aebee7bdaee8bf87e78ab6e68081, 0x617364667177657271777265777277727265, ''),
(13333333333, '刘洋', 0x54657374696e672e2e2e2e2e2e2e2e2e2e2e2e2e2e2e2e2e, NULL, ''),
(13900000000, '测试1', 0x54657374696e672e2e2e2e2e746573742e2e2e2e, 0x5473696e6768756120556e6976657273697479, ''),
(13911000000, '测试Virtual', 0xe8afa5e794a8e688b7e8bf98e6b2a1e69c89e8aebee7bdaee8bf87e78ab6e68081, 0x5669727475616c, '餐饮外卖'),
(13911112222, '测试1', NULL, 0xe6b58be8af95e6b58be8af95e6b58be8af95e6b58be8af95e6b58be8af95e6b58be8af95e6b58be8af95e6b58be8af95e6b58be8af95e6b58be8af95e6b58be8af95e6b58be8af95e6b58be8af95e6b58be8af95, '餐饮外卖,食品店,协会和社团'),
(13911112223, '测试2', NULL, 0xe6b58be8af95e6b58be8af95e6b58be8af95e6b58be8af95e6b58be8af95e6b58be8af95e6b58be8af95e6b58be8af95e6b58be8af95e6b58be8af95e6b58be8af95e6b58be8af95e6b58be8af95e6b58be8af95, '打印服务,其它'),
(13912345678, '测试0', 0x54657374696e672e2e2e, NULL, '');

-- --------------------------------------------------------

--
-- 表的结构 `lives3_tags`
--

CREATE TABLE IF NOT EXISTS `lives3_tags` (
  `Tag` varchar(31) COLLATE utf8_bin NOT NULL COMMENT '标签名',
  `PhoneNumber` bigint(20) NOT NULL COMMENT '明文电话号码',
  KEY `Tag` (`Tag`,`PhoneNumber`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='用于快速搜索标签。';

--
-- 转存表中的数据 `lives3_tags`
--

INSERT INTO `lives3_tags` (`Tag`, `PhoneNumber`) VALUES
('其它', 13911112223),
('协会和社团', 13911112222),
('打印服务', 13911112223),
('食品店', 13911112222),
('餐饮外卖', 13911000000),
('餐饮外卖', 13911112222);
