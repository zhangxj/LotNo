use barcode;
if EXISTS (select * from sysobjects where name = 'FANXIU_SN')
	DROP TABLE FANXIU_SN;

create table FANXIU_SN
(
	LOT_NO varchar(50),
	BLOCK_NO varchar(50),
	SN varchar(50),
	LOCATION varchar(50),
	ADDON datetime default getdate()
)

