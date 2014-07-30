function order = GetOrder(varargin)
%GETORDER ��ȡ����
% ��ȡ���б�����order = GETORDER;
% ��ȡ�������ӱ�����order = GETORDER(orderref); orderrefΪ������������
% ��ȡָ�����ӱ�����order = GETORDER(frontid, session, orderref); ȫ������Ϊ����
% ��������order����order����0
if(nargin == 0)
    order = TraderMain(7);
elseif (nargin == 1)
    if(~isnumeric(varargin{1}))
        error('�������Ϊ����!');
    end
    order = TraderMain(7, num2str(varargin{1}));
elseif (nargin == 3)
    if(~isnumeric(varargin{1}) || ~isnumeric(varargin{2}) || ~isnumeric(varargin{3}))
        error('�������ȫ��Ϊ����!');
    end
    order = TraderMain(7, varargin{1}, varargin{2}, num2str(varargin{3}));
else
    error('������������!');
end

end

