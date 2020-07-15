using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace testWeb.Page
{
    public partial class Temp : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            String Str = Request["Str"];
            if (Str == null)
            {
                Response.Write("缺少参数");
            }
            else
            {
                Response.Write("传入参数:" + Str);
                Response.Write("代码页:" + Encoding.GetEncoding(Str));
            }
        }
    }
}