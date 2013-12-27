if NOT EXISTS (select * From master.dbo.sysdatabases where name='barcode')
	CREATE DATABASE barcode;

use barcode;

if EXISTS (select * from sysobjects where name = 'LOT_NO')
	DROP TABLE LOT_NO;

create table LOT_NO 
(
	LOT_NO varchar(50) primary key,
	addon datetime default getdate()
);
if EXISTS (select * from sysobjects where name = 'BLOCK_NO')
	DROP TABLE BLOCK_NO;

create table BLOCK_NO
(  
	BLOCK_NO varchar(50) primary key,
	LOT_NO varchar(50),
	addon datetime default getdate()
);

if EXISTS (select * from sysobjects where name = 'SN')
	DROP TABLE SN;

create table SN
(
	SN varchar(50) primary key,
	BLOCK_NO varchar(50),
	addon datetime default getdate()
)
