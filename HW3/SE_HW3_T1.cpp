#include<set>
//读卡器状态
enum IDCardReaderStatus{
	REQ, //读卡器读到了卡，正在请求回应
	WAIT //读卡器等待下一次读到卡
};
//红外线感应器状态
enum InfraredSensorStatus{
	REQ, //红外线感应器感应到有人通过，正在请求回应
	WAIT //红外线感应器等待下一个人通过
};
//闸门状态
enum GateStatus{
	OUT_OPENED,		//闸门向外打开
	OUT_OPENING,	//闸门正在向外打开
	IN_OPENED,		//闸门向内打开
	IN_OPENING,		//闸门正在向内打开
	CLOSED,			//闸门关闭
	OUT_CLOSING,	//闸门正在向外关闭
	IN_CLOSING,		//闸门正在向内关闭
};
//方向
enum Direction{
	OUTSIDE,		//向外
	INSIDE			//向内
};
//数据库，存储一卡通的准入信息
class IDCardDatabase{
    private:
		Database IDCards;//闸机系统所连接到的数据库，具体实现方式省略
    public:
		int CreateDatebase();//创建数据库并初始化一个空表格
		int InsertRecord(int ID,bool Admission);//增加一条新的记录
		int DeleteRecord(int ID);//以ID为索引，删除一条记录
		bool SearchRecord(int ID);//以ID为索引，搜索记录，返回其是否存在
		bool CheckAdmission(int ID);//以ID为索引，确认该ID是否有准入权限（包括不在数据库中的情况）
		int AlterRecordAdmission(int ID,bool NewAdmission);//以ID为索引，更新记录的准入权限情况
		int DeleteDatebase();//删除数据库
};
//一卡通本身
class IDCard{
    public:
		int ID;//一卡通的ID，作为唯一标识号
		string name;//一卡通的卡主名字
};
//读卡器
class IDCardReader{
    public:
		int IDCardReaderID;//读卡器的唯一标识ID
		IDCardReaderStatus Status;//标识读卡器的状态
		int ReadCard();//读卡，发起请求，如果有一卡通，返回读到的一卡通的ID，不然返回空
};
//红外线感应器
class InfraredSensor{
    public:
	int InfraredSensorID;//红外线感应器的唯一标识ID
	InfraredSensorStatus Status;//标识红外线传感器的状态，一次经过的操作是否正在激活中
};
//闸门本身,对于闸机系统来说可能有若干个
class Gate{
    public:
		int GateID;//闸门的唯一标识ID
		GateStatus Status;//闸门的状态
		Timer timer;//闸门内置的计时器，除非被归零，其始终保持自增，具体实现方式省略
		void Open(Direction Dir);//向着Dir指示的方向开门
		void Close(Direction Dir);//向着Dir指示的方向关门
};
//中控模块，采用时间触发
//轮询读卡器、红外线传感器读取信息、转换相应状态，
//如果考虑读卡器的请求，同时通过数据库进行验证
//再根据闸门的状态和Timer值，发起相应控制操作
//允许直接对闸门进行操作，比如某些时候校方会保持闸门始终开启或者关闭
class GateController{
    private:
		Gate Gates[];//中控模块管理所有闸门
		IDCardReader IDCardReaders[];//中控模块管理所有读卡器
		InfraredSensor InfraredSensors[];//中控模块管理所有红外线感应器
		IDCardDatabase IDCardDB;
		void AutoManager();//在没有用户介入的情况下，中控模块将自动轮询调度
	public:
		int UserManager(...);//在有特殊需要的时候，由用户手动设定，具体略，返回结果
};

int main()
{
	printf("hello world!");
}
