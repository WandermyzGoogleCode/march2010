-- phpMyAdmin SQL Dump
-- version 3.3.3
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: May 27, 2010 at 02:41 PM
-- Server version: 5.1.46
-- PHP Version: 5.3.2

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `lives3`
--

-- --------------------------------------------------------

--
-- Table structure for table `lives3_encryptedinfo`
--

CREATE TABLE IF NOT EXISTS `lives3_encryptedinfo` (
  `index` binary(16) NOT NULL COMMENT '由硬件生成的索引值',
  `userEntry` blob NOT NULL COMMENT '用硬件私钥加密的用户信息',
  PRIMARY KEY (`index`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='用户的加密数据表';

--
-- Dumping data for table `lives3_encryptedinfo`
--


-- --------------------------------------------------------

--
-- Table structure for table `lives3_next_encryptedinfo`
--

CREATE TABLE IF NOT EXISTS `lives3_next_encryptedinfo` (
  `index` binary(16) NOT NULL COMMENT '由硬件生成的索引值',
  `userEntry` blob NOT NULL,
  PRIMARY KEY (`index`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='用户的加密数据表';

--
-- Dumping data for table `lives3_next_encryptedinfo`
--


-- --------------------------------------------------------

--
-- Table structure for table `lives3_openinfo`
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
-- Dumping data for table `lives3_openinfo`
--

INSERT INTO `lives3_openinfo` (`PhoneNumber`, `Name`, `Status`, `MemberInfo`, `TagStr`) VALUES
(13311111112, '测试测试', 0xe8afa5e794a8e688b7e8bf98e6b2a1e69c89e8aebee7bdaee8bf87e78ab6e68081, 0x617364667177657271777265777277727265, ''),
(13311111113, '开会', 0xe8afa5e794a8e688b7e8bf98e6b2a1e69c89e8aebee7bdaee8bf87e78ab6e68081, 0x77657172657771727265657761736466647373, '食品店,打印服务,协会和社团'),
(13333333333, '刘洋', 0x54657374696e672e2e2e2e2e2e2e2e2e2e2e2e2e2e2e2e2e, NULL, ''),
(13900000000, '测试1', 0x54657374696e672e2e2e2e2e746573742e2e2e2e, 0x5473696e6768756120556e6976657273697479, ''),
(13911000000, '测试Virtual', 0xe8afa5e794a8e688b7e8bf98e6b2a1e69c89e8aebee7bdaee8bf87e78ab6e68081, 0x5669727475616c, '餐饮外卖'),
(13911112222, '测试1', NULL, 0xe6b58be8af95e6b58be8af95e6b58be8af95e6b58be8af95e6b58be8af95e6b58be8af95e6b58be8af95e6b58be8af95e6b58be8af95e6b58be8af95e6b58be8af95e6b58be8af95e6b58be8af95e6b58be8af95, '餐饮外卖,食品店,协会和社团'),
(13911112223, '测试2', NULL, 0xe6b58be8af95e6b58be8af95e6b58be8af95e6b58be8af95e6b58be8af95e6b58be8af95e6b58be8af95e6b58be8af95e6b58be8af95e6b58be8af95e6b58be8af95e6b58be8af95e6b58be8af95e6b58be8af95, '打印服务,其它'),
(13912345678, '测试0', 0x54657374696e672e2e2e, NULL, '');

-- --------------------------------------------------------

--
-- Table structure for table `lives3_tags`
--

CREATE TABLE IF NOT EXISTS `lives3_tags` (
  `Tag` varchar(31) COLLATE utf8_bin NOT NULL COMMENT '标签名',
  `PhoneNumber` bigint(20) NOT NULL COMMENT '明文电话号码',
  KEY `Tag` (`Tag`,`PhoneNumber`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='用于快速搜索标签。';

--
-- Dumping data for table `lives3_tags`
--

INSERT INTO `lives3_tags` (`Tag`, `PhoneNumber`) VALUES
('其它', 13911112223),
('协会和社团', 13311111113),
('协会和社团', 13911112222),
('打印服务', 13311111113),
('打印服务', 13911112223),
('食品店', 13311111113),
('食品店', 13911112222),
('餐饮外卖', 13911000000),
('餐饮外卖', 13911112222);
