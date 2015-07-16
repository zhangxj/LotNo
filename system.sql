
/*第一步: 单独执行  (选中内容 点击执行)*/
if NOT EXISTS (select * From master.dbo.sysdatabases where name='smf_barcode')
	CREATE DATABASE smf_barcode;
/* end */

use smf_barcode;

if EXISTS (select * from sysobjects where name = 'LOT_NO')
	DROP TABLE LOT_NO;

create table LOT_NO 
(
	LOT_NO varchar(50) primary key,
	ADDON datetime default getdate()
);
if EXISTS (select * from sysobjects where name = 'BLOCK_NO')
	DROP TABLE BLOCK_NO;

create table BLOCK_NO
(  
	BLOCK_NO varchar(50) primary key,
	LOT_NO varchar(50),
	ADDON datetime default getdate()
);

if EXISTS (select * from sysobjects where name = 'SN')
	DROP TABLE SN;

create table SN
(
	SN varchar(50),
	BLOCK_NO varchar(50),
	LOCATION varchar(50),
	FLAG int,  /* 0:正常  1:返修品*/
	ADDON datetime default getdate()
)

ALTER TABLE SN ADD PRODUCT VARCHAR(20);
use smf_barcode;
ALTER TABLE SN ADD OPT_ID VARCHAR(50);


use smf_barcode;
if EXISTS (select * from sysobjects where name = 'SETTINGS')
	DROP TABLE SETTINGS;

create table SETTINGS
(
	BLOCK_NO_LIMIT int
)

insert SETTINGS (BLOCK_NO_LIMIT) values (100);

use smf_barcode;
if EXISTS (select * from sysobjects where name = 'PASSPORT')
	DROP TABLE PASSPORT;

create table PASSPORT 
(
	ID int primary key identity(1,1),
	OPT_ID varchar(50) unique,
	NICKNAME varchar(50),
	ADDON datetime default getdate()
);


/*
select LOT_NO.LOT_NO, BLOCK_NO.BLOCK_NO, SN.SN from LOT_NO 
left join BLOCK_NO on LOT_NO.LOT_NO = BLOCK_NO.LOT_NO 
left join SN on BLOCK_NO.BLOCK_NO = SN.BLOCK_NO
where LOT_NO.LOT_NO = 'q'


select name from sysobjects where parent_obj in (select id from sysobjects where name='BLOCK_NO') and xtype='pk'
alter table	BLOCK_NO drop constraint PK__BLOCK_NO__489AC854;

*/
