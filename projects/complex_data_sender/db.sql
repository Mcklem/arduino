CREATE TABLE `input_data` (
  `id` int(11) NOT NULL auto_increment,
  `type` varchar(15) NOT NULL,
  `data` longtext NOT NULL,
  `date` datetime NOT NULL,
  PRIMARY KEY  (`id`)
)