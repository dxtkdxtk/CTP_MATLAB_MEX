function order = GetOrderFromAllSession(frontid, session, ref)
%GETORDERFROMALLSESSION ��ȡָ�����ӱ���
% frontid: ����ǰ��
% session: ���ӱ���
% ref: ��������
if(~isnumeric(frontid) || ~isnumeric(frontid) || ~isnumeric(frontid))
    error('�������ͱ���Ϊ���֣�');
end
order = TraderMain(13, frontid, session, num2str(ref));

end

