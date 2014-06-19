function CTPConnect(varargin)
%CTP连接函数，参数为INI文件中服务器字段
%包含连接信息，可自行设置
server = 'sampleServer';
if(nargin == 1)
    server = varargin{1};
    if(~ischar(server))
        error('服务器类型错误');
    end
elseif(nargin > 1)
    error('参数不能多于1');
end
TraderMain(1, server);


end

