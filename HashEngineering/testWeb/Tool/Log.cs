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
namespace Tools
{
    class Log
    {
        static private string Date;
        static private string RootPath;
        static private string path;
        static private ulong PrveSigSize;
        static private int PrveTime;
        static Log()
        {
            Date = "";
            path = "";
            Object WebRootPhysicsPath = HttpContext.Current.Request.PhysicalApplicationPath + "dynamicfiles";
            String WebRootDomainPath = HttpContext.Current.Request.Url.Host;
            PrveSigSize = 0;
            if (Directory.Exists(WebRootPhysicsPath.ToString()) == false)
                Directory.CreateDirectory(WebRootPhysicsPath.ToString());
            RootPath = WebRootPhysicsPath.ToString();
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
            String path1 = DateTime.Now.ToString("_HH-m-s_");
            Name = Name + path1;
            for (int i = 0; i < request.Files.Count; i++)
            {
                String str = request.Files[i].FileName;
                String lastPath = Path;
                write(lastPath);
                if (lastPath.IndexOf('.') == -1) { 
                    request.Files[i].SaveAs(lastPath+"/"+Name+str + ".log");
                }else
                    request.Files[i].SaveAs(lastPath);
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
    }
}
