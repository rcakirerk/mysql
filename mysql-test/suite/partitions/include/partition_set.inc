--disable_query_log
# DATA DIRECTORY
eval SET @data_dir = 'DATA DIRECTORY =
''/tmp''';
let $data_directory = `select @data_dir`;

#INDEX DIRECTORY
eval SET @indx_dir = 'INDEX DIRECTORY =
''/tmp''';
let $index_directory = `select @indx_dir`;
--enable_query_log

eval create table t1 (a set('A','B','C','D','E','F','G','H','I','J','K','L') not null, primary key(a)) engine=$engine 
partition by key (a) (
partition pa1 $data_directory $index_directory max_rows=20 min_rows=2,
partition pa2 $data_directory $index_directory max_rows=30 min_rows=3,
partition pa3 $data_directory $index_directory max_rows=30 min_rows=4,
partition pa4 $data_directory $index_directory max_rows=40 min_rows=2);
show create table t1;
insert into t1 values ('A,B'),('C,D'),('E,L'),('G,H,K');
select * from t1 order by a;
select * from t1 where a='A,B';
update t1 set a='A,B,C' where a='E,L';
select * from t1 order by a;
delete from t1 where a='A,B';
select * from t1 order by a;
drop table t1;

eval create table t2 (a set (
'1','2','3','4','5','6','7','8','9','0',
'A','B','C','D','E','F','G','H','I','J','K','L',
'M','N','O','P','Q','R','S','T','U','V','W','X',
'Y','Z'
) not null, primary key(a)) engine=$engine 
partition by key (a) partitions 27;
show create table t2;
insert into t2 values ('A'),('B'),('C'),('D'),('E'),('F'),('G'),('H'),('I'),('K'),('L'),('M'),('N'),('O'),('P'),('Q'),('S'),('T'),('U'),('V'),('X'),('Y'),('Z');
insert into t2 values ('A,B'),('B,C'),('C,D'),('D,E'),('E,F'),('F,G'),('G,H'),('H,I'),('I,J'),('K,L'),('L,M'),('M,N'),('N,O'),('O,P'),('P,Q'),('Q,R'),('S,T'),('T,U'),('U,V'),('V,W'),('X,Y'),('Y,Z'),('Z,A');
insert into t2 values ('A,B,C'),('B,C,D'),('C,D,E'),('D,E,F'),('E,F,G'),('F,G,H'),('G,H,I'),('H,I,J'),('I,J,K'),('K,L,M'),('L,M,N'),('M,N,O'),('N,O,P'),('O,P,Q'),('P,Q,R'),('Q,R,S'),('S,T,U'),('T,U,V'),('U,V,W'),('V,W,X'),('X,Y,Z'),('Y,Z,A'),('Z,A,B');
insert into t2 values ('1'),('2'),('3'),('4'),('5'),('6'),('7'),('8'),('9'),('0');
insert into t2 values ('1,2'),('2,3'),('3,4'),('4,5'),('5,6'),('6,7'),('7,8'),('8,9'),('9,0'),('0,1');
insert into t2 values ('1,2,3'),('2,3,4'),('3,4,5'),('4,5,6'),('5,6,7'),('6,7,8'),('7,8,9'),('8,9,0'),('9,0,1'),('0,1,2');
select count(*) from t2;
select * from t2 order by a;
drop table t2;

eval create table t3 (a set (
'1','2','3','4','5','6','7','8','9','0'
) not null, primary key(a)) engine=$engine 
partition by range (cast(a as unsigned)) subpartition by key (a) subpartitions 3 (
partition pa9 values less than (10),
partition pa18 values less than (19),
partition pa27 values less than (28),
partition pa36 values less than (37),
partition pa64 values less than (65),
partition pa128 values less than (129),
partition pa256 values less than (257),
partition pa512 values less than (513),
partition pa768 values less than (769),
partition pa1024 values less than (1025)
);
show create table t3;
#insert into t3 values ('1'),('2'),('3'),('4'),('5'),('6'),('7'),('8'),('9'),('0');
#insert into t3 values ('1,2'),('2,3'),('3,4'),('4,5'),('5,6'),('6,7'),('7,8'),('8,9'),('9,0'),('0,1');
#insert into t3 values ('1,2,3'),('2,3,4'),('3,4,5'),('4,5,6'),('5,6,7'),('6,7,8'),('7,8,9'),('8,9,0'),('9,0,1'),('0,1,2');
select count(*) from t3;
select * from t3 order by a;
drop table t3;

eval create table t4 (a set (
'1','2','3') not null, primary key(a)) engine=$engine 
partition by list (cast(a as unsigned)) subpartition by key (a) subpartitions 3 (
partition pa9 values in (1,2,3,4,5,6,7,8,9),
partition pa18 values in (10,11,12,13,14,15,16,17,18),
partition pa27 values in (19,20,21,22,23,24,25,26,27)
);
show create table t4;
#insert into t4 values ('1'),('2'),('3');
#insert into t4 values ('1,2'),('2,3'),('3,1');
#insert into t4 values ('1,2,3');
select count(*) from t4;
select * from t4 order by a;
drop table t4;