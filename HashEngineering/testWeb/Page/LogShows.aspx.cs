using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace testWeb.Page
{
    public partial class LogShows : System.Web.UI.Page
    {
        List<String> alldirsbuff;
        List<String> templistbuff;
        protected void Page_Load(object sender, EventArgs e)
        {
            alldirsbuff = new List<string>();
            templistbuff = new List<string>();
            ListViewItem lvi = new ListViewItem(0);
            lvi.DataItem = "sdfsd";
            ListViewDataItem lvdi = new ListViewDataItem(0, 0);
            for (int i = 0; i < 10; i++)
            {
                ListView1.Items.Add("");

            }
            //ListView1.Row
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