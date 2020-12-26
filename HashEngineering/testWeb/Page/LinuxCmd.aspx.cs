using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using testWeb.Message;
using System.Web.Script.Serialization;
using testWeb.Logic;
//Linux 系统命令 暂时已废除
namespace testWeb.Page
{
    public partial class LinuxCmd : System.Web.UI.Page
    {
        private static String helpText = "";
        private static DateTime dt = DateTime.Now;
        
        protected void Page_Load(object sender, EventArgs e)
        {
            if (DateTime.Now.Day != dt.Day)
            {
                helpText = "";
            }
            Dictionary<String, Object> data = new Dictionary<string, object>();
            Func<String,String> fun = (str) =>
            {
                return this.getHelp(str);
            };
            data["gethelp"] = fun;
            data["runcmd"] = "cmd.cs";
            
            BasePage.BaseHeadHand(this,ref data);
        }
        public String getHelp(String str)
        {
            if (helpText == "")
            {
                Dictionary<string,Object> helpdata = new Dictionary<string,object>();
                helpdata["runcmd"] = "cmd.cs";
                helpdata["dir"] = "C:\\cygwin64\\bin";
                if (str == null || str == "")
                    helpdata["exepath"] = "";
                else
                    helpdata["exepath"] = str+" -help ";
                Func<String> fun = () =>
                {
                    return this.getHelp("");
                };
                helpdata["back"] = fun;
                MsgCenter.push(ref helpdata);
            }
            return helpText;
        }
    }
}