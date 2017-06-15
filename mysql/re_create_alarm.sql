use gap;
DROP TABLE IF EXISTS `tab_alarm`;

CREATE TABLE `tab_alarm` (
  `hash_msg` int(11) DEFAULT NULL COMMENT '识别码',
  `msg` varchar(512) DEFAULT NULL COMMENT '消息',
  `mode` varchar(30) DEFAULT NULL COMMENT '模块',
  `severity` varchar(8) DEFAULT NULL COMMENT '级别',
  `type` int(11) DEFAULT NULL COMMENT '类型',
  `optime` datetime DEFAULT NULL COMMENT '时间',
  `reptime` int(11) DEFAULT NULL COMMENT '重复次数',
  `gap_ip` varchar(16) DEFAULT NULL COMMENT '本机IP'
) ENGINE=MyISAM DEFAULT CHARSET=gbk COMMENT='告警日志';
