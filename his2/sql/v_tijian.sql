create or replace view his.v_tijian as
select 所属部,部门名称,卡号,姓名,性别,to_char(riqi,'yyyy-mm-dd') rq,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,
a15,a16,a17,a18,/*a19*/ ls ,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,a31,a32,extract(year from sysdate)-extract(year from 出生日期) a33,
extract(year from sysdate)-extract(year from 工作日期) a34,工作日期,riqi,tsgf,afp,cea,rec_comm from 职工基本情况表,tijian,
                                                                        /**********************/
厂部门表 where 职工基本情况表.卡号=tijian.kahao and 职工基本情况表.部门编码=厂部门表.部门编码

