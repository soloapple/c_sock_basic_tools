use gap;
DROP TABLE IF EXISTS `tab_alarm`;

CREATE TABLE `tab_alarm` (
  `hash_msg` int(11) DEFAULT NULL COMMENT 'ʶ����',
  `msg` varchar(512) DEFAULT NULL COMMENT '��Ϣ',
  `mode` varchar(30) DEFAULT NULL COMMENT 'ģ��',
  `severity` varchar(8) DEFAULT NULL COMMENT '����',
  `type` int(11) DEFAULT NULL COMMENT '����',
  `optime` datetime DEFAULT NULL COMMENT 'ʱ��',
  `reptime` int(11) DEFAULT NULL COMMENT '�ظ�����',
  `gap_ip` varchar(16) DEFAULT NULL COMMENT '����IP'
) ENGINE=MyISAM DEFAULT CHARSET=gbk COMMENT='�澯��־';
