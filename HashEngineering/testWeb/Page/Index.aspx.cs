using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.IO;
using System.Configuration;
namespace testWeb.Page
{
    public partial class Index : System.Web.UI.Page
    {
        static private Random ran = new Random();
        protected void Page_Load(object sender, EventArgs e)
        {
            String path = ConfigurationManager.AppSettings["path"];
            if (path == null || path == "")
            {
                Response.Write("并未设置要读取路径");
                return;
            }
            try
            {
                String[] data = File.ReadAllLines(path);
                Response.Write("读取到的行数" + data.Length + "内容如下");
                for (int i = 0; i < data.Length; i++)
                {
                    Response.Write(data[i]);
                }
                return ;
            }
            catch (Exception ex)
            {
                Response.Write("发生了异常");
                Response.Write(ex.ToString());
                return;
            }
        }
    }
}