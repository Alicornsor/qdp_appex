#'#' ��ʾע�� �˵�ϵͳ���Դ���
#���ܣ���ʾ�ı� ��ʽ��@TEXT|��ʼ��|��ʼ��|�ı�����|��ʾ���� 0 ���� 1 ����
#���ܣ����� ��ʽ��@BOX|��ʼ��|��ʼ��|ĩβ��|ĩβ��
#���ܣ����� ��ʽ��@LINE|��|��|����|������־ - ��ʾ���� | ��ʾ����
#���ܣ�����˵���Ԫ ��ʽ:�˵���|�˵����ʶ|���˵���ʶ|��(��Ļλ��)|��(��Ļλ��) 

##��������
##�ŢƢǢȢɢʢˢ̢͢΢ϢТѢҢӢԢբ֢ע�

#Ŀ¼����
#��־Ŀ¼����
@CFG|../log

#����
@BBOX|0|1|43|125
#�˵���
@MBOX|
#һ�㷽��
#@BOX|2|3|5|125

@TITLE|   ��Ͷ���� QDAM ϵͳ��ά���� V1.0    |1

�廷�����  |1|0|0|0
���������  |2|0|0|0
������Ѳ��  |3|0|0|0
���̺���  |4|0|0|0
��Ӧ������  |5|0|0|0

�ż�������Ϣ|11|1|0|0
�Ƽ������ʱ��|12|1|0|0
�Ǽ��˿����|13|1|0|0
�ȼ��������|14|1|0|0
�ɼ��ϵͳ״̬|15|1|0|0
�ʼ���ϳ�����|16|1|0|0
�˼����ǰ����|17|1|0|0
�̼����������|18|1|0|0

������֮ǰ׼��|55|2|0|0
������ϵͳ����|21|2|0|0
�Ǽ��������|22|2|0|0
�ȴ����¼���|23|2|0|0
��������Ŀ���|42|2|0|0
�ʼ���ϲ�����|48|2|0|0
������ctp����|24|2|0|0
������es����|25|2|0|0
�Ͳ鿴CTP�����Լ|26|2|0|0
�β鿴ES�����Լ|27|2|0|0
�Ͽ���CTP�����Լ|28|2|0|0
�п���ES�����Լ|29|2|0|0
                  
�Ž��̽������|41|3|0|0
��������Ŀ���|42|3|0|0
�ǵ�¼�������|43|3|0|0
�ȱ�����Ŀ���|44|3|0|0
�ɳɽ���Ŀ���|45|3|0|0
�ʼ��ϵͳ״̬|46|3|0|0
�˼���ʽ�״̬|47|3|0|0
�̼���ϲ�����|48|3|0|0

�ż��������|41|4|0|0
��ֹͣϵͳ����|51|4|0|0
�Ǳ���ϵͳ��ˮ|52|4|0|0
������ϵͳ��ˮ|53|4|0|0
�ɱ�ȫ�����ݿ�|54|4|0|0
�����³����ݿ�|55|4|0|0

��ֹͣϵͳ����|51|5|0|0
�Ʊ���ϵͳ��ˮ|52|5|0|0
������ϵͳ��ˮ|53|5|0|0
�ȱ�ȫ�����ݿ�|54|5|0|0
�����³����ݿ�|55|5|0|0
������ϵͳ����|61|5|0|0
������ϵͳ����|21|5|0|0
���û��޸�����|1002|5|0|0


#�˵���������
#��ʽ:@CMD|�˵����ܺ�|�����½��־(0:������ 1:��ʧ��ȷ�� 2:����˫�û�)|ʱ��α��|�ⲿ�����Shell
#�������
@CMD|11|0|0|cd ../../bin; ./mcall dispdisk;
@CMD|12|0|0|cd ../../bin; ./mcall showtime;
@CMD|13|0|0|cd ../../bin; ./portfuns port
@CMD|14|0|0|cd ../../bin; ./mcall show
@CMD|15|0|0|cd ../../bin; ./dball chksystemstatus
@CMD|16|0|0|cd ../../bin; ./calluser mc_batch qdamcheckphase1 ../list/list.user
@CMD|17|0|0|cd ../../bin; ./calluser mc_batch qdamcheckphase2 ../list/list.user
@CMD|18|0|0|cd ../../bin; ./calluser mc_batch qdamcheckphase3 ../list/list.user

#��������
@CMD|21|1|0|cd ../../bin; ./calluser mc_batch restart
@CMD|22|0|0|cd ../../bin; ./calluser mc_batch show
@CMD|23|0|0|cd ../../bin; ./mcall show
@CMD|24|0|0|cd ../../bin; ./calluser dbaction.sh insctp ../list/list.db
@CMD|25|0|0|cd ../../bin; ./calluser dbaction.sh inses ../list/list.db
@CMD|26|0|0|cd ../../bin; ./showinsctp.sh
@CMD|27|0|0|cd ../../bin; ./showinses.sh
@CMD|28|0|0|cd ../../bin; ./calluser mc_batch copyins
@CMD|29|0|0|cd ../../bin; ./calluser mc_batch copyes

#����Ѳ��
@CMD|41|0|0|cd ../../bin; ./mcall show
@CMD|42|0|0|cd ../../bin; ./portfuns link
@CMD|43|0|0|cd ../../bin; ./dball chksession
@CMD|44|0|0|cd ../../bin; ./dball chkorder
@CMD|45|0|0|cd ../../bin; ./dball chktrade
@CMD|46|0|0|cd ../../bin; ./dball chksystemstatus
@CMD|47|0|0|cd ../../bin; ./dball chkaccount
@CMD|48|0|0|cd ../../bin; ./portfuns up

#�̺���
@CMD|51|2|0|cd ../../bin; ./calluser mc_batch stop
@CMD|52|1|0|cd ../../bin; ./calluser mc_batch backlog
@CMD|53|2|0|cd ../../bin; ./calluser mc_batch clearlog
@CMD|54|1|0|cd ../../bin; ./calluser mc_batch backupdb ../list/list.db.user
@CMD|55|1|0|cd ../../bin; ./callone dbaction.sh clearone ../list/list.db

#Ӧ������
@CMD|61|2|0|cd ../../bin; ./calluser mc_batch restart
@CMD|1002|0|0|(�ڲ�)�޸�����

#@cmd|1:in 0:out|time id|begin time|end time 
@TIME_CTRL|1|1|07:00:00|09:10:00
@TIME_CTRL|0|2|15:15:00|19:40:00
@TIME_CTRL|0|3|09:05:00|15:18:00
