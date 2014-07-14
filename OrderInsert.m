function ref = OrderInsert(inst, direction, flag, volume, price)
%ORDERINSERT 下单操作
%ref = OrderInsert('IF1407', '0', '0', 1, 2300);
% inst: 合约名
%direction: 买卖方向。其中: 买='0', 卖='1'
%flag; 开平标志。其中: 开='0'，平='3'
%volume: 数量
%price: 价格
%ref: 返回报单引用
if(~ischar(inst) || ~ischar(direction) || ~ischar(flag) || ~isnumeric(volume) || ~isnumeric(price))
    error('input type error');
end
ref = TraderMain(6, inst, direction, flag, volume, price);


end

