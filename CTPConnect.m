function [frontid, sessionid] = CTPConnect(varargin)
%CTP���Ӻ���������ΪINI�ļ��з������ֶ�
%����������Ϣ������������
%����frontid, sessionid, ��ʶ�����ӡ�
server = 'sampleServer';
if(nargin == 1)
    server = varargin{1};
    if(~ischar(server))
        error('���������ʹ���');
    end
elseif(nargin > 1)
    error('�������ܶ���1');
end
[frontid, sessionid] = TraderMain(1, server);


end

