using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace testWeb.Message
{
    public class MsgCenter
    {

        static private Dictionary<UInt64, Dictionary<String, Object>> MSG;
        static private UInt64 HashId = 0xffffffffffffff;
        static private Queue<UInt64> queuelist;
        static private Dictionary<String, Logic.BaseHandle> DSB = new Dictionary<string, Logic.BaseHandle>();
        static private Dictionary<String, List<UInt64>> TypeList = new Dictionary<string,List<ulong>>();
        enum MsgState
        {
            //InMSG = 0,
            //InHandle
        }
        static MsgCenter()
        {
            MSG = new Dictionary<UInt64,Dictionary<string, object>>();
            queuelist = new Queue<ulong>();
            DSB["CmdHandle"] = new Logic.CmdHandle();
            foreach (var item in DSB)
            {
                item.Value.SetClassKey(item.Key);
                item.Value.init();
                TypeList[item.Key] = new List<ulong>();
            }
        }
        public static UInt64 push(ref Dictionary<string, object> msg)
        {
            UInt64 pid = 0;
            if (msg.ContainsKey("back") == false)
            {
                return 0;
            }
            Object obj = msg["back"];
            Func<String,bool> back = (str)=>{
                return true;
            };
            if (obj.GetType() != back.GetType())
            {
                return 0;
            }
            if (msg.ContainsKey("exe") == false || !(msg["exe"] is String))
            {
                return 0;
            }
            if (msg.ContainsKey("runcmd") == false || !(msg["runcmd"] is String) || DSB.ContainsKey(msg["runcmd"].ToString()) == false)
            {
                return 0;
            }
            if (msg.ContainsKey("cmd") == false || !(msg["cmd"] is String))
            {
                return 0;
            }
            //0 还不知道 1 可以立即响应 2 不能立即响应，需要后面get页面 参数来获取状态或者内容 
            pid = HashId;
            Logic.BaseHandle bsd = DSB[msg["runcmd"].ToString()];
            if (bsd.CheckIsWait(ref msg) == false)
            {
                if (HashId < UInt64.MaxValue)
                    HashId++;
                else
                    HashId = 0xffffffffffffff;
                if (MSG.ContainsKey(HashId) == true)
                {
                    return push(ref msg);
                }
                TypeList[msg["runcmd"].ToString()].Add(pid);
                msg["runcmd"] = bsd;
                msg["wait"] = 0;
                msg["time"] = DateTime.Now;
                msg["pid"] = pid;
                Func<Dictionary<string, object> , bool> remove = (self) =>
                {
                    Object suid = self["pid"];
                    if (suid == null)
                    {
                        self.Clear();
                    }
                    UInt64 uid = (UInt64)suid;
                    MSG.Remove(uid);
                    self.Clear();
                    return false;
                };
                msg["remove"] = remove;
                queuelist.Enqueue(pid);
                return pid;
            }
            else
                msg["runcmd"] = null;
            bsd.Run(ref msg);
            return UInt64.MaxValue;
            
        }
        public static Dictionary<string, object> pop()
        {
            try{
                UInt64 uid = queuelist.Peek();
                if(uid < 100000)
                    return null;
                if (MSG.ContainsKey(uid) == false)
                    return null;
                return MSG[uid];
            }
            catch (Exception)
            {
                return null;
            }
            
        }
        public static Dictionary<string, object> onlySelectPop(String Str)
        {
            if(TypeList.ContainsKey(Str) == false)
                return null;
            var lis = TypeList[Str];
            if (lis.Count() == 0)
                return null;
            UInt64 uid = lis.First();
            if (MSG.ContainsKey(uid) == false)
                return null;
            return MSG[uid];
        }
        public static int size()
        {
            return MSG.Count();
        }
    }
}