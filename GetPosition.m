function position = GetPosition(varargin)
%GETPOSITION ��ȡ�ֲ���Ϣ
if(nargin == 0)
    position = TraderMain(9);
elseif (nargin == 1)
    if(~ischar(varargin{1}))
        error('�������ʹ���');
    end
    position = TraderMain(14, varargin{1});
else
    error('������������');
end


end

