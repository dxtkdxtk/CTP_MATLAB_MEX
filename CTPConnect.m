function CTPConnect(varargin)
%CTP���Ӻ���������ΪINI�ļ��з������ֶ�
%����������Ϣ������������
server = 'sampleServer';
if(nargin == 1)
    server = varargin{1};
    if(~ischar(server))
        error('���������ʹ���');
    end
elseif(nargin > 1)
    error('�������ܶ���1');
end
TraderMain(1, server);


end

