
//任务状态
enum TaskStatus{
    SUBMIT,//已经提交任务，正在过初始检测
    PENDING,//任务已经在验证
    PASS,//任务验证完成，非灰色应用
    GREY//任务验证完成，是灰色应用
};
//应用
class Application{
    public:
        string Name;//应用名字
        string Path;//应用路径
        CreateApplication(string Name,string Path);//构造函数
        int DeleteApplication();//删应用对象
};
//通知
class Notice{
    public:
        int NoticeID;//通知ID
        int UserID;//用户ID
        string Information;//通知信息
        CreateNotice(int NoticeID,int UserID,string Information);//构造函数
        int DeleteNotice();//删通知对象
}
//报告
class Report{
    public:
        int TaskID;//任务ID
        string Information;//报告信息
        CreateReport(int TaskID,string Information);//构造函数
        int DeleteReport();//删报告对象
}
//任务
class Task{
    public:
        int TaskID;//任务ID
        int UserID;//用户ID
        TaskStatus Status;//任务状态
        Application APP;//任务检测的APP
        CreateTask(int ID,Application APP);//构造函数
        int DeleteTask();//删任务对象
};
//任务服务器
class TaskServer{
    private:
        HTTPPackets SendBack();//用于发回报文
    public:
        TaskDatabase Database;
        CheckEngine Engine;
        int SubmitTask(Task task);//提交任务，任务在客户端封装
        Task[] GetAllTasks(int UserID);//得到所有任务的信息
        int CancelTask(int TaskID);//取消任务
        int DeleteTask(int TaskID);//删除任务
        Report GetReport(int TaskID);//得到指定任务的报告
};
//通知中心
class NoticeModule{
    private:
        Notice Notices[];
    public:
        int AddNotice(Notice notice);//增加新的通知，通知由CheckEngine来封装
        Notice[] GetNotice(int UserID);//得到用户的通知
        int DeleteNotice(int NoticeID);//删除指定通知
}
//客户端
class Client{
    private:
        int NoticeFinished();//提示用户任务完成了
        int DisplayAllTask();//向用户显示所有任务
        int DisplayNotice();//向用户显示所有通知
        int DisplayReport();//向用户显示报告
    public:
        int UserID;//用户ID
        NoticeModule noticeModule;
        TaskServer taskServer;
        int CreateTask(APP:Application);//创建任务
        int ViewTasks();//查看任务
        int CancelTask(int ID);//取消任务
        int DeleteTask(int ID);//删除任务
        int ViewNotice();//查看通知
        int DeleteNotice(int ID);//删除通知
        int ViewReport(int ID);//查看报告
        int DownloadReport(int ID);//下载报告
};
//存放任务信息的数据库
class TaskDatabase{
    private:
        Task Tasks[];
        Report Reports[];
    public:
        int InsertRecord(Task task);//加入任务记录
        Task[] SelectAllRecords(int UserID);//返回指定用户的所有任务
        int DeleteRecord(int TaskID);//删除任务记录
        int FinishCheck(int TaskID,TaskStatus Status,Report report);//完成任务时更新数据库记录以及报告
        Report SelectReport(int TaskID);//返回指定任务的报告
};
//验证的机器
class CheckEngine{
    public:
        TaskDatabase Database;
        NoticeModule noticeModule;
        void run();//常驻线程，在完成任务的时候请求数据库更新并提交通知
        int InsertWork(Task task);//增加任务
        int CancelWork(int TaskID);//取消任务
};