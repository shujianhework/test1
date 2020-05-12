using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace testWeb.Page
{
    public partial class UpdateFile : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            try
            {
                String ret = Tools.Log.UpdateFile(Request);
                //Response.Write(ret);
            }
            catch (Exception ex)
            {
                Tools.Log.write(ex.ToString());
                Response.Write(ex.ToString());
            }
        }
    }
}