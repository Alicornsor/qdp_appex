��Ҫ��
	�˽ű����������𡢶������ͳһ��ͣ�����ݵ�һ�壬����ģ�黯�̶ȼ��ߣ�����
	7.2�汾��mctrl��Ҫ�ؽ���Ӧ���û�����
���ߣ�
	���һ�
Ŀ¼˵����
	bin: shell�ű������ڿ���ϵͳ��ͣ�Ͳ���ϵͳ
	mctrl:��ά��������
	sql:���ݿ�ִ�нű�
	run:Ӧ�ó����ÿ����������ú������ű�
	list:ϵͳ�û���ģ�顢���ݿ�������б��ǽű������仯�ĵط���Ҳ�����õ���Ҫ�ļ�

ʹ�÷�����
	bin����Ľű�������Ҫ�Ľű��������ű���ʹ�÷���
	(1)showall:
		showall �鿴list.run����ĳ�����������
		showall 1 �鿴list.run�����һ��ģ����������
		showall qtrade �鿴list.run����qtradeģ����������
		showall a �鿴list.run��������ģ����������
		
	(2)startall/stopall/restartall��showallһ��
		��startallһ����������߼���run_batch��
		
	(3)mcall(���ƻ��Ŀ��ƻ�)
		mcall show �鿴list.user�������Ŀ��������Ƶĳ�����������
		mcall show 1 �鿴list.user�����һ��Ŀ��������Ƶĳ�����������
		mcall show qdp01 �鿴list.user�������Ϊqdp01Ŀ��������Ƶĳ�����������
		mcall show a �鿴list.user��������Ŀ��������Ƶĳ�����������
		mcall show qdp01 qtrade �鿴list.user�������Ϊqdp01Ŀ��������Ƶ�list.run����qtradeģ����������
		mcall show qdp01 1 �鿴list.user�������Ϊqdp01Ŀ��������Ƶ�list.run����qtradeģ����������
		mcall show qdp01 a �鿴list.user�������Ϊqdp01Ŀ��������Ƶ�list.run��������ģ����������
		������߼��� mc_batch��
		
	(4)dball��mcall�����л���һ��
		����Ļ���� dbaction.sh��
		
	���ϳ������ѡ�������ĸ�ģ�飬ʹ��calluser���ü�����ѡ��Ľ��棬�ֶ�ѡ�������ĸ�����
	calluserĬ��ʹ��list.user��Ϊѡ�����ݣ�Ҳ���Դ��ϲ������ṩlist����ѡ��
	./calluser dbaction.sh insctp ../list/list.db :ʹ��list.db��Ϊѡ��Դ������dbaction.sh�ű�
	./calluser mc_batch show :ʹ��list.user��ΪĬ��ѡ��Դ������mc_batch�ű�
	
	(5)portfuns:�˿�ʹ��������ű�
		portfuns link �鿴list.link����Ķ˿ںŵ�ʹ�����
		portfuns up �鿴list.up����Ķ˿ںŵ�ʹ�����
		portfuns port �鿴list.port����Ķ˿ںŵ�ʹ�����
		
	
	