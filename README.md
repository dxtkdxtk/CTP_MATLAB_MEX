ctp for matlab mex
============
Usage
-------

####此版本在32位matlab R2014a编译通过，mex使用vs2013 C++。

* make: 编译项目
* server.ini中设置服务器，期商，账号，数据流路径。
* CTPConnect: 连接CTP
* CTPDisconnect: 断开CTP
* Subscribe: 订阅合约
* GetAllOrders: 获取所有报单
* GetOrder: 获取指定报单
* GetInstrument: 获取当日交易合约
* GetMarketData: 获取合约行情数据
* TraderMain: mex主入口
