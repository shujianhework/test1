using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Threading;
using System.Threading.Tasks;
using System.Diagnostics;

namespace testWeb.Logic
{
    public class CmdHandle:BaseHandle
    {
        override public bool CheckIsWait(ref Dictionary<string, Object> data)
        {
            return true;
        }
        override public void Run(ref Dictionary<string, Object> data)
        {
            Process P = new Process();
            P.StartInfo.CreateNoWindow = true;
            P.StartInfo.FileName = "cmd.exe";
            P.StartInfo.UseShellExecute = false;
            P.StartInfo.RedirectStandardError = true;
            P.StartInfo.RedirectStandardInput = true;
            P.StartInfo.RedirectStandardOutput = true;
            P.Start();
        }
        public void loop()
        {
            Process P = new Process();
            P.StartInfo.CreateNoWindow = true;
            P.StartInfo.FileName = "cmd.exe";
            P.StartInfo.UseShellExecute = false;
            P.StartInfo.RedirectStandardError = true;
            P.StartInfo.RedirectStandardInput = true;
            P.StartInfo.RedirectStandardOutput = true;
            P.Start();
        }
        override public bool init()
        {
            //delegate void ThreadStart();
            //Action<int> ac = [](a){};
            Thread th = new Thread(new ParameterizedThreadStart(t =>
            {
                CmdHandle cmdthre = (CmdHandle)t;
                this.loop();
            }));
            th.Start(this);
            return true;
        }
    }
}