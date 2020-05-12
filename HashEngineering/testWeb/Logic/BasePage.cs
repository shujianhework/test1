using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Script.Serialization;
using testWeb.Message;
namespace testWeb.Logic
{
    public class BasePage
    {
        public static bool BaseHeadHand(System.Web.UI.Page page,ref Dictionary<String, Object> data){
            String Keys = page.Request["Keys"];
            String Cmd = page.Request["Cmd"];
            String Help = page.Request["Help"];
            bool help = false;
            if ((Cmd == null || Keys == null) && Help == null)
            {
                help = true;
            }
            try
            {
                if (Help != null && Help != "")
                {
                    help = true;
                }
                else
                {
                    if (Cmd != null && Cmd != "" && Keys != null && Keys != "")
                    {
                        JavaScriptSerializer json = new JavaScriptSerializer();
                        String[] keys = json.Deserialize<String[]>(Keys);
                        Func<String, bool> fun = (str) =>
                        {
                            return false;
                        };
                        data["back"] = fun;
                        for (int i = 0; i < keys.Length; i++)
                        {
                            String temp = page.Request[keys[i]];
                            if (temp == null || temp == "")
                            {
                                throw new Exception("");
                            }
                            if (data.ContainsKey(temp))
                            {
                                throw new Exception("已经存在该key请检查是否重复或者占用系统key "+temp);
                            }
                            data[keys[i]] = temp;
                        }
                    }
                    else
                    {
                        help = true;
                    }
                }
                
            }
            catch (Exception ex)
            {
                help = true;
                page.Response.Write(ex.ToString());
            }
            finally
            {
                if (help == true)
                {
                    if(data.ContainsKey("gethelp"))
                    {
                        Func<String>fun = (Func<String>)data["gethelp"];
                        page.Response.Write(fun());
                    }
                }
                else
                {
                    MsgCenter.push(ref data);
                }
            }
            return true;
        }
    }
}