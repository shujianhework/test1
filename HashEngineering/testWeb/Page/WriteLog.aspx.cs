using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace testWeb.Page
{
    //最初版本的写日志提页面。已经停用
    public partial class WriteLog : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            try
            {
                String Head = this.Request["head"];
                String data = this.Request["data"];
                if (Head != null && data != null)
                {
                    Tools.Log.write("head:" + Head + "\ndata:" + data);
                    Response.Write("ok");
                }
                else
                {
                    Response.Write("ffffffffffffffff");
                }
            }
            catch (Exception ex)
            {
                Response.Write(ex.ToString());
            }
        }
    }
}