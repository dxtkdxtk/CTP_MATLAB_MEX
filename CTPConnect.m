function CTPConnect(varargin)
%CTP连接函数
server = 'sampleServer';
if(nargin == 1)
    server = varargin{1};
elseif(nargin > 1)
    error('参数不能多于1');
end
TraderMain(1, server);


end

