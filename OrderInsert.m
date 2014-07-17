function ref = OrderInsert(inst, direction, flag, volume, price)
%ORDERINSERT �µ�����
%ref = OrderInsert('IF1407', '0', '0', 1, 2300);
% inst: ��Լ��
%direction: ������������: ��='0', ��='1'
%flag; ��ƽ��־������: ��='0'��ƽ='3'
%volume: ����
%price: �۸�
%ref: ���ر�������
if(~ischar(inst) || ~ischar(direction) || ~ischar(flag) || ~isnumeric(volume) || ~isnumeric(price))
    error('input type error');
end
ref = TraderMain(6, inst, direction, flag, volume, price);

end

