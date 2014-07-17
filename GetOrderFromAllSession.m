function order = GetOrderFromAllSession(frontid, session, ref)
%GETORDERFROMALLSESSION 获取指定连接报单
% frontid: 连接前置
% session: 连接编码
% ref: 报单引用
if(~isnumeric(frontid) || ~isnumeric(frontid) || ~isnumeric(frontid))
    error('参数类型必须为数字！');
end
order = TraderMain(13, frontid, session, num2str(ref));

end

