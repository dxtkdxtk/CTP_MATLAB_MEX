function order = GetOrder(varagin)
%GETORDER ��ȡ����
% ��ȡ���б�����order = GETORDER;
% ��ȡ�������ӱ�����order = GETORDER(orderref); orderrefΪ������������
% ��ȡָ�����ӱ�����order = GETORDER(frontid, session, orderref); ȫ������Ϊ����
if(nargin == 0)
    order = TraderMain(7);
elseif (nargin == 1)
    if(~isnumeric(varagin{1}))
        error('�������Ϊ����!');
    end
    order = TraderMain(12, num2str(varagin{1}));
elseif (nargin == 3)
    if(~isnumeric(varagin{1}) || ~isnumeric(varagin{2}) || ~isnumeric(varagin{3}))
        error('�������ȫ��Ϊ����!');
    end
    order = TraderMain(13, varagin{1}, varagin{2}, num2str(varagin{3}));
else
    error('������������!');
end

end

