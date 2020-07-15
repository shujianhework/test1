using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Web.Script.Serialization;
using System.IO;
using System.Web;
namespace Tools
{
    class PIL<T>{
        public bool isArr;
        public string jsonstr;
        public PIL(Dictionary<int, T> data, Func<T, string> back)
        {
            isArr = false;
            if (data.Count > 0 && data.ContainsKey(0) && data.ContainsKey(data.Count - 1))
            {
                int idx = 0;
                for (int i = 1; i < data.Count - 2; i++)
                {
                    if (data.ContainsKey(i) == false)
                    {
                        idx = -1;
                        break;
                    }
                    idx = i;
                }
                isArr = idx > -1;
            }
            string s = isArr ? "[" : "{";
            foreach (var item in data)
            {
                if (!isArr)
                    s = s +"\"" + item.Key + "\":";
                string tempstr = back(item.Value).ToString();
                s = s + tempstr + ",";
            }
            s = s.Substring(0, s.Length - 1) + (isArr ? "]" : "}");
            jsonstr = s;
        }
        public PIL(Dictionary<string, T> data, Func<T, string> back)
        {
            isArr = false;

            string s = isArr ? "[" : "{";
            foreach (var item in data)
            {
                if (!isArr)
                    s = s +"\"" +item.Key + "\":";
                string tempstr = back(item.Value).ToString();
                s = s + tempstr + ",";
            }
            s = s.Substring(0, s.Length - 1) + (isArr ? "]" : "}");
            jsonstr = s;
        }
        public PIL(List<T> data,Func<T,string> back)
        {
            isArr = true;
            string s = "[";
            foreach (var item in data)
            {
                string tempstr = back(item).ToString();
                s = s + tempstr + ",";
            }
            s = s.Substring(0, s.Length - 1) +"]";
            jsonstr = s;
        }
        public PIL(T[] data,bool PisArr, Func<T, string> back)
        {
            isArr = true;
            string s = "[";
            foreach (var item in data)
            {
                string tempstr = back(item).ToString();
                s = s + tempstr + ",";
            }
            s = s.Substring(0, s.Length - 1) + "]";
            jsonstr = s;
        }
    }
    class Tool
    {
        static private JavaScriptSerializer json = new JavaScriptSerializer();
        static Tool() {}
        //static public string Object2Json(object data){
        //    if (data == null)
        //        return "";
        //    return json.Serialize(data);
        //}
        static public string Object2Json(Dictionary<string, string> data)
        {
            if (data == null)
                return "";
            return json.Serialize(data);
        }
        //static public T string Object2Json(Dictionary)
        static public string Object2Json(Dictionary<int, Dictionary<string,object>> data)
        {
            if (data == null)
                return "";
            Func<Dictionary<string, object>, string> func = (obj) =>
            {
                return json.Serialize(obj);
            };
            var pil = new PIL<Dictionary<string, object>>(data,(obj)=>json.Serialize(obj));
            return pil.jsonstr;
        }
        static public string Object2Json(Dictionary<int, Dictionary<string, string>> data)
        {
            if (data == null)
                return "";
            var pil = new PIL<Dictionary<string, string>>(data, (obj) => json.Serialize(obj));
            return pil.jsonstr;
        }
        static public string Object2Json(Dictionary<string, Dictionary<string, string>> data)
        {
            if (data == null)
                return "";
            var pil = new PIL<Dictionary<string, string>>(data, (obj) => json.Serialize(obj));
            return pil.jsonstr;
        }

        static public string Object2Json(object[] data)
        {
            if (data == null)
            {
                return "";
            }
            var pil = new PIL<object>(data,true, (obj) => json.Serialize(obj));
            return pil.jsonstr;
        }
        static public string Object2Json(int data)
        {
            return json.Serialize(data);
        }
        static public string Object2Json(string data)
        {
            return json.Serialize(data);
        }
        static public string Object2Json(double data)
        {
            return json.Serialize(data);
        }
        static public string Object2Json(bool data)
        {
            return json.Serialize(data);
        }
        static public object Json2Object(string s)
        {
            return json.DeserializeObject(s);
        }
        static public bool Json2Objects<T>(string s, Func<T, int, bool> func)
        {
            bool ret = false;
            try
            {
                object obj = Json2Object(s);
                object[] objs = obj as object[];
                if (objs == null)
                    return false;
                for (int i = 0; i < objs.Length; i++)
                {
                    T item = (T)objs[i];
                    if (item == null)
                        return false;
                    if (func(item, i) == false)
                        return false;
                }
                ret = true;
            }
            catch (Exception ex)
            {
                ret = false;
            }
            return ret;
        }
        public static string GetMD5HashFromFile(string fileName)
        {
            try
            {
                FileStream file = new FileStream(fileName, FileMode.Open);
                System.Security.Cryptography.MD5 md5 = new System.Security.Cryptography.MD5CryptoServiceProvider();
                byte[] retVal = md5.ComputeHash(file);
                file.Close();

                StringBuilder sb = new StringBuilder();
                for (int i = 0; i < retVal.Length; i++)
                {
                    sb.Append(retVal[i].ToString("x2"));
                }
                return sb.ToString();
            }
            catch (Exception ex)
            {
                throw new Exception("GetMD5HashFromFile() fail,error:" + ex.Message);
            }
        }
        public static bool GetMD5HashFromFiles(ref Dictionary<int, Dictionary<string, string>> infos)
        {
            bool ret = true;
            string tempstr = "";
            try
            {
                foreach (var item in infos)
                {
                    item.Value["md5"] = GetMD5HashFromFile(item.Value["File"]);
                }
            }
            catch (Exception ex)
            {
                ret = false;
                Log.write("加载系列md5文件失败" + ex.ToString() + "\n"+tempstr);
                infos.Clear();
                infos[0] = new Dictionary<string, string>();
                infos[0]["Error"] = "true";
            }
            return ret;
        }
        public static string Greplace(string str, string pattern, string repl)
        {
            char[] cstr = str.ToCharArray();
            char[] cpattern = pattern.ToCharArray();
            return Greplace(cstr,cpattern,repl);
        }
        public static string Greplace(char[] str,char[] pattern,string repl)
        {
            int index = 0;
            int strlen = str.Length;
            string ret = "";
            if (strlen < pattern.Length)
            {
                for (int i = 0; i < strlen; i++)
                {
                    ret = ret + str[i];
                }
            }
            else
            {
                while (true)
                {
                    if (strlen <= index)
                        break;
                    if (str[index] != pattern[0])
                    {
                        ret = ret + str[index];
                        index++;
                    }
                    else
                    {
                        int flen = -1;
                        for (int i = 0; i < pattern.Length; i++)
                        {
                            if (strlen < (index + i) || str[index + i] != pattern[i])
                            {
                                break;
                            }
                            flen = i;
                        }
                        flen++;
                        if (flen == pattern.Length)
                        {
                            ret = ret + repl;
                            index += flen;
                        }
                        else
                        {
                            for (int i = 0; i < flen; i++)
                            {
                                ret = ret + str[index + i];
                            }
                            index += flen;
                        }
                    }
                }
            }
            return ret;
        }
        public static string GetIp(HttpRequest Request)
        {
            string userIP = "";
            try
            {
                userIP = Request.ServerVariables["HTTP_X_FORWARDED_FOR"];
                if (userIP == null || userIP == "")
                {
                    userIP = Request.ServerVariables["REMOTE_ADDR"];
                }
            }
            catch (Exception ex)
            {
                userIP = "error";
                return userIP;
            }
            return userIP;
        } 
    }
}
