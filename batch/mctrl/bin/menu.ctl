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

@TITLE|   QDP System Control V1.0    |1

�廷�����  |1|0|0|0
����  ��    |2|0|0|0
����������|3|0|0|0
��Ѳ  ��    |4|0|0|0
���̺���  |5|0|0|0
��Ӧ������  |6|0|0|0

�ż�������Ϣ  |11|1|0|0
�Ƽ������ʱ��  |12|1|0|0
�Ǽ�������ļ�  |13|1|0|0
�ȼ��˿����  |14|1|0|0
�ɼ��������  |15|1|0|0
�ʼ��ϵͳ״̬  |16|1|0|0

���������׽���|21|2|0|0
�Ƽ�齻�׽���|22|2|0|0
�������������|23|2|0|0
�ȼ���������|24|2|0|0

�ż�齻�׽���|31|3|0|0
�ƴ����¼���|32|3|0|0
�Ǽ��ϵͳ״̬|33|3|0|0
�ȼ���������|34|3|0|0

�Ž������    |41|4|0|0
�����������  |42|4|0|0
�ǵ�¼�������|43|4|0|0
�ȱ�����Ŀ���|44|4|0|0
�ɳɽ���Ŀ���|45|4|0|0
�ʼ��ϵͳ״̬|46|4|0|0
�˼���ʽ�״̬|47|4|0|0
�ȼ�齻�����˿�|48|4|0|0

�ż��������|50|5|0|0
��ֹͣ���н���|51|5|0|0
�Ǳ���������ˮ|52|5|0|0
������������ˮ|53|5|0|0
��Ӧ���ϳ��ļ�|56|5|0|0
����ʱͳ��|58|5|0|0
��ֹͣ�������|54|5|0|0
������������|55|5|0|0

��ֹͣ��һQDP|60|6|0|0
������һ���ݿ�|61|6|0|0
��������һQDP|62|6|0|0
��������һQDP|63|6|0|0
����������QDP|64|6|0|0

#�˵���������
#��ʽ:@CMD|�˵����ܺ�|�����½��־(0:������ 1:��ʧ��ȷ�� 2:����˫�û�)|ʱ��α��|�ⲿ�����Shell
#����ǰ
@CMD|11|0|0|cd ../../bin; ./mcall dispdisk
@CMD|12|0|0|cd ../../bin; ./mcall showtime
@CMD|13|0|0|cd ../script; ./chkconfig.sh
@CMD|14|0|0|cd ../../bin; ./callfuns CheckAllPort
@CMD|15|0|0|cd ../../bin; ./showall
@CMD|16|0|0|cd ../script; ./checkdb.sh chksystemstatus

#����
@CMD|21|2|0|cd ../../bin; ./startall
@CMD|22|0|0|cd ../../bin; ./showall
@CMD|23|2|0|ssh -n qmarket@172.16.102.66  "export PATH=$PATH:~/bin;cd bin; ./startall"
@CMD|24|0|0|ssh -n qmarket@172.16.102.66  "export PATH=$PATH:~/bin;cd bin; ./showall"

#������ 
@CMD|31|0|0|cd ../../bin; ./showall;
@CMD|32|0|0|cd ../../bin; ./mcall chktxt
@CMD|33|0|0|cd ../script; ./checkdb.sh chksystemstatus
@CMD|34|0|0|cd ../../binmd; ./showall

#Ѳ��
@CMD|41|0|0|cd ../../bin; ./showall;ssh -n qmarket@172.16.102.66  "export PATH=$PATH:~/bin;cd bin; ./showall"
@CMD|42|0|0|cd ../../bin; ./callfuns checklink;
@CMD|43|0|0|cd ../script; ./checkdb.sh chksession
@CMD|44|0|0|cd ../script; ./checkdb.sh chkorder
@CMD|45|0|0|cd ../script; ./checkdb.sh chktrade
@CMD|46|0|0|cd ../script; ./checkdb.sh chksystemstatus
@CMD|47|0|0|cd ../script; ./checkdb.sh chkaccount
@CMD|48|0|0|cd ../../bin; ./callfuns CheckUpPort

#�̺���
@CMD|50|0|0|cd ../../bin; ./showall
@CMD|51|2|0|cd ../../bin; ./stopall
@CMD|52|2|0|cd ../../bin; ./mcall backlog
@CMD|53|2|0|cd ../../bin; ./mcall clearlog
@CMD|56|2|0|cd ../../bin; ./mcall dumptinit
@CMD|58|1|0|cd ../../bin; ./mcall looptime
@CMD|54|0|0|ssh -n qmarket@172.16.102.66  "export PATH=$PATH:~/bin;cd bin; ./stopall"
@CMD|55|0|0|ssh -n qmarket@172.16.102.66  "export PATH=$PATH:~/bin;./clearlog.sh"

@CMD|60|2|0|cd ../../bin; ./stopone
@CMD|61|2|0|cd ../script; ./checkdb.sh clear
@CMD|62|2|0|cd ../../bin; ./startone
@CMD|63|2|0|cd ../../bin; ./restartone
@CMD|64|2|0|cd ../../bin; ./restartall


#@cmd|1:in 0:out|time id|begin time|end time 
@TIME_CTRL|1|1|07:00:00|09:10:00
@TIME_CTRL|0|2|15:15:00|19:40:00
@TIME_CTRL|0|3|09:05:00|15:18:00
