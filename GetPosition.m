function position = GetPosition(varargin)
%GETPOSITION ��ȡ�ֲ���Ϣ
%��ȡȫ���ֲ�: position = GETPOSITION;
%��ȡָ����Լ�ֲ�: position = GETPOSITION(instrument);
if(nargin == 0)
    position = TraderMain(9);
elseif (nargin == 1)
    if(~ischar(varargin{1}))
        error('�������ʹ���');
    end
    position = TraderMain(9, varargin{1});
else
    error('������������');
end


end

