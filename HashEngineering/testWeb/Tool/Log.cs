using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Net;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Threading;
namespace Tools
{
    class ListBuffData{
        public String _data = "";
        public String _path = "";
        public ListBuffData(String data,String prvepath = "")
        {
            DateTime dt = DateTime.Now;
            _data = data + "\t\t\t" + "[" + dt.ToString("yyyy-MM-dd HH:mm:ss.fff") + "]"; ;
            _path = prvepath;
            
        }
    }
    class Log
    {
        static private string Date;
        static private DateTime prveDateTime;
        static private string RootPath;
        static private string path;
        static private string queuepath;
        static private ulong PrveSigSize;
        static private int PrveTime;
        static private DateTime PrveDate;
        static private List<ListBuffData> listbuff = new List<ListBuffData>();
        static private ListBuffData[] temparr = new ListBuffData[130];
        static public bool SwitchWriteLog = true;
        public static object dtFlag = new object();
        static Log()
        {
            Date = "";
            path = "";
            Object WebRootPhysicsPath = HttpContext.Current.Request.PhysicalApplicationPath + "dynamicfiles";
            String WebRootDomainPath = HttpContext.Current.Request.Url.Host;
            PrveSigSize = 0;
            if (Directory.Exists(WebRootPhysicsPath.ToString()) == false)
                Directory.CreateDirectory(WebRootPhysicsPath.ToString());
            if (Directory.Exists(WebRootPhysicsPath.ToString()+"queue") == false)
                Directory.CreateDirectory(WebRootPhysicsPath.ToString()+"queue");
            prveDateTime = DateTime.Now;
            RootPath = WebRootPhysicsPath.ToString();
            PrveDate = prveDateTime;
            
        }
        static private void loop()
        {
            Action<Boolean> UpdateTimeFileName = delegate(Boolean b)
            {
                DateTime now = DateTime.Now;
                if (now.Day != PrveDate.Day || now.Hour != PrveDate.Hour)
                {
                    PrveDate = now;
                }
                return;
            };
            int TimesFullLoad = 0;
            int TimesCoutLoop = 0;
            while (true)
            {
                try
                {
                    int size = listbuff.Count;
                    if (size > 0)
                    {
                        lock (dtFlag)
                        {
                            size = listbuff.Count;
                            if (size < 130)
                            {
                                for (int i = 0; i < size; i++)
                                {
                                    temparr[i] = listbuff[i];
                                }
                                listbuff.Clear();
                            }
                            else
                            {
                                for (int i = 0; i < 130; i++)
                                {
                                    temparr[i] = listbuff[i];
                                }
                                for (int i = 0; i < 130; i++)
                                {
                                    listbuff.RemoveAt(0);
                                }
                                size = 130;
                            }
                        }
                        for (int i = 0; i < size; i++)
                        {
                            String path = temparr[i]._path;
                            if (path.Equals(""))
                                path = queuepath;
                            else
                                path = RootPath + "queue\\" + path + ".log";
                            var mysw = File.AppendText(path);
                            mysw.WriteLine(temparr[i]._data);
                            mysw.Close();
                        }
                        //后面 睡眠 4 -- 30 s
                        int SleepSec = 30 - size * 26 / 130;
                        TimesCoutLoop = TimesCoutLoop + 1;
                        if (TimesCoutLoop == 800)
                        {
                            TimesCoutLoop = 0;
                            UpdateTimeFileName(true);
                        }
                        if (size != 130)//还没有满负荷运作
                        {
                            Thread.Sleep(SleepSec);
                        }
                        else
                        {
                            TimesFullLoad++;
                            if (TimesFullLoad > 5000)//130*5000
                            {
                                SwitchWriteLog = false;
                            }
                        }

                    }
                    else
                    {
                        SwitchWriteLog = true;
                        TimesFullLoad = 0;
                        TimesCoutLoop = 0;
                        UpdateTimeFileName(true);
                        Thread.Sleep(5);
                    }
                }
                catch (Exception s)
                {
                }
                finally
                {
                }
            }
        }
        static public void setSwitchWriteLog(bool flg)
        {
            if (flg != SwitchWriteLog)
            {
                if (SwitchWriteLog == false && listbuff.Count > 5000)
                {
                    lock(dtFlag)
                        listbuff.Clear();
                }
                SwitchWriteLog = flg;
            }
        }
        static public String getSwitchWriteLog()
        {
            return "SwitchWriteLog = " + SwitchWriteLog.ToString() + " listsize = " + listbuff.Count;
        }
        static private string GetHead()
        {
            DateTime dt = DateTime.Now;
            if (dt.ToString("D") != Date)
            {
                Date = dt.ToString("D");
                path = RootPath +"\\" + Date + ".log";
                if (File.Exists(path) == false)
                {
                    var f = File.Create(path);
                    f.Close();
                }
                queuepath = RootPath + "queue\\" + Date + ".log";
                if (File.Exists(queuepath) == false)
                {
                    var f = File.Create(queuepath);
                    f.Close();
                }
            }
            return "[" + dt.ToString("yyyy-MM-dd HH:mm:ss.fff") + "]";
        }
        static public void write(string s)
        {
            s = s + GetHead();
            var mysw = File.AppendText(path);
            mysw.WriteLine(s);
            mysw.Close();
        }
        static public void Error(string s)
        {
            write(s);
        }
        static public bool CheckCreateDirectory(String Path)
        {
            try {
                if (Directory.Exists(Path) == false)
                {
                    DirectoryInfo di = Directory.CreateDirectory(Path);
                    return di.Exists;
                }
            }
            catch (Exception ex)
            {
                return false;
            }
            return true;
        }
        static private String GetDirName(HttpRequest request, out int version, out String DirName,out String FileName)
        {
            FileName = "";
            if(request.Files.Count < 1)
            {
                DirName = "";
                version = 0;
                return "";
            }
            String ret = "";
            String Version = request["Version"];
            version = 0;
            if (Version != null)
            {
                if (Int32.TryParse(Version, out version) == false)
                    version = 0;
            }
            DirName = "";
            if (version == 0)
            {
                String Channel = request["Channel"];
                String Device = request["Device"];
                if (Channel == null || Channel == "")
                    Channel = "Other";
                if (Device == null || Device == "")
                    Device = "Other";
                String Topath = RootPath;
                if (Directory.Exists(Topath) == false)
                    Directory.Exists(Topath);
                if (CheckCreateDirectory(Topath + "\\" + Channel))
                    Topath = Topath + "\\" + Channel;
                else
                {
                    CheckCreateDirectory(Topath + "\\Other");
                    Topath = Topath + "\\Other";
                }
                if (CheckCreateDirectory(Topath + "\\" + Device))
                    Topath = Topath + "\\" + Device;
                else
                {
                    CheckCreateDirectory(Topath + "\\Other");
                    Topath = Topath + "\\Other";
                }
                if (Directory.Exists(Topath) == false)
                {
                    return "中间路径生成失败，目标路劲为:" + Topath;
                }
                String path1 = DateTime.Now.ToString("F").Replace(' ', '—');
                path1 = path1.Replace(':', '_');
                Topath = Topath + "\\" + path1;
                ret = Topath;
                DirName = ret;
            }
            else if (version == 1) {
                string ISW = request["ISW"];
                if (ISW == null)
                    ISW = "w";
                else
                {
                    String isw2 = ISW.ToLower();
                    ISW = isw2;
                    if (ISW == "ios" || ISW == "i") {
                        ISW = "i";
                    }
                    else if (ISW == "android" || ISW == "a") {
                        ISW = "a";
                    }
                    else
                    {
                        ISW = "w";
                    }
                }
                String UserDirs = request["UserDirs"];
                if(UserDirs == null)
                {
                    UserDirs = "Other/Other/Other/Other";
                }
                else
                {
                    String [] dispool = UserDirs.Split('/');
                    if (dispool.Length > 8)
                    {
                        DirName = "";
                        return "";
                    }
                    for (int i = 0; i < dispool.Length; i++)
                    {
                        if(dispool[i].Length < 1 || dispool[i].Length > 18 || dispool[i].IndexOf(':') >= 0 || dispool[i].IndexOf('.') >= 0)
                        {
                            DirName = "";
                            return "";
                        }
                    }
                }
                String UserName = request["UserName"];
                if (UserName == null || UserName == "" || UserName.IndexOf('\\') >= 0)
                {
                    UserName = "N";
                }
                UserDirs = RootPath + UserDirs;
                if (Directory.Exists(UserDirs) == false)
                {
                    DirectoryInfo dir = Directory.CreateDirectory(UserDirs);
                    if(dir.Exists == false)
                    {                        
                        return "";
                    }                    
                }
                FileName = ISW+"_";   
                FileName = FileName + UserName + "_";
                DirName = UserDirs;
                ret = UserDirs;
            }
            return ret;

        }
        static private String SaveNames(HttpRequest request,String Path, String Name)
        {
            Dictionary<String, String> ret = new Dictionary<string, string>();
            //String path1 = DateTime.Now.ToString("_HH-m-s_");
            //Name = Name + path1;
            for (int i = 0; i < request.Files.Count; i++)
            {
                String str = request.Files[i].FileName;
                String lastPath = Path;
                write(lastPath);
                if (str.IndexOf('.') == -1)
                { 
                    request.Files[i].SaveAs(lastPath+Name+str + ".log");
                }else
                    request.Files[i].SaveAs(lastPath+Name+str);
            }
            return Path+"/"+Name+"****.log";
        }
        static public String UpdateFile(HttpRequest request)
        {
            int version = 0;
            String DirPath = "";
            String FileName = "";
            DateTime Now = DateTime.Now;
            int curtime = Now.Hour * 10000 + Now.Minute * 100 + Now.Second;
            if (curtime != PrveTime)
            {
                PrveSigSize = 0;
                PrveTime = curtime;
            }
            PrveSigSize = PrveSigSize + 1;
            if (PrveSigSize > 100)
            {
                return "";
            }
            if (GetDirName(request, out version, out DirPath, out FileName) == "")
            {
                return "";
            }
            String SavePath = SaveNames(request, DirPath, FileName);
            write("Put Log Info Item: " + DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss") + " :" + SavePath);
            return "";
        }
        static public String UpdateFile1(HttpRequest request) {
            String Topath = "";
            if (request.Files.Count == 0)
                return "无上传文件";
            
            String Channel = request["Channel"];
            String Device = request["Device"];
            if (Channel == null || Channel == "")
                Channel = "Other";
            if (Device == null || Device == "")
                Device = "Other";
            Topath = RootPath;
            if (Directory.Exists(Topath) == false)
                Directory.Exists(Topath);
            if (CheckCreateDirectory(Topath + "\\" + Channel))
                Topath = Topath + "\\" + Channel;
            else
            {
                CheckCreateDirectory(Topath + "\\Other");
                Topath = Topath + "\\Other";
            }
            if (CheckCreateDirectory(Topath + "\\" + Device))
                Topath = Topath + "\\" + Device;
            else
            {
                CheckCreateDirectory(Topath + "\\Other");
                Topath = Topath + "\\Other";
            }
            if (Directory.Exists(Topath) == false)
            {
                return "中间路径生成失败，目标路劲为:"+Topath;
            }
            String path1 =  DateTime.Now.ToString("F").Replace(' ','—');
            path1 = path1.Replace(':', '_');
            Topath = Topath + "\\" + path1;

            if (request.Files.Count == 1) {                
                Topath = Topath + request.Files[0].FileName;
                request.Files[0].SaveAs(Topath);
                return "写入文件:" + Topath;
            }
            else
            {
                String ret = "";
                for (int i = 0; i < request.Files.Count; i++)
                {
                    String str = request.Files[i].FileName;
                    request.Files[i].SaveAs(Topath+str);
                    ret = ret + "," + Topath;
                }
                return ret;
            }
        }
        
        static public void Queuewrite(string s,String prvepath = "")
        {
            if (SwitchWriteLog == false)
                throw new Exception("已经关闭日志写入");
            if (prvepath.Equals(""))
                prvepath = GetHead();
            else
            {
                prvepath = prvepath.Replace(".", "");
                prvepath = prvepath.Replace("\\", "");
                prvepath = prvepath.Replace("/", "");
                prvepath = prvepath +"_"+ PrveDate.ToString("yy-MM-dd-H");
                if (File.Exists(RootPath + "queue\\" + prvepath + ".log") == false)
                {
                    var f = File.Create(RootPath + "queue\\" + prvepath + ".log");
                    f.Close();
                }
            }
            lock (dtFlag)
            {
                if(listbuff.Count > 20){
                    var last = listbuff[listbuff.Count - 1];
                    if ((last._data.Length + s.Length) < 5000 && last._path.Equals(prvepath))
                    {
                        listbuff[listbuff.Count - 1]._data = last._data + s;
                        return;
                    }
                }
                ListBuffData lbd = new ListBuffData(s,prvepath);
                listbuff.Add(lbd);
            }
        }
        static public string[] getQueueDirs()
        {
            String path = RootPath + "queue\\";
            if (Directory.Exists(path))
            {
                return Directory.GetFiles(RootPath+"queue","*.log");
            }
            return null;
        }
        
    }
}
