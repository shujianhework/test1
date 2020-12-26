using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Drawing;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
namespace testWeb.Page
{
    //专门处理日志显示的页面。因技术问题搁置
    public partial class LogShows : System.Web.UI.Page
    {
        List<String> alldirsbuff;
        List<String> templistbuff;
        protected void Page_Load(object sender, EventArgs e)
        {
            alldirsbuff = new List<string>();
            templistbuff = new List<string>();
            this.ListView1.Items.Clear();
            //ListViewItem item = new ListViewItem();
            //item.Text = "";
        }

        protected void Button1_Click(object sender, EventArgs e)
        {
            String[] list = Tools.Log.getQueueDirs();
            foreach (string item in list)
            {
                File.Delete(item);
            }
            alldirsbuff.Clear();
            templistbuff.Clear();
            ShowData2Log("");
        }
        protected void Button2_Click(object sender, EventArgs e)
        {
            alldirsbuff.Clear();
            String[] buff = Tools.Log.getQueueDirs();
            foreach (String item in buff)
            {
                alldirsbuff.Add(item);
            }
        }
        protected void Button3_Click(object sender, EventArgs e)
        {
            String str = TextBox1.Text;
            if (str.Count() > 0)
            {
                if (alldirsbuff.Count == 0)
                {
                    String[] buff = Tools.Log.getQueueDirs();
                    foreach (String item in buff)
                    {
                        alldirsbuff.Add(item);
                    }
                }
                if (alldirsbuff.Count() > 0)
                {
                    templistbuff.Clear();
                    String lstr = "";
                    foreach (String item in alldirsbuff)
                    {
                        if (item.IndexOf(str) != -1)
                        {
                            templistbuff.Add(item);
                            lstr = lstr + item + "\n";
                        }
                    }
                    //ShowData2Log(lstr);
                    
                }
            }
        }
        void ShowData2Log(String str)
        {
            this.TextBox2.Text = str;
        }

        protected void ListView1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
    }
}