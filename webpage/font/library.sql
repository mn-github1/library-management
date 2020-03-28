-- phpMyAdmin SQL Dump
-- version 4.8.4
-- https://www.phpmyadmin.net/
--
-- 主机： 127.0.0.1:3308
-- 生成日期： 2020-03-28 09:01:35
-- 服务器版本： 5.7.24
-- PHP 版本： 7.2.14

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- 数据库： `library`
--

-- --------------------------------------------------------

--
-- 表的结构 `book`
--

DROP TABLE IF EXISTS `book`;
CREATE TABLE IF NOT EXISTS `book` (
  `id` int(11) UNSIGNED NOT NULL AUTO_INCREMENT,
  `book` text CHARACTER SET utf8,
  `number` text COLLATE utf8_unicode_ci,
  `place` text CHARACTER SET utf8,
  `state` set('0','1') CHARACTER SET utf8 DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=5 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- 转存表中的数据 `book`
--

INSERT INTO `book` (`id`, `book`, `number`, `place`, `state`) VALUES
(1, 'C语言基础', '2.1.1', '社会科学(1)', '1'),
(2, 'vim实用技巧', '2.1.2', '社会科学(1)', '0'),
(3, '21天学会C语言', '2.1.3', '自科(2)', '0'),
(4, 'C++从入门到精通', '2.1.4', '自科(1)', '0');

-- --------------------------------------------------------

--
-- 表的结构 `sheke1`
--

DROP TABLE IF EXISTS `sheke1`;
CREATE TABLE IF NOT EXISTS `sheke1` (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `type` set('1','0') CHARACTER SET utf8 NOT NULL,
  `state` set('0','1') CHARACTER SET utf8 NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=37 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- 转存表中的数据 `sheke1`
--

INSERT INTO `sheke1` (`id`, `type`, `state`) VALUES
(1, '0', '1'),
(2, '0', '1'),
(3, '0', '1'),
(4, '0', '0'),
(5, '0', '1'),
(6, '0', '1'),
(7, '0', '1'),
(8, '0', '1'),
(9, '0', '1'),
(10, '0', '1'),
(11, '0', '1'),
(12, '0', '1'),
(13, '0', '1'),
(14, '0', '1'),
(15, '0', '1'),
(16, '0', '0'),
(17, '0', '1'),
(18, '0', '1'),
(19, '0', '0'),
(20, '0', '1'),
(21, '0', '0'),
(22, '0', '0'),
(23, '0', '0'),
(24, '0', '0'),
(25, '0', '0'),
(26, '0', '0'),
(27, '0', '1'),
(28, '0', '0'),
(29, '0', '1'),
(30, '0', '0'),
(31, '0', '0'),
(32, '0', '1'),
(33, '1', '1'),
(34, '1', '1');

-- --------------------------------------------------------

--
-- 表的结构 `sheke2`
--

DROP TABLE IF EXISTS `sheke2`;
CREATE TABLE IF NOT EXISTS `sheke2` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `type` set('0','1') CHARACTER SET utf8 NOT NULL,
  `state` set('0','1') CHARACTER SET utf8 NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=34 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- 转存表中的数据 `sheke2`
--

INSERT INTO `sheke2` (`id`, `type`, `state`) VALUES
(1, '0', '0'),
(2, '0', '0'),
(3, '0', '0'),
(4, '0', '0'),
(5, '0', '0'),
(6, '0', '0'),
(7, '0', '0'),
(8, '0', '0'),
(9, '0', '0'),
(10, '0', '0'),
(11, '0', '0'),
(12, '0', '0'),
(13, '0', '0'),
(14, '0', '0'),
(15, '0', '0'),
(16, '0', '0'),
(17, '0', '1'),
(18, '0', '0'),
(19, '0', '0'),
(20, '0', '0'),
(21, '0', '0'),
(22, '0', '0'),
(23, '0', '0'),
(24, '0', '0'),
(25, '0', '0'),
(26, '0', '0'),
(27, '0', '0'),
(28, '0', '0'),
(29, '0', '0'),
(30, '0', '0'),
(31, '1', '1'),
(32, '1', '0'),
(33, '1', '1');

-- --------------------------------------------------------

--
-- 表的结构 `user`
--

DROP TABLE IF EXISTS `user`;
CREATE TABLE IF NOT EXISTS `user` (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `name` text NOT NULL,
  `password` text NOT NULL,
  `seat` text,
  `seat_time` text,
  `seat_room` text,
  `seat_num` text,
  `book1` text,
  `book_time1` text,
  `book2` text,
  `book_time2` text,
  `book3` text,
  `book_time3` text,
  `book4` text,
  `book_time4` text,
  `book5` text,
  `book_time5` text,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;

--
-- 转存表中的数据 `user`
--

INSERT INTO `user` (`id`, `name`, `password`, `seat`, `seat_time`, `seat_room`, `seat_num`, `book1`, `book_time1`, `book2`, `book_time2`, `book3`, `book_time3`, `book4`, `book_time4`, `book5`, `book_time5`) VALUES
(1, 'ma', '123456', '教室:社会科学(2)  座位号:17', '2020-03-27 10:48', 'sheke2', '17', 'C语言基础', '2020-03-25 20:47', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(2, 'ning', '123', '教室:社会科学(1)  座位号:29', '2020-03-26 11:23', 'sheke1', '29', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
