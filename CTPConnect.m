function CTPConnect(varargin)
%CTP���Ӻ���
server = 'sampleServer';
if(nargin == 1)
    server = varargin{1};
elseif(nargin > 1)
    error('�������ܶ���1');
end
TraderMain(1, server);


end

