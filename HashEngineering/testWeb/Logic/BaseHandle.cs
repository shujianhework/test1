using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace testWeb.Logic
{
    abstract public class BaseHandle
    {
        private String ClassKey;
        public void SetClassKey(String str)
        {
            ClassKey = str;
        }
        abstract public bool CheckIsWait(ref Dictionary<string,Object> data);
        abstract public void Run(ref Dictionary<string, Object> data);
        abstract public bool init();
        public Dictionary<String,Object> onlySelectPop()
        {
            return Message.MsgCenter.onlySelectPop(ClassKey);
        }
    }
}